#ifndef SPECTACLES_H
#define SPECTACLES_H

#include <QDialog>
#include "customerprofile.h"

namespace Ui {
class Spectacles;
}

class Spectacles : public QDialog
{
    Q_OBJECT

public:
    explicit Spectacles(QWidget *parent = 0, qint32 transaction = 0, QString date = "",
                        QString description = "", int total = 0.0, QString type = "",
                        QString Last = "", QString First = "", QString Phone = "",
                        qint32 account = 0, QString status = "",
                        customerProfile *profile = new customerProfile(), QString Address1 = "", QString Address2 = "");
    ~Spectacles();

    qint32 balance = 0;
    qint32 thisAccount = 0;
    QString thisTransaction;
    QString thisStatus = "";\
    customerProfile *thisProfile;
    bool isDownPayment = false;

private slots:
    void on_commandLinkButton_cancel_clicked();

    void on_commandLinkButton_update_clicked();

    void on_commandLinkButton_print_clicked();

    void on_commandLinkButton_delete_clicked();

private:
    Ui::Spectacles *ui;
};

#endif // SPECTACLES_H
