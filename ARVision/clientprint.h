#ifndef CLIENTPRINT_H
#define CLIENTPRINT_H

#include <QDialog>

namespace Ui {
class ClientPrint;
}

class ClientPrint : public QDialog
{
    Q_OBJECT

public:
    explicit ClientPrint(QWidget *parent = 0, qint32 transaction = 0, QString date = "",
                         QString fullName = "", QString Phone = "", qint32 account = 0,
                         QString Address1 = "", QString Address2 = "");
    ~ClientPrint();


private:
    Ui::ClientPrint *ui;
};

#endif // CLIENTPRINT_H
