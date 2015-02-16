#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include <QDialog>
#include "customers.h"

namespace Ui {
class NewAccount;
}

class NewAccount : public QDialog
{
    Q_OBJECT

public:
    explicit NewAccount(QWidget *parent = 0, Customers *client = new Customers(), QString name = "");
    ~NewAccount();

    qint32 newAccount;
    Customers *thisClient;
    QString globalName;

    void optimize();

private slots:
    void on_commandLinkButton_clicked();

    void on_pushButton_Optimize_clicked();

private:
    Ui::NewAccount *ui;
};

#endif // NEWACCOUNT_H
