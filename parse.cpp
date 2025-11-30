

#include "parse.h"
#include "porter_stemming.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QDataStream>
#include <QTime>
#include <QDebug>

char *Parse::p_data;
QVector<QString> alltitle;
std::unordered_map<QString, QVector<int>> keypos;
Graph* g;

QString filter_Non_Punctuation(QString str) {
    QString res;
    for (QChar c : str)
        if (!c.isPunct()) res += c;
    return res;
}

Parse::Parse(QObject *parent) : QThread(parent) {
    condi = author_flag = title_flag = group_flag = key_flag = 0;
    author_count.resize(100);
}

void Parse::run() {
    switch (condi) {
    case 0: parse(); break;
    case 1: parse_Author(); break;
    case 2: parse_Title(); break;
    case 3: parse_AuthorGroup(); break;
    case 4: parse_KeyWord(); break;
    }
}

void Parse::parse_AuthorGroup() {
    if (group_flag == 0) {
        clique.clear();
        m_timing.start();
        emit state_Changed("开始作者群组分析.");

        QFile file(m_fileName);
        file.open(QFile::ReadOnly);
        p_data = new char[file.size()];
        quint32 len = file.read(p_data, file.size());
        file.close();
        emit state_Changed("成功读取xml文件.");

        QVector<int> oneAuthorIndex;
        quint32 x = 0;
        int verticlenum = 1, edgenum = 0;
        QSet<QPair<int, int>> edgeSet;

        g = initialize_graph(3600000, 49826330 << 1);
        if (!authorList.contains(" ")) authorList.insert(" ", 0);

        while (x < len) {
            if (p_data[x] == '<') {
                if (String_Ref(x, len).start_With("title", 1)) {
                    oneAuthorIndex.clear();
                }
                else if (String_Ref(x, len).start_With("author", 1)) {
                    String_Ref author = read_ElementText(String_Ref(0, len), x);
                    QString str = get_Information(author);
                    if (!authorList.contains(str))
                        authorList.insert(str, verticlenum++);

                    int current = authorList[str];
                    for (int prev : oneAuthorIndex) {
                        if (!edgeSet.contains({prev, current})) {
                            add_unweighted_edge(g, prev + 1, current + 1);
                            add_unweighted_edge(g, current + 1, prev + 1);
                            edgeSet.insert({prev, current});
                            edgeSet.insert({current, prev});
                            edgenum += 2;
                        }
                    }
                    oneAuthorIndex.append(current);
                }
            }
            ++x;
        }

        g->vertex_count = verticlenum;
        g->edge_count = edgenum;
        double *C = (double *)calloc(verticlenum + 1, sizeof(double));
        Pivoter::run_pivoter_algorithm(g, C);

        int time = m_timing.elapsed();
        emit state_Changed(QString("关系图已产生. 耗时: %1").arg(Util::formatTime(time)));

        delete[] p_data;
        for (int i = 1; i <= 500; ++i) {
            if (C[i] > 0) {
                clique.append(C[i]);
                emit state_Changed(QString("%1 群组数: %2").arg(i).arg(C[i], 0, 'f', 1));
            }
        }

        m_costMsecs = m_timing.elapsed();
        emit state_Changed(QString("完成作者群组分析. 总共耗时: %1").arg(Util::formatTime(m_costMsecs)));
        group_flag = 1;
        emit done();
    }
    else if (group_flag == 1) {
        for (int i = 0; i < clique.size(); ++i)
            emit state_Changed(QString("%1 群组数: %2").arg(i + 1).arg(clique[i]));
        emit done();
    }
}


