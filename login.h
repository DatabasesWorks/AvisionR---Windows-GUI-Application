#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0, QString target = "");
    ~Login();

    QString thisTarget;

private slots:
    void on_lineEdit_User_selectionChanged();

    void on_lineEdit_Password_selectionChanged();

    void on_commandLinkButton_Login_clicked();

    void on_lineEdit_User_textChanged();

    void on_lineEdit_Password_textChanged();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
