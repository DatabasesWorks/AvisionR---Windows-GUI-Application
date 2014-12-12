#ifndef SPECTACLESPRINT_H
#define SPECTACLESPRINT_H

#include <QDialog>

namespace Ui {
class SpectaclesPrint;
}

class SpectaclesPrint : public QDialog
{
    Q_OBJECT

public:
    explicit SpectaclesPrint(QWidget *parent = 0, qint32 transaction = 0, QString date = "",
                             QString description = "", QString type = "",
                             QString fullName = "", QString Phone = "", qint32 account = 0,
                             QString Address1 = "", QString Address2 = "");
    ~SpectaclesPrint();

    qint32 thisTransaction;
    QString thisDate;
    QString thisDescription;
    QString thisType;
    QString thisFullName;
    QString thisPhone;
    qint32 thisAccount;
    QString thisAddress1;
    QString thisAddress2;

private slots:
    void on_pushButton_Lab_clicked();

    void on_pushButton_Client_clicked();
    
    void on_pushButton_Both_clicked();

private:
    Ui::SpectaclesPrint *ui;
};

#endif // SPECTACLESPRINT_H