void Parse::parse_Author(){
    if(author_flag==0){
        m_timing.start();  // 开始计时
        emit state_Changed(tr("开始作者文章计数分析.<br/>"));
        // 检查文件名是否为空

        QFile file(m_fileName);
        file.open(QFile::ReadOnly);

        p_data = new char[static_cast<quint64>(file.size())];
        quint32 len = static_cast<quint32>(file.read(p_data, file.size()));
        String_Ref ref(0, len);
        file.close();
        emit state_Changed(tr("成功读取xml文件."));

        QVector<String_Ref> authorcountIndex;  // 用于存储作者索引的容器
        quint32 x = 0;
        while(x < len){
            if(ref[x] == '<'){
                if(ref.start_With("author", x + 1)){  // 如果遇到了<author>标签
                    String_Ref author = read_ElementText(ref, x);  // 从标签中读取文本内容
                    authorcountIndex.append(author);  // 将读取的作者信息添加到作者索引容器中
                }
            }
            ++x;
        }
        emit state_Changed(tr("正在整理索引文件……"));
        // 使用 QHash 统计每个字符串的出现次数
        QHash<QString, int> countMap;
        for (const auto& ref : authorcountIndex) {
            QString str = QString::fromUtf8(p_data + ref.l, ref.r - ref.l);
            countMap[str]++;
        }
        // 使用 QMap 对计数结果进行排序
        QMap<int, QString> sortedMap;
        for (auto it = countMap.begin(); it != countMap.end(); it++) {
            sortedMap.insert(it.value(), it.key());
        }
        // 输出出现次数最多的前一百个字符串
        QMap<int, QString>::iterator it = sortedMap.end();
        int count=0;
        while (it != sortedMap.begin()&& count<100) {
            --it;
            author_count[count].first=it.key();        author_count[count].second=it.value();
            emit state_Changed(tr("No.%1 作者: %2 数量: %3 <br/>").arg(count+1).arg(it.value()).arg(it.key()));
            count++;
        }
        author_flag=1;

        delete[] p_data;

        m_costMsecs = m_timing.elapsed();
        emit state_Changed(tr("作者文章计数分析完毕. 总共耗时: %1").arg(Util::formatTime(m_costMsecs)));
        emit done();
    }
    else if(author_flag==1){
        for(int i=0;i<100;i++){
            emit state_Changed(tr("No.%1 作者: %2 数量: %3 <br/>").arg(i+1).arg(author_count[i].second).arg(author_count[i].first));
        }
        emit done();
    }

}

void Parse::parse_Title(){
    if(title_flag==0){
        m_timing.start();
        emit state_Changed(tr("开始标题分析."));

        QFile file(m_fileName);
        file.open(QFile::ReadOnly);

        p_data = new char[static_cast<quint64>(file.size())];
        quint32 len = static_cast<quint32>(file.read(p_data, file.size()));
        String_Ref ref(0, len);
        file.close();
        emit state_Changed(tr("成功读取xml文件."));
        quint32 x = 0;
        while(x < len){
            if(ref[x] == '<'){
                if(ref.start_With("title", x + 1)){  // 如果遇到了<title>标签
                    static int titlepos=0;
                    String_Ref title = read_ElementText(ref, x);  // 从标签中读取文本内容
                    QString tmp=get_Information(title);
                    alltitle.append(tmp);
                    QString filtered = filter_Non_Punctuation(tmp);
                    QStringList words = filtered.split(" ", Qt::SkipEmptyParts);
                    for (const QString& word : words) {keypos[lemma(word)].append(titlepos); }
                    titlepos++;
                }
            }
            ++x;
        }
        title_flag=1;
        delete[] p_data;
        m_costMsecs = m_timing.elapsed();
        emit state_Changed(tr("标题分析完成. 总共耗时: %1").arg(Util::formatTime(m_costMsecs)));
        emit done();
    }

}

