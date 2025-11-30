/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingdialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *settingListWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_Language;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QComboBox *comboBox;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *settingdialog)
    {
        if (settingdialog->objectName().isEmpty())
            settingdialog->setObjectName("settingdialog");
        settingdialog->resize(466, 300);
        verticalLayout = new QVBoxLayout(settingdialog);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        settingListWidget = new QListWidget(settingdialog);
        new QListWidgetItem(settingListWidget);
        settingListWidget->setObjectName("settingListWidget");

        horizontalLayout->addWidget(settingListWidget);

        stackedWidget = new QStackedWidget(settingdialog);
        stackedWidget->setObjectName("stackedWidget");
        page_Language = new QWidget();
        page_Language->setObjectName("page_Language");
        formLayoutWidget = new QWidget(page_Language);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(9, 9, 281, 251));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(formLayoutWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setInsertPolicy(QComboBox::NoInsert);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        stackedWidget->addWidget(page_Language);

        horizontalLayout->addWidget(stackedWidget);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(settingdialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(settingdialog);

        QMetaObject::connectSlotsByName(settingdialog);
    } // setupUi

    void retranslateUi(QDialog *settingdialog)
    {
        settingdialog->setWindowTitle(QCoreApplication::translate("settingdialog", "Dialog", nullptr));

        const bool __sortingEnabled = settingListWidget->isSortingEnabled();
        settingListWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = settingListWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("settingdialog", "Language", nullptr));
        settingListWidget->setSortingEnabled(__sortingEnabled);

        comboBox->setItemText(0, QCoreApplication::translate("settingdialog", "System", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("settingdialog", "English", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("settingdialog", "Chinese", nullptr));

        label->setText(QCoreApplication::translate("settingdialog", "Language", nullptr));
    } // retranslateUi

};

namespace Ui {
    class settingdialog: public Ui_settingdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
