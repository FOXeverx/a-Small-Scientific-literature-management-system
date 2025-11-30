#ifndef PARSE_H
#define PARSE_H

#include <QThread>
#include <QMap>
#include <QTime>
#include <QXmlStreamReader>
#include <QDebug>
#include <QElapsedTimer>
#include "util.h"
#include "pivoter.h"

class QFile;
QString filter_Non_Punctuation(QString str);
class Parse : public QThread
{
    Q_OBJECT
public:
    Parse(QObject *parent = nullptr);
    QString fileName() const { return m_fileName; }
    int cost_sec() { return m_costMsecs; }
    void run() override;
    void parse();
    void parse_Author();
    void parse_Title();
    void parse_AuthorGroup();
    void parse_KeyWord();
    void set_FileName(const QString &fileName) { m_fileName = fileName; }
    int condi;
    int author_flag, title_flag, group_flag, key_flag;
    QVector<QPair<int, QString>> author_count;
    std::unordered_map<int, std::unordered_map<QString, int>> year_Keyword_Count_Map;
    static void clear_Index();

signals:
    void state_Changed(QString state);
    void done();

private:
    static char *p_data;

public:
    struct String_Ref {
        quint32 l, r;
        String_Ref() {}
        String_Ref(quint32 l_, quint32 r_) : l(l_), r(r_) {}

        // 获取引用中位置 x 处的字符
        char &operator[](quint32 x) const;

        // 比较 String_Ref 大小
        bool operator<(const String_Ref &s) const;

        // 获取引用从位置 'posi' 开始到末尾的子串
        String_Ref midd(quint32 posi) const;

        // 获取引用从位置 'pos' 开始指定长度为 'len' 的子串
        String_Ref midd(quint32 posi, quint32 length) const;

        // 检查引用是否以给定子串从指定位置 'from' 开始
        bool start_With(const char *str, quint32 from = 0) const;

        // 在引用中从指定位置 'from' 开始查找给定子串的索引
        qint32 index_Of(const char *str, quint32 from = 0) const;
    };

    friend QDebug operator<<(QDebug debug, const String_Ref &s) {
        debug << QByteArray::fromRawData(p_data + s.l, static_cast<int>(s.r - s.l));
        return debug;
    }

    friend QString get_Information(String_Ref s) {
        return QString::fromUtf8(p_data + s.l, static_cast<int>(s.r - s.l));
    }

    QHash<QString, int> authorList;
    QVector<double> clique;

    class My_Priority_Queue {
    public:
        void push_in(const QPair<QString, int>& val) {
            data.push_back(val);
            std::push_heap(data.begin(), data.end(), compare);
        }
        void pop_out() {
            std::pop_heap(data.begin(), data.end(), compare);
            data.pop_back();
        }
        QPair<QString, int> get_top() const { return data.front(); }
        size_t get_size() const { return data.size(); }
    private:
        struct Comp {
            bool operator()(const QPair<QString, int>& a, const QPair<QString, int>& b) const {
                return a.second > b.second;
            }
        } compare;
        QVector<QPair<QString, int>> data;
    };

    struct Trie_Node {
        std::unordered_map<QChar, Trie_Node*> children_word;
        bool isEnd;
        int count;
        Trie_Node() : isEnd(false), count(0) {}
    };

    class Trie {
    public:
        Trie() : root(new Trie_Node()) {}
        void insert(const QString& word) {
            QString lower = word.toLower();
            Trie_Node* curr = root;
            for (QChar ch : lower) {
                if (!curr->children_word[ch])
                    curr->children_word[ch] = new Trie_Node();
                curr = curr->children_word[ch];
            }
            curr->isEnd = true;
            curr->count++;
        }
        int get_Word_Frequency(const QString& word) {
            Trie_Node* curr = root;
            for (QChar ch : word) {
                if (!curr->children_word[ch]) return 0;
                curr = curr->children_word[ch];
            }
            return curr->isEnd ? curr->count : 0;
        }
        QVector<QPair<QString, int>> top_Ten_Words() {
            My_Priority_Queue heap;
            topTenHelper(root, "", heap);
            QVector<QPair<QString, int>> res;
            while (heap.get_size() > 0) {
                res.push_back(heap.get_top());
                heap.pop_out();
            }
            return res;
        }
    private:
        Trie_Node* root;
        void topTenHelper(Trie_Node* node, QString word, My_Priority_Queue& heap) {
            if (!node) return;
            if (node->isEnd) {
                heap.push_in({word, node->count});
                if (heap.get_size() > 10) heap.pop_out();
            }
            for (auto& child : node->children_word)
                topTenHelper(child.second, word + child.first, heap);
        }
    };

private:
    QString m_fileName;
    int m_costMsecs;
    QElapsedTimer m_timing;

    static String_Ref read_ElementText(const String_Ref &r, quint32 &from);
    static String_Ref read_KeyElementText(const String_Ref &r, quint32 &from);
    static int read_YearElementText(const String_Ref &r, quint32 &from);
};

extern QVector<QString> alltitle;
extern std::unordered_map<QString, QVector<int>> keypos;
extern Graph* g;
#endif