void Parse::parse_KeyWord(){
    QSet<QString> stopWords = { "for","in","of","on","to","an","us","with","de","and","the","by",
                               "from","as","without","towards","using","or","but","a","based","w"};
    if(key_flag==0){
        m_timing.start();
        emit state_Changed(tr("关键词统计开始."));

        QFile file(m_fileName);
        file.open(QFile::ReadOnly);

        p_data = new char[static_cast<quint64>(file.size())];// 从文件中读取数据到字符数组s_data中
        quint32 len = static_cast<quint32>(file.read(p_data, file.size()));
        String_Ref ref(0, len);  // 根据读取的数据创建一个StringRef对象
        file.close();  // 关闭文件
        unordered_map<int,QVector<QString>>keyWordIndex;
        emit state_Changed(tr("成功读取xml文件."));  // 发射状态变化信号，用于通知XML文件读取成功
        quint32 x = 0;

        while(x < len){
            if(ref[x] == '<'){
                if(ref.start_With("title",x+1)){
                    String_Ref title = read_ElementText(ref, x);  // 读取文本内容
                    QString tmptitle=get_Information(title);
                    QString filtered = filter_Non_Punctuation(tmptitle);
                    QStringList words = filtered.split(" ", Qt::SkipEmptyParts);
                    x++;
                    while(ref[x]!='<'|| !ref.start_With("year",x+1))x++;
                    String_Ref tmpyear = read_ElementText(ref, x);
                    int year=get_Information(tmpyear).toInt();
                    for (const QString& word : words) {
                        QString lowercaseWord = word.toLower(); // 将单词转换为小写
                        if(stopWords.find(lowercaseWord) == stopWords.end())
                            keyWordIndex[year].push_back((lowercaseWord));
                        if(keyWordIndex[year].size()%1000000==1)qDebug()<<lowercaseWord;
                    }
                }
            }
            ++x;
        }
        map<int, QVector<QString>> sortedKeyWordIndex(keyWordIndex.begin(), keyWordIndex.end());
        for (const auto& pair : sortedKeyWordIndex) {
            int year = pair.first;  // 获取年份
            const QVector<QString>& keywords = pair.second;  // 获取该年份对应的所有关键词
            // 使用 unordered_map 统计每个关键词的出现次数
            std::unordered_map<QString, int> keywordCount;
            for (const QString& keyword : keywords) {
                keywordCount[keyword]++;
                year_Keyword_Count_Map[year][keyword]++;
            }

            QVector<QPair<int, QString>> keywordcount_vector;
            // 将统计结果转换为 Qvector 以便排序
            for (const auto& countPair : keywordCount) {
                keywordcount_vector.push_back(std::make_pair(countPair.second, countPair.first));
            }

            // 对关键词按频率进行排序
            std::sort(keywordcount_vector.rbegin(), keywordcount_vector.rend());

            // 输出每年的前十名关键词
            int count = 0;
            for (const auto& countPair : keywordcount_vector) {
                if (count < 10) {
                    emit state_Changed(tr("年份:%1 No.%2 关键词: %3 count: %4 <br/>")
                                           .arg(year).arg(count + 1).arg(countPair.second).arg(countPair.first));
                    count++;
                } else {
                    break;
                }
            }
        }
        key_flag=1;
        delete[] p_data;

        m_costMsecs = m_timing.elapsed();
        emit state_Changed(tr("关键词统计完毕. 总共耗时: %1").arg(Util::formatTime(m_costMsecs)));  // 发射状态变化信号，用于通知解析完成，并附带所花费的时间信息
        emit done();
    }
    else if (key_flag == 1) {
        // 在需要输出时遍历 yearKeywordCountMap 输出每年的前十个关键词
        for (auto& yearKeywords : year_Keyword_Count_Map) {
            int year = yearKeywords.first;
            std::unordered_map<QString, int>& keywords = yearKeywords.second;

            // 将 keywords 转换为 vector 以便排序
            std::vector<std::pair<int, QString>> countVector;
            for (const auto& countPair : keywords) {
                countVector.push_back(std::make_pair(countPair.second, countPair.first));
            }

            // 对关键词按频率进行排序
            std::sort(countVector.rbegin(), countVector.rend());

            // 输出每年的前十名关键词
            int cou = 0;
            for (const auto& countPair : countVector) {
                if (cou < 10) {
                    emit state_Changed(tr("年份: %1 No.%2 关键词: %3 数量: %4 <br/>")
                                           .arg(year).arg(cou + 1).arg(countPair.second).arg(countPair.first));
                    cou++;
                } else {
                    break;
                }
            }
        }
        emit done();
    }

}


