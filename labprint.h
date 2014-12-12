#ifndef LABPRINT_H
#define LABPRINT_H

#include <QDialog>

namespace Ui {
class LabPrint;
}

class LabPrint : public QDialog
{
    Q_OBJECT

public:
    explicit LabPrint(QWidget *parent = 0, qint32 transaction = 0, QString date = "",
                      QString description = "", QString type = "",
                      QString fullName = "", QString Phone = "", qint32 account = 0,
                      QString Address1 = "", QString Address2 = "");
    ~LabPrint();
    qint32 thisTransaction;
    QString thisDate;
    QString thisDescription;
    QString thisType;
    QString thisFullName;
    QString thisPhone;
    qint32 thisAccount;
    QString thisAddress1;
    QString thisAddress2;

private:
    Ui::LabPrint *ui;
};

#endif // LABPRINT_H
