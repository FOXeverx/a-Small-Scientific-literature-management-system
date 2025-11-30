
#include "recorder.h"

#include<QDebug>
#include<QRegularExpression>
Recorder::Recorder(const QString &s,QObject *parent)
    : QObject{parent}
{

    // 使用正则表达式从字符串 s 中匹配作者的部分，存储到 m_authors 和 m_coauthors 中
    QRegularExpression re(R"(<author.*?>(.+)<\/author>)");
    auto i = re.globalMatch(s);
    //一篇DBLP文献很多作者

    while(i.hasNext()){
        QString author = i.next().captured(1);
        r_authors << author;  // 将作者添加到 m_authors 列表
        r_coauthors << author;  // 将作者添加到 m_coauthors 列表
    }

    // 从字符串 s 中匹配标题的部分，存储到 m_title 中
    re.setPattern(R"(<title.*?>(.+)<\/title>)");
    auto m = re.match(s);
    if(m.hasMatch())
        r_title = m.captured(1);

    // 从字符串 s 中匹配日期的部分，存储到 m_mdate 中
    re.setPattern(R"#(mdate\s*=\s*"((?:\d{4})-(?:\d{2})-(?:\d{2}))")#");
    m = re.match(s);
    if(m.hasMatch())
        r_mdate = m.captured(1);

    // 从字符串 s 中匹配类型的部分，存储到 m_name 中
    re.setPattern(R"(<(article|inproceedings|proceedings|book|incollection|phdthesis|mastersthesis|www|person|data))");
    m = re.match(s);
    if(m.hasMatch())
        r_name = m.captured(1);

    // 从字符串 s 中匹配关键字的部分，存储到 m_key 中
    re.setPattern(R"#(key="(.*?)")#");
    m = re.match(s);
    if(m.hasMatch())
        r_key = m.captured(1);

    re.setPattern(R"(<publisher.*?>(.+)<\/publisher>)");
    m = re.match(s);
    r_publisher = m.captured(1);
}
void Recorder::clearCoauthors()
{
    r_coauthors.clear();
}