void Parse::parse()
{
    m_timing.start();
    emit state_Changed(tr("开始分析文件."));

    QFile file(m_fileName);
    file.open(QFile::ReadOnly);

    // 从文件中读取数据到字符数组s_data中
    p_data = new char[static_cast<quint64>(file.size())];
    quint32 len = static_cast<quint32>(file.read(p_data, file.size()));
    String_Ref ref(0, len);  // 根据读取的数据创建一个StringRef对象
    file.close();  // 关闭文件
    emit state_Changed(tr("成功读取xml文件."));  // 发射状态变化信号，用于通知XML文件读取成功

    QVector<String_Ref> authorIndex;  // 用于存储作者索引的容器
    QVector<String_Ref> titleIndex;   // 用于存储标题索引的容器
    QVector<String_Ref> keyIndex;   // 用于存储key索引的容器
    quint32 x = 0;
    while(x < len){
        if(ref[x] == '<'){
            if(ref.start_With("author", x + 1)){  // 如果遇到了<author>标签
                String_Ref author = read_ElementText(ref, x);  // 从标签中读取文本内容
                authorIndex.append(author);
            }else if(ref.start_With("title", x + 1)){
                String_Ref title = read_ElementText(ref, x);
                titleIndex.append(title);
            }
        }
        else if(ref[x]=='k'){
            if(ref.start_With("key=",x)){
                String_Ref key = read_KeyElementText(ref, x);  // 读取文本内容
                keyIndex.append(key);  // 将读取的关键词信息添加到关键词索引容器中;
            }
        }
        ++x;
    }

    emit state_Changed(tr("成功分析xml文件."));
    int m1 = m_timing.elapsed();
    emit state_Changed(tr("xml文件分析耗时: %1").arg(Util::formatTime(m1)));

    emit state_Changed(tr("正在整理索引文件"));
    std::sort(authorIndex.begin(), authorIndex.end());
    std::sort(titleIndex.begin(), titleIndex.end());
    std::sort(keyIndex.begin(), keyIndex.end());
    int m2 = m_timing.elapsed();
    emit state_Changed(tr("排序索引耗时: %1").arg(Util::formatTime(m2-m1)));

    emit state_Changed(tr("已产生索引."));
    emit state_Changed(tr("已保存索引……"));
    delete[] p_data;

    // 写入作者索引到文件author.dat中
    file.setFileName("author.dat");
    QDataStream stream(&file);
    file.open(QFile::WriteOnly);
    foreach(auto i, authorIndex){
        stream << i.l << i.r;
    }
    file.close();

    // 写入标题索引到文件title.dat中
    file.setFileName("title.dat");
    stream.setDevice(&file);
    file.open(QFile::WriteOnly);
    foreach(auto j, titleIndex){
        stream << j.l << j.r;
    }
    file.close();

    // 写入标题索引到文件key.dat中
    file.setFileName("key.dat");
    stream.setDevice(&file);
    file.open(QFile::WriteOnly);
    foreach(auto i, keyIndex){
        stream << i.l << i.r;
    }
    file.close();

    emit state_Changed(tr("已保存索引."));

    m_costMsecs = m_timing.elapsed();
    emit state_Changed(tr("分析完成. 总共耗时: %1").arg(Util::formatTime(m_costMsecs)));
    emit done();
}

void Parse::clear_Index()
{
    QFile("author.dat").remove();
    QFile("title.dat").remove();
    QFile("key.dat").remove();
}

//关于String_Ref类函数的实现

char &Parse::String_Ref::operator[](quint32 x) const
{
    //返回第x个字符
    return p_data[l + x];
}

bool Parse::String_Ref::operator<(const Parse::String_Ref &s) const
{
    quint32 len = r - l;
    //比较当前对象与引用对象的长度，取小值
    if(s.r - s.l < len) len = s.r - s.l;
    // 逐个比较当前对象和引用的字符，如果遇到不同的字符则返回对应位置字符的大小比较结果
    for(quint32 j = 0; j < len; j++){
        if(p_data[l + j] != p_data[s.l + j]){
            return p_data[l + j] < p_data[s.l + j];
        }
    }
    // 如果前len个字符相等，则返回长度较短的字符串
    if(len == s.r - s.l) return false;
    else return true;
}

