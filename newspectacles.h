#ifndef NEWSPECTACLES_H
#define NEWSPECTACLES_H

#include <QDialog>
#include "customerprofile.h"

namespace Ui {
class NewSpectacles;
}

class NewSpectacles : public QDialog
{
    Q_OBJECT

public:
    explicit NewSpectacles(QWidget *parent = 0, QString type = "", QString Address1 = "",
                           QString Address2 = "", qint32 Account = 0, customerProfile *profile = new customerProfile());
    ~NewSpectacles();

    QString thisAddress1;
    QString thisAddress2;
    qint32 thisAccount;
    customerProfile *thisProfile;
    qint32 newTransaction = 0;

private slots:
    void on_commandLinkButton_cancel_clicked();

    void on_commandLinkButton_save_clicked();

    void on_lineEdit_Frame_textChanged(const QString &arg1);

    void on_lineEdit_Lens_textChanged(const QString &arg1);

private:
    Ui::NewSpectacles *ui;
};

#endif // NEWSPECTACLES_H
