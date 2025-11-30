#include "settingdialog.h"
#include "ui_settingdialog.h"
#include<QMessageBox>
#include <QSettings>
#include <QAbstractButton>
#include <QDebug>
#include <QPushButton>
SettingDialog::SettingDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::settingdialog)
{
    ui->setupUi(this);
    ui->settingListWidget->setMaximumWidth(ui->settingListWidget->sizeHintForColumn(0) + 10);
    QSettings settings;
    if(settings.contains("language")){
        QString language = settings.value("language").toString();
        if(language == "english") ui->comboBox->setCurrentIndex(1);
        else if(language == "chinese") ui->comboBox->setCurrentIndex(2);
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

// 根据选择的索引设置不同的语言选项
void SettingDialog::applySettings()
{
    QSettings settings;
    int i = ui->comboBox->currentIndex();    // 获取下拉框中当前选择的索引
    if(i == 0)
        settings.setValue("language", "system");
    else if(i == 1)
        settings.setValue("language", "english");
    else if(i == 2)
        settings.setValue("language", "chinese");
}

// 应用设置并关闭对话框
void SettingDialog::on_buttonBox_accepted()
{
    QMessageBox::about(this, "提示", "重启窗口以应用新语言！");
    applySettings();
    close();
}

// 取消并关闭对话框
void SettingDialog::on_buttonBox_rejected()
{

    close();
}