Parse::String_Ref Parse::String_Ref::midd(quint32 pos) const
{
    //返回从pos开始到尾部的字符串
    return String_Ref(l + pos, r);
}

Parse::String_Ref Parse::String_Ref::midd(quint32 pos, quint32 len) const
{
    //返回pos到pos+len的字符串
    return String_Ref(l + pos, l + pos + len);
}

bool Parse::String_Ref::start_With(const char *string, quint32 from) const
{
    quint32 x = l + from;
    // 从位置x开始逐个比较str中的字符和当前字符串中的字符，如果有不同的则返回false，如果x溢出则返回false
    while(*string != 0){
        if(*string != p_data[x]) return false;
        ++string;
        ++x;
        if(x >= r) return false;
    }
    return true;
}

qint32 Parse::String_Ref::index_Of(const char *string, quint32 from) const
{
    for(quint32 t = l + from; t < r; ++t){
        bool flag = true;
        // 从位置t开始逐个比较str中的字符和当前字符串中的字符
        for(const char *x = string; *x != 0; ++x){
            if(*x != p_data[t + x - string]){
                flag = false;
                break;
            }
        }
        // 如果匹配成功则返回匹配位置相对于l的偏移量
        if(flag){
            return static_cast<qint32>(t - l);
        }
    }
    // 如果没有找到匹配则返回-1
    return -1;
}


// 从输入字符串中提取 XML 元素的文本内容
Parse::String_Ref Parse::read_ElementText(const Parse::String_Ref &r, quint32 &from)
{
    // 从索引 'from' 开始提取子字符串 's'
    String_Ref s = r.midd(from);

    //第一个字符为'<      '
    quint32 i = 1;
    char name[30];
    name[0] = '<';
    name[1] = '/';

    while(s[i] != ' ' && s[i] != '>'){
        name[i + 1] = s[i];
        i++;
    }
    from += i;
    name[i + 1] = '>';
    name[i + 2] = 0;
    // 'name' 存储了结束标签的内容，如 "</ele>"

    // 继续遍历子字符串 's' 直到找到结束标签的 '>'，并在子字符串 's' 中查找结束标签 'name' 的位置
    while(s[i] != '>') i++;
    qint32 p = s.index_Of(name, i + 1);
    // 计算结束标签在s字符串中的偏移，并更新 'from' 的值
    quint32 x = static_cast<quint32>(p);
    from += x + 1;
    // 返回开始标签和结束标签之间的文本内容
    return s.midd(i + 1, x - i - 1);
}

Parse::String_Ref Parse::read_KeyElementText(const Parse::String_Ref &r, quint32 &from)
{
    // 从索引 'from' 开始提取子字符串 's'
    String_Ref s = r.midd(from);
    quint32 i=0,x1,x2;
    // 从第二个字符开始，找出元素的名称，并存储在 'name' 数组中，直到遇到空格或者 '"'
    while(s[i] != '"'){
        i++;
    }
    i++;x1=i;
    while(s[i] != '"'){
        i++;
    }
    //Q_ASSERT(s[i] == '"');
    x2=i;i++;
    from += i;
    return s.midd(x1, x2-x1);
}

int Parse::read_YearElementText(const Parse::String_Ref &r, quint32 &from)
{
    // 从索引 'from' 开始提取子字符串 's'
    String_Ref s = r.midd(from);QString str="";
    quint32 i=0;
    // 从第二个字符开始，找出元素的名称，并存储在 'name' 数组中，直到遇到空格或者 '"'
    while(s[i] != '"'){
        i++;
    }
    i++;
    while(s[i] != '-'){
        str+=s[i];i++;
    }
    //Q_ASSERT(s[i] == '-');
    i++;
    from += i;
    int year=str.toInt();
    // 计算结束标签在s字符串中的偏移，并更新 'from' 的值
    // 返回开始标签和结束标签之间的文本内容
    return year;
}
