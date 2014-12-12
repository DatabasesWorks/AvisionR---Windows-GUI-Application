#ifndef NEWCONTACTS_H
#define NEWCONTACTS_H

#include <QDialog>
#include "customerprofile.h"

namespace Ui {
class NewContacts;
}

class NewContacts : public QDialog
{
    Q_OBJECT

public:
    explicit NewContacts(QWidget *parent = 0, qint32 Account = 0, customerProfile *profile = new customerProfile());
    ~NewContacts();

    qint32 thisAccount;
    customerProfile *thisProfile;

private slots:
    void on_commandLinkButton_save_clicked();

    void on_lineEdit_Lens_textChanged(const QString &arg1);

private:
    Ui::NewContacts *ui;
};

#endif // NEWCONTACTS_H
