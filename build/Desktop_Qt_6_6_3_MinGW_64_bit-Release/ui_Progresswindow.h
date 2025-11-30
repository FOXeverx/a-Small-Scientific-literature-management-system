/********************************************************************************
** Form generated from reading UI file 'Progresswindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSWINDOW_H
#define UI_PROGRESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Progresswindow
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *b_close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Progresswindow)
    {
        if (Progresswindow->objectName().isEmpty())
            Progresswindow->setObjectName("Progresswindow");
        Progresswindow->resize(400, 321);
        verticalLayout = new QVBoxLayout(Progresswindow);
        verticalLayout->setObjectName("verticalLayout");
        textBrowser = new QTextBrowser(Progresswindow);
        textBrowser->setObjectName("textBrowser");

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        b_close = new QPushButton(Progresswindow);
        b_close->setObjectName("b_close");

        horizontalLayout_2->addWidget(b_close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Progresswindow);

        QMetaObject::connectSlotsByName(Progresswindow);
    } // setupUi

    void retranslateUi(QDialog *Progresswindow)
    {
        Progresswindow->setWindowTitle(QCoreApplication::translate("Progresswindow", "Progress", nullptr));
        b_close->setText(QCoreApplication::translate("Progresswindow", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Progresswindow: public Ui_Progresswindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSWINDOW_H
