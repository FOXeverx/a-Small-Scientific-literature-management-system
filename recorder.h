#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>

class Recorder : public QObject
{
    Q_OBJECT
public:
    explicit Recorder(const QString &s,QObject *parent = nullptr);
    QString name() const{return r_name;}
    QString key() const{return r_key;}
    QString mdate() const{return r_mdate;}
    QStringList authors() const{return r_authors;}
    QString title() const{return r_title;}
    QString publisher() const{return r_publisher;}
    QStringList coauthors() const{return r_coauthors;}

    void clearCoauthors();

private:
    QString r_name;
    QString r_publisher;
    QString r_key;
    QString r_mdate;
    QStringList r_authors;
    QString r_title;
    QStringList r_coauthors;
signals:
};

#endif // RECORDER_H
