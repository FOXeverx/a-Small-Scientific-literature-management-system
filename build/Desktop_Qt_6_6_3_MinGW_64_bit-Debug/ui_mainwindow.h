/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *a_Help;
    QAction *a_Open;
    QAction *a_Exit;
    QAction *a_Clear;
    QAction *a_AuthorCount;
    QAction *a_FuzzyOpen;
    QAction *a_GroupAnalyze;
    QAction *a_KeyWordCount;
    QAction *a_Status;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *LabelBox;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *b_Key;
    QRadioButton *b_Author;
    QRadioButton *b_Title;
    QRadioButton *b_Coauthor;
    QRadioButton *b_Fuzzy;
    QStackedWidget *stackedWidget;
    QWidget *authorPage;
    QTableWidget *Table_1;
    QWidget *titlePage;
    QLabel *Label;
    QWidget *coauthorPage;
    QTextBrowser *Browser;
    QWidget *fuzzyPage;
    QTableWidget *Table_2;
    QHBoxLayout *TextLine;
    QLineEdit *lineEdit;
    QCheckBox *fuzzy;
    QPushButton *Search;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuFunction;
    QMenu *menuHelp;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(825, 602);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/nicon/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("background-image: url(:/nicon/DailyBing-zh-cn-20250519-FHD.jpg);"));
        MainWindow->setTabShape(QTabWidget::Triangular);
        a_Help = new QAction(MainWindow);
        a_Help->setObjectName("a_Help");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/nicon/help_filled.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_Help->setIcon(icon1);
        a_Open = new QAction(MainWindow);
        a_Open->setObjectName("a_Open");
        a_Open->setCheckable(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/nicon/store.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_Open->setIcon(icon2);
        a_Exit = new QAction(MainWindow);
        a_Exit->setObjectName("a_Exit");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/nicon/close.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_Exit->setIcon(icon3);
        a_Clear = new QAction(MainWindow);
        a_Clear->setObjectName("a_Clear");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/nicon/ashbin.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_Clear->setIcon(icon4);
        a_AuthorCount = new QAction(MainWindow);
        a_AuthorCount->setObjectName("a_AuthorCount");
        a_AuthorCount->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/nicon/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_AuthorCount->setIcon(icon5);
        a_FuzzyOpen = new QAction(MainWindow);
        a_FuzzyOpen->setObjectName("a_FuzzyOpen");
        a_FuzzyOpen->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/nicon/flow.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_FuzzyOpen->setIcon(icon6);
        a_GroupAnalyze = new QAction(MainWindow);
        a_GroupAnalyze->setObjectName("a_GroupAnalyze");
        a_GroupAnalyze->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/nicon/sub_account.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_GroupAnalyze->setIcon(icon7);
        a_KeyWordCount = new QAction(MainWindow);
        a_KeyWordCount->setObjectName("a_KeyWordCount");
        a_KeyWordCount->setCheckable(true);
        a_KeyWordCount->setChecked(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/nicon/count.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_KeyWordCount->setIcon(icon8);
        a_Status = new QAction(MainWindow);
        a_Status->setObjectName("a_Status");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/nicon/checksearch.png"), QSize(), QIcon::Normal, QIcon::Off);
        a_Status->setIcon(icon9);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(-1, -1, -1, 5);
        LabelBox = new QGroupBox(centralwidget);
        LabelBox->setObjectName("LabelBox");
        LabelBox->setEnabled(true);
        LabelBox->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_5 = new QHBoxLayout(LabelBox);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        b_Key = new QRadioButton(LabelBox);
        b_Key->setObjectName("b_Key");

        horizontalLayout_5->addWidget(b_Key);

        b_Author = new QRadioButton(LabelBox);
        b_Author->setObjectName("b_Author");

        horizontalLayout_5->addWidget(b_Author, 0, Qt::AlignLeft);

        b_Title = new QRadioButton(LabelBox);
        b_Title->setObjectName("b_Title");

        horizontalLayout_5->addWidget(b_Title);

        b_Coauthor = new QRadioButton(LabelBox);
        b_Coauthor->setObjectName("b_Coauthor");

        horizontalLayout_5->addWidget(b_Coauthor);

        b_Fuzzy = new QRadioButton(LabelBox);
        b_Fuzzy->setObjectName("b_Fuzzy");

        horizontalLayout_5->addWidget(b_Fuzzy);


        gridLayout->addWidget(LabelBox, 3, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        stackedWidget->setAutoFillBackground(false);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        authorPage = new QWidget();
        authorPage->setObjectName("authorPage");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(authorPage->sizePolicy().hasHeightForWidth());
        authorPage->setSizePolicy(sizePolicy1);
        Table_1 = new QTableWidget(authorPage);
        if (Table_1->columnCount() < 5)
            Table_1->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Table_1->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Table_1->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Table_1->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Table_1->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        Table_1->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        Table_1->setObjectName("Table_1");
        Table_1->setGeometry(QRect(0, 0, 811, 391));
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(Table_1->sizePolicy().hasHeightForWidth());
        Table_1->setSizePolicy(sizePolicy2);
        Table_1->setMinimumSize(QSize(811, 0));
        Table_1->setAutoFillBackground(true);
        Table_1->horizontalHeader()->setCascadingSectionResizes(true);
        Table_1->horizontalHeader()->setStretchLastSection(true);
        Table_1->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_1->verticalHeader()->setStretchLastSection(true);
        stackedWidget->addWidget(authorPage);
        titlePage = new QWidget();
        titlePage->setObjectName("titlePage");
        Label = new QLabel(titlePage);
        Label->setObjectName("Label");
        Label->setGeometry(QRect(0, 0, 801, 391));
        sizePolicy.setHeightForWidth(Label->sizePolicy().hasHeightForWidth());
        Label->setSizePolicy(sizePolicy);
        stackedWidget->addWidget(titlePage);
        coauthorPage = new QWidget();
        coauthorPage->setObjectName("coauthorPage");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(coauthorPage->sizePolicy().hasHeightForWidth());
        coauthorPage->setSizePolicy(sizePolicy3);
        Browser = new QTextBrowser(coauthorPage);
        Browser->setObjectName("Browser");
        Browser->setGeometry(QRect(0, 10, 801, 391));
        sizePolicy1.setHeightForWidth(Browser->sizePolicy().hasHeightForWidth());
        Browser->setSizePolicy(sizePolicy1);
        stackedWidget->addWidget(coauthorPage);
        fuzzyPage = new QWidget();
        fuzzyPage->setObjectName("fuzzyPage");
        sizePolicy3.setHeightForWidth(fuzzyPage->sizePolicy().hasHeightForWidth());
        fuzzyPage->setSizePolicy(sizePolicy3);
        Table_2 = new QTableWidget(fuzzyPage);
        if (Table_2->columnCount() < 3)
            Table_2->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Table_2->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        Table_2->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        Table_2->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        Table_2->setObjectName("Table_2");
        Table_2->setGeometry(QRect(0, 0, 801, 401));
        sizePolicy1.setHeightForWidth(Table_2->sizePolicy().hasHeightForWidth());
        Table_2->setSizePolicy(sizePolicy1);
        Table_2->setAutoFillBackground(true);
        Table_2->horizontalHeader()->setCascadingSectionResizes(true);
        Table_2->horizontalHeader()->setStretchLastSection(true);
        Table_2->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        Table_2->verticalHeader()->setStretchLastSection(true);
        stackedWidget->addWidget(fuzzyPage);

        gridLayout->addWidget(stackedWidget, 2, 0, 1, 1);

        TextLine = new QHBoxLayout();
        TextLine->setObjectName("TextLine");
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMaximumSize(QSize(16777215, 25));
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        TextLine->addWidget(lineEdit);

        fuzzy = new QCheckBox(centralwidget);
        fuzzy->setObjectName("fuzzy");

        TextLine->addWidget(fuzzy);

        Search = new QPushButton(centralwidget);
        Search->setObjectName("Search");
        Search->setMinimumSize(QSize(100, 25));
        Search->setMaximumSize(QSize(16777215, 25));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        Search->setIcon(icon10);

        TextLine->addWidget(Search);


        gridLayout->addLayout(TextLine, 4, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 825, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuFunction = new QMenu(menubar);
        menuFunction->setObjectName("menuFunction");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setContextMenuPolicy(Qt::CustomContextMenu);
        toolBar->setStyleSheet(QString::fromUtf8("color: rgb(100,100, 200);"));
        toolBar->setIconSize(QSize(30, 30));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuFunction->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(a_Open);
        menuFile->addAction(a_Status);
        menuFile->addAction(a_Exit);
        menuFunction->addAction(a_Clear);
        menuFunction->addAction(a_AuthorCount);
        menuFunction->addAction(a_FuzzyOpen);
        menuFunction->addAction(a_GroupAnalyze);
        menuFunction->addAction(a_KeyWordCount);
        menuHelp->addAction(a_Help);
        toolBar->addAction(a_Open);
        toolBar->addAction(a_Status);
        toolBar->addAction(a_Clear);
        toolBar->addAction(a_FuzzyOpen);
        toolBar->addAction(a_AuthorCount);
        toolBar->addAction(a_GroupAnalyze);
        toolBar->addAction(a_KeyWordCount);
        toolBar->addAction(a_Help);
        toolBar->addAction(a_Exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\226\207\347\214\256\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        a_Help->setText(QCoreApplication::translate("MainWindow", "\344\275\277\347\224\250\345\270\256\345\212\251", nullptr));
        a_Open->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        a_Exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        a_Clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\226\207\344\273\266", nullptr));
        a_AuthorCount->setText(QCoreApplication::translate("MainWindow", "\344\275\234\350\200\205\347\273\237\350\256\241", nullptr));
        a_FuzzyOpen->setText(QCoreApplication::translate("MainWindow", "\346\250\241\347\263\212\345\214\271\351\205\215", nullptr));
        a_GroupAnalyze->setText(QCoreApplication::translate("MainWindow", "\350\201\232\345\233\242\345\210\206\346\236\220", nullptr));
        a_KeyWordCount->setText(QCoreApplication::translate("MainWindow", "\347\203\255\350\257\215\347\273\237\350\256\241", nullptr));
        a_Status->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\347\212\266\346\200\201", nullptr));
        LabelBox->setTitle(QCoreApplication::translate("MainWindow", "\347\264\242\345\274\225\357\274\232", nullptr));
        b_Key->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\224\256\350\257\215", nullptr));
        b_Author->setText(QCoreApplication::translate("MainWindow", "\344\275\234\350\200\205", nullptr));
        b_Title->setText(QCoreApplication::translate("MainWindow", "\351\242\230\347\233\256", nullptr));
        b_Coauthor->setText(QCoreApplication::translate("MainWindow", "\345\220\210\350\221\227\350\200\205", nullptr));
        b_Fuzzy->setText(QCoreApplication::translate("MainWindow", "\346\250\241\347\263\212\346\220\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Table_1->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\346\240\207\351\242\230", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Table_1->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\344\275\234\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Table_1->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\220\216\344\277\256\346\224\271\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Table_1->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\345\207\272\347\211\210\347\244\276", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = Table_1->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\224\256\350\257\215", nullptr));
        Label->setText(QString());
        QTableWidgetItem *___qtablewidgetitem5 = Table_2->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = Table_2->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Modify Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = Table_2->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        fuzzy->setText(QCoreApplication::translate("MainWindow", "\346\250\241\347\263\212\346\220\234\347\264\242", nullptr));
        Search->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        menuFunction->setTitle(QCoreApplication::translate("MainWindow", "\345\212\237\350\203\275", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
