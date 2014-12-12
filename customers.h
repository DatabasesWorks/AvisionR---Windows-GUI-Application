#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <QDialog>

namespace Ui {
class Customers;
}

class Customers : public QDialog
{
    Q_OBJECT

public:
    explicit Customers(QWidget *parent = 0);

    QString Address1;
    QString Address2;

    void link();
    ~Customers();

private slots:
    void on_lineEdit_Last_selectionChanged();

    void on_lineEdit_First_selectionChanged();

    void on_lineEdit_Phone_selectionChanged();

    void on_lineEdit_Account_selectionChanged();

    void on_commandLinkButton_Search_clicked();

    void on_tableView_Customers_doubleClicked(const QModelIndex &index);

    void on_commandLinkButton_New_clicked();



    void on_commandLinkButton_Search_2_clicked();

private:
    Ui::Customers *ui;
};

#endif // CUSTOMERS_H
