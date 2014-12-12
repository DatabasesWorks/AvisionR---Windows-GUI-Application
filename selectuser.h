#ifndef SELECTUSER_H
#define SELECTUSER_H

#include <QDialog>
#include "usermanagement.h"


namespace Ui {
class SelectUser;
}

class SelectUser : public QDialog
{
    Q_OBJECT

public:
    explicit SelectUser(QWidget *parent = 0, QString name="", QString id="",
                        UserManagement *user = new UserManagement());
    ~SelectUser();

    UserManagement *thisUser;

private slots:
    void on_commandLinkButton_update_clicked();

private:
    Ui::SelectUser *ui;
};

#endif // SELECTUSER_H
