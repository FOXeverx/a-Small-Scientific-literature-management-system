#ifndef FIND_H
#define FIND_H

#include <QObject>
#include "parse.h"
#include "recorder.h"
#include "util.h"

class Find : public QObject
{
    Q_OBJECT
public:
    explicit Find(QObject *parent = nullptr);
    static void initializeIndex();
    static bool isIndexParsed();
    static void clearIndex();
    QList<quint32> findAuthorIndices(const QString &author) const;
    QList<quint32> findTitleIndices(const QString &title) const;
    QList<quint32> findKeywordIndices(const QString &keyword) const;

private:
    static QFile *dataFile;
    static Parse::String_Ref *authorIndices;
    static Parse::String_Ref *titleIndices;
    static Parse::String_Ref *keywordIndices;
    static quint32 authorIndexCount;
    static quint32 titleIndexCount;
    static quint32 keywordIndexCount;

    static QString readIndexContent(const Parse::String_Ref &ref);
    static QPair<const Parse::String_Ref*, const Parse::String_Ref*>
    findEqualRange(const Parse::String_Ref *first,
                   const Parse::String_Ref *last,
                   const QString &value);
    static const Parse::String_Ref*
    findLowerBound(const Parse::String_Ref *first,
                   const Parse::String_Ref *last,
                   const QString &value);
    static const Parse::String_Ref*
    findUpperBound(const Parse::String_Ref *first,
                   const Parse::String_Ref *last,
                   const QString &value);
};

#endif // FIND_H
