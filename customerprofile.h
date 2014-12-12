#ifndef CUSTOMERPROFILE_H
#define CUSTOMERPROFILE_H

#include <QDialog>

namespace Ui {
class customerProfile;
}

class customerProfile : public QDialog
{
    Q_OBJECT

public:
    explicit customerProfile(QWidget *parent = 0, qint32 account = 0, QString Last = "",
                             QString First = "", QString Phone = "", QString Address1 = "", QString Address2 = "");
    ~customerProfile();

    QString thisLast, thisFirst, thisPhone, thisAddress1, thisAddress2;
    qint32 thisAccount;
    void setup();

private slots:
    void on_tableView_History_doubleClicked(const QModelIndex &index);

    void on_commandLinkButton_newPurchase_clicked();

    void on_commandLinkButton_3_clicked();

private:
    Ui::customerProfile *ui;
};

#endif // CUSTOMERPROFILE_H
