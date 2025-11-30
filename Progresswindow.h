    #ifndef PROGRESSWINDOW_H
#define PROGRESSWINDOW_H

#include <QObject>
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui {
class Progresswindow;
}
QT_END_NAMESPACE
class Progresswindow : public QDialog
{
    Q_OBJECT
public:
    explicit Progresswindow(QWidget *parent = nullptr);
    ~Progresswindow();
    void showStatus(const QString &msg);
    void clear();
    void activeButton();

private slots:

    void on_b_close_clicked();

private:
    Ui::Progresswindow *ui;
signals:
};

#endif // PROGRESSWINDOW_H
