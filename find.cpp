#include "find.h"
#include <QFile>
#include <QDataStream>
#include <QSettings>

std::unordered_map<QString, int> authorFrequencyMap;
Parse::String_Ref *Find::authorIndices = nullptr;
Parse::String_Ref *Find::titleIndices = nullptr;
Parse::String_Ref *Find::keywordIndices = nullptr;
quint32 Find::authorIndexCount = 0;
quint32 Find::titleIndexCount = 0;
quint32 Find::keywordIndexCount = 0;
QFile *Find::dataFile = nullptr;

Find::Find(QObject *parent) : QObject(parent) {}

bool Find::isIndexParsed()
{
    return QFile("author.dat").exists() &&
           QFile("title.dat").exists() &&
           QFile("key.dat").exists();
}

void Find::clearIndex()
{
    delete[] authorIndices;
    delete[] titleIndices;
    delete[] keywordIndices;
    authorIndices = titleIndices = keywordIndices = nullptr;
}

QList<quint32> Find::findAuthorIndices(const QString &author) const
{
    QList<quint32> results;
    if(!authorIndices) return results;

    auto range = findEqualRange(authorIndices, authorIndices + authorIndexCount, author);
    for(auto it = range.first; it != range.second; ++it) {
        results.append(it->l);
    }
    return results;
}

QList<quint32> Find::findTitleIndices(const QString &title) const
{
    QList<quint32> results;
    if(!titleIndices) return results;

    auto range = findEqualRange(titleIndices, titleIndices + titleIndexCount, title);
    for(auto it = range.first; it != range.second; ++it) {
        results.append(it->l);
    }
    return results;
}

QList<quint32> Find::findKeywordIndices(const QString &keyword) const
{
    QList<quint32> results;
    if(!keywordIndices) return results;

    auto range = findEqualRange(keywordIndices, keywordIndices + keywordIndexCount, keyword);
    for(auto it = range.first; it != range.second; ++it) {
        results.append(it->l);
    }
    return results;
}

QString Find::readIndexContent(const Parse::String_Ref &ref)
{
    dataFile->seek(ref.l);
    return dataFile->read(ref.r - ref.l);
}

void Find::initializeIndex()
{
    if(!isIndexParsed()) return;

    // 读取 author
    QFile file("author.dat");
    file.open(QFile::ReadOnly);
    QDataStream stream(&file);
    authorIndexCount = file.size() / sizeof(Parse::String_Ref);
    authorIndices = new Parse::String_Ref[authorIndexCount];

    for(quint32 i = 0; i < authorIndexCount; ++i) {
        stream >> authorIndices[i].l >> authorIndices[i].r;
    }
    file.close();

    // 读取 title
    file.setFileName("title.dat");
    file.open(QFile::ReadOnly);
    stream.setDevice(&file);
    titleIndexCount = file.size() / sizeof(Parse::String_Ref);
    titleIndices = new Parse::String_Ref[titleIndexCount];

    for(quint32 i = 0; i < titleIndexCount; ++i) {
        stream >> titleIndices[i].l >> titleIndices[i].r;
    }
    file.close();

    // 读取 keyword
    file.setFileName("key.dat");
    file.open(QFile::ReadOnly);
    stream.setDevice(&file);
    keywordIndexCount = file.size() / sizeof(Parse::String_Ref);
    keywordIndices = new Parse::String_Ref[keywordIndexCount];

    for(quint32 i = 0; i < keywordIndexCount; ++i) {
        stream >> keywordIndices[i].l >> keywordIndices[i].r;
    }
    file.close();

    // 初始化
    QSettings settings;
    QString dataFilePath = settings.value("lastOpenFileName").toString();
    if(dataFile) {
        dataFile->close();
        delete dataFile;
    }
    dataFile = new QFile(dataFilePath);
    dataFile->open(QFile::ReadOnly);
}

QPair<const Parse::String_Ref*, const Parse::String_Ref*>
Find::findEqualRange(const Parse::String_Ref *first,
                     const Parse::String_Ref *last,
                     const QString &value)
{
    quint32 length = last - first;
    while(length > 0) {
        quint32 half = length >> 1;
        const Parse::String_Ref *mid = first + half;
        QString midText = readIndexContent(*mid);

        if(midText < value) {
            first = mid + 1;
            length -= half + 1;
        } else if(midText > value) {
            length = half;
        } else {
            auto left = findLowerBound(first, mid, value);
            auto right = findUpperBound(mid + 1, first + length, value);
            return {left, right};
        }
    }
    return {first, first};
}

const Parse::String_Ref*
Find::findLowerBound(const Parse::String_Ref *first,
                     const Parse::String_Ref *last,
                     const QString &value)
{
    quint32 length = last - first;
    while(length > 0) {
        quint32 half = length >> 1;
        const Parse::String_Ref *mid = first + half;
        QString midText = readIndexContent(*mid);

        if(midText < value) {
            first = mid + 1;
            length -= half + 1;
        } else {
            length = half;
        }
    }
    return first;
}

const Parse::String_Ref*
Find::findUpperBound(const Parse::String_Ref *first,
                     const Parse::String_Ref *last,
                     const QString &value)
{
    quint32 length = last - first;
    while(length > 0) {
        quint32 half = length >> 1;
        const Parse::String_Ref *mid = first + half;
        QString midText = readIndexContent(*mid);

        if(value < midText) {
            length = half;
        } else {
            first = mid + 1;
            length -= half + 1;
        }
    }
    return first;
}
