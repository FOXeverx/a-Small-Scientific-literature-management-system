#include "util.h"
#include <QTime>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>


Util::Util(QObject *parent)
    : QObject{parent}
{}
//转换为可读时间
QString Util::formatTime(int ms)
{
    //Q_ASSERT(ms >= 0);
    QTime time = QTime::fromMSecsSinceStartOfDay(ms);
    if(time.hour() == 0){
        if(time.minute() == 0){
            return time.toString("s.zzz ")+tr("s");
        }else{
            return time.toString("m:ss.z");
        }
    }else{
        return time.toString("H:mm:ss");
    }
}

//阅读指定位置前后3000个字节
QString Util::readAround(const QString &fileName, quint32 &pos)
{
     // 根据给定的文件名创建一个 QFile 对象
    QFile file(fileName);
    file.open(QFile::ReadOnly | QFile::Text);


    // 根据指定的位置，从文件中读取数据
    if(pos < BUF_SZ){
        file.seek(0);
    }else{
        file.seek(pos - BUF_SZ);
        pos = BUF_SZ;
    }
    QString data = file.read(BUF_SZ << 1);
    file.close();
    return data;
}

QString Util::findRecord(const QString &fileName, quint32 pos)
{

    QString data = readAround(fileName, pos); // 从文件中读取一定范围的数据
    // 创建正则表达式用于匹配特定格式的记录
    QRegularExpression re(R"(<\/(article|inproceedings|proceedings|book|incollection|phdthesis|mastersthesis|www|person|data)>)");
    auto m = re.match(data, static_cast<int>(pos));// 在数据中搜索匹配正则表达式的内容

    QString name = m.captured(1);//捕获第一个表达式内容，也就是"article""book"之类的，用于匹配开头标记
    int endPos = m.capturedEnd(1) + 1;// 获取匹配项的结束位置
    data.remove(endPos, data.size() - endPos);  // 把结束标记后面的都移除

    int beginPos = data.lastIndexOf("<" + name);  // 根据开头标记查找记录的起始位置（lastIndex确保不包含别的文章）
    return data.remove(0, beginPos);    // 移除开头标记以前的内容，返回特定文章的内容

}
