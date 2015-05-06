#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <QDialog>
#include "newaccount.h"

namespace Ui {
class Optimize;
}

class Optimize : public QDialog
{
    Q_OBJECT

public:
    explicit Optimize(QWidget *parent = 0, NewAccount *newaccount = new NewAccount());
    ~Optimize();

    NewAccount *thisNewAccount;

private slots:
    void on_commandLinkButton_clicked();

private:
    Ui::Optimize *ui;
};

#endif // OPTIMIZE_H
