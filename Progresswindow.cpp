#include "Progresswindow.h"
#include "ui_Progresswindow.h"
#include "parse.h"

Progresswindow::Progresswindow(QWidget *parent):
    QDialog{parent},
    ui(new Ui::Progresswindow)
{
    ui->setupUi(this);
    clear();
}
Progresswindow::~Progresswindow()
{
    delete ui;  // 释放从UI文件中创建的用户界面对象
}

void Progresswindow::showStatus(const QString &msg)
{
    ui->textBrowser->append(msg);  // 在文本浏览部件中显示指定的消息
}

void Progresswindow::clear()
{
    ui->b_close->setEnabled(false);  // 禁用按钮
}

void Progresswindow::activeButton()
{
    ui->b_close->setEnabled(true);  // 启用按钮
}

void Progresswindow::on_b_close_clicked()
{
    close();  // 点击按钮后关闭对话框
}

