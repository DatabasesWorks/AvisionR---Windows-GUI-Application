#include "clientprint.h"
#include "ui_clientprint.h"
#include "database.h"

ClientPrint::ClientPrint(QWidget *parent, qint32 transaction, QString date,
                         QString fullName, QString Phone, qint32 account,
                         QString Address1, QString Address2) :
    QDialog(parent),
    ui(new Ui::ClientPrint)
{
    ui->setupUi(this);

    ui->label_Fullname->setText(fullName);
    ui->label_addressLine1->setText(Address1);
    ui->label_addressLine2->setText(Address2);
    ui->label_phoneNumber->setText(Phone);
    ui->label_date->setText(date);
    ui->label_account->setText(QString::number(account));

    Database conn;
    conn.connOpen("customersDetail");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    QSqlQueryModel * model = new QSqlQueryModel();

    queryStream << "SELECT Description, Status, Frame, LensLeft, LensRight, Cost from '" << account << "' WHERE \"Transaction\" = " << transaction;

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        model->setQuery(*qry);
        ui->tableView_History->setModel(model);
    }

    queryString = "";

    queryStream << "SELECT * FROM '" << account << "' WHERE \"Transaction\" = " << transaction;

    qry->prepare(queryString);


    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() = " in Setup");
    }
    else
    {
        while(qry->next())
        {
            QString total = QString::number(qry->value(3).toInt() + qry->value(63).toInt());
            ui->label_balance->setText(qry->value(56).toString());
            ui->label_balance_2->setText(qry->value(56).toString());
            ui->label_total->setText(total);
            ui->label_subtotal->setText(qry->value(3).toString());
            ui->label_discount->setText(qry->value(63).toString());

            if(qry->value(61).toString() == "")
                ui->label_deposit->setText("0");
            else
                ui->label_deposit->setText(qry->value(59).toString());

            if(qry->value(62).toString() == "")
                ui->label_payment->setText("0");
            else
                ui->label_payment->setText(qry->value(60).toString());
        }
    }

    ui->tableView_History->setColumnWidth(0, 260);
    ui->tableView_History->horizontalHeader()->setStretchLastSection(true);

    {
    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from mastertable";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " in Phone");
    }
    else
    {
        while(qry->next())
        {
              ui->label_line1->setText(qry->value(6).toString());
              QString tempPhone = qry->value(11).toString();

              if(qry->value(7).toString() == "")
              {
                  ui->label_line2->setText(qry->value(8).toString() + ", " +
                                           qry->value(9).toString() + " "  +
                                           qry->value(10).toString());

                  ui->label_line3->setText("(" + tempPhone.left(3) + ")" +
                                           tempPhone.mid(3,3) + "-" +
                                           tempPhone.right(4));

                  ui->label_line4->setText("");
              }
              else
              {
                  ui->label_line2->setText(qry->value(7).toString());

                  ui->label_line3->setText(qry->value(8).toString() + ", " +
                                           qry->value(9).toString() + " "  +
                                           qry->value(10).toString());

                  ui->label_line4->setText("(" + tempPhone.left(3) + ")" +
                                           tempPhone.mid(3,3) + "-" +
                                           tempPhone.right(4));
              }
        }
    }

    conn.connClose();
    }


}

ClientPrint::~ClientPrint()
{
    delete ui;
}
