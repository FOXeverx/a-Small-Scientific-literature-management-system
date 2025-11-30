#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QTranslator>
namespace Ui {
class settingdialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void applySettings();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::settingdialog *ui;
};

#endif // SETTINGDIALOG_H
