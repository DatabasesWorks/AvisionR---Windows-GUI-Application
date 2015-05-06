#ifndef LOG_H
#define LOG_H

#include <QDialog>

namespace Ui {
class Log;
}

class Log : public QDialog
{
    Q_OBJECT

public:
    explicit Log(QWidget *parent = 0, QString name = "");
    ~Log();
    QString globalName;

    void setup();
    void clearHelper();

private slots:
    void on_commandLinkButton_Search_clicked();

    void on_commandLinkButton_Clear_clicked();

    void on_commandLinkButton_Manual_clicked();

private:
    Ui::Log *ui;
};

#endif // LOG_H
