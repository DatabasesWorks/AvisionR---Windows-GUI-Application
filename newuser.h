#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include "usermanagement.h"

namespace Ui {
class NewUser;
}

class NewUser : public QDialog
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = 0, UserManagement *user = new UserManagement());
    ~NewUser();

    UserManagement *thisUser;
    qint32 newID;

private slots:
    void on_commandLinkButton_save_clicked();

private:
    Ui::NewUser *ui;
};

#endif // NEWUSER_H
