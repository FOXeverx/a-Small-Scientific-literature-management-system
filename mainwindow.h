#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "find.h"
#include "parse.h"
#include "settingdialog.h"
#include "Progresswindow.h"
#include "util.h"
#include "recorder.h"
#include "porter_stemming.h"

#include <QMainWindow>
#include <QThread>

class Parser;
class ParserDialog;
class Finder;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Resize(QResizeEvent* event) ;
    QStringList wordList;
    QString previousText;
private slots:
    void FuzzyChanged();

    //查询按钮
    void on_Search_clicked();
    //作者统计动作
    void on_a_AuthorCount_triggered();
    //打开动作
    void on_a_Open_triggered();
    //退出动作
    void on_a_Exit_triggered();
    //关于帮助
    void on_a_Help_triggered();
    //清除索引动作
    void on_a_Clear_triggered();
    //状态动作
    void on_a_Status_triggered();
    //聚团分析动作
    void on_a_GroupAnalyze_triggered();
    //关键词统计动作
    void on_a_KeyWordCount_triggered();
    //模糊搜索开启动作
    void on_a_FuzzyOpen_triggered();
    //作者按钮
    void on_b_Author_clicked();
    //共同作者按钮
    void on_b_Coauthor_clicked();
    //标题按钮
    void on_b_Title_clicked();
    //按关键词key搜索按钮
    void on_b_Key_clicked();
    //模糊搜索按钮
    void on_b_Fuzzy_clicked();

private:
    Ui::MainWindow *ui;
    Parse *main_parser;
    Find *main_finder;
    QTimer *searchTimer;
};
#endif // MAINWINDOW_H
