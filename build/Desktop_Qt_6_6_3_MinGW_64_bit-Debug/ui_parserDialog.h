/********************************************************************************
** Form generated from reading UI file 'parserDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARSERDIALOG_H
#define UI_PARSERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_parserDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *b_close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *parserDialog)
    {
        if (parserDialog->objectName().isEmpty())
            parserDialog->setObjectName("parserDialog");
        parserDialog->resize(400, 321);
        verticalLayout = new QVBoxLayout(parserDialog);
        verticalLayout->setObjectName("verticalLayout");
        textBrowser = new QTextBrowser(parserDialog);
        textBrowser->setObjectName("textBrowser");

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        b_close = new QPushButton(parserDialog);
        b_close->setObjectName("b_close");

        horizontalLayout_2->addWidget(b_close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(parserDialog);

        QMetaObject::connectSlotsByName(parserDialog);
    } // setupUi

    void retranslateUi(QDialog *parserDialog)
    {
        parserDialog->setWindowTitle(QCoreApplication::translate("parserDialog", "Dialog", nullptr));
        b_close->setText(QCoreApplication::translate("parserDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class parserDialog: public Ui_parserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARSERDIALOG_H
