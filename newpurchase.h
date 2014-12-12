#ifndef NEWPURCHASE_H
#define NEWPURCHASE_H

#include <QDialog>
#include "customerprofile.h"

namespace Ui {
class NewPurchase;
}

class NewPurchase : public QDialog
{
    Q_OBJECT

public:
    explicit NewPurchase(QWidget *parent = 0, QString Address1 = "", QString Address2 = "",
                         qint32 Account = 0, customerProfile *profile = new customerProfile());
    ~NewPurchase();

    QString thisAddress1;
    QString thisAddress2;
    qint32 thisAccount;
    customerProfile *thisProfile;

private slots:
    void on_pushButton_SingleVision_clicked();

    void on_pushButton_MultiFocal_clicked();

    void on_pushButton_Contacts_clicked();

    void on_pushButton_Custom_clicked();

private:
    Ui::NewPurchase *ui;
};

#endif // NEWPURCHASE_H
