#ifndef MODIFYPROFILE_H
#define MODIFYPROFILE_H

#include <QDialog>
#include "customerprofile.h"

namespace Ui {
class ModifyProfile;
}

class ModifyProfile : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyProfile(QWidget *parent = 0, qint32 account = 0,
                            customerProfile *profile = new customerProfile());
    ~ModifyProfile();

    qint32 thisAccount;
    customerProfile *thisProfile;

private slots:
    void on_commandLinkButton_cancel_clicked();
    void on_commandLinkButton_Update_clicked();

    void on_commandLinkButton_Delete_clicked();

private:
    Ui::ModifyProfile *ui;


};

#endif // MODIFYPROFILE_H
