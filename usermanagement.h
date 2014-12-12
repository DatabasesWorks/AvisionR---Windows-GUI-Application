#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>

namespace Ui {
class UserManagement;
}

class UserManagement : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagement(QWidget *parent = 0);
    ~UserManagement();

    qint32 currentEmpId = 0;

    void setup();

private slots:
    void on_tableView_Users_doubleClicked(const QModelIndex &index);

    void on_commandLinkButton_forceCLockOut_clicked();

    void on_tableView_clock_clicked(const QModelIndex &index);

    void on_commandLinkButton_newUser_clicked();

    void on_commandLinkButton_done_clicked();

private:
    Ui::UserManagement *ui;
};

#endif // USERMANAGEMENT_H
