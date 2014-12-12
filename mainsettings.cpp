#include "mainsettings.h"
#include "ui_mainsettings.h"
#include "database.h"

MainSettings::MainSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainSettings)
{
    ui->setupUi(this);

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
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
              ui->lineEdit_storeAddress1->setText(qry->value(6).toString());
              ui->lineEdit_StoreAddress2->setText(qry->value(7).toString());
              ui->lineEdit_storeCity->setText(qry->value(8).toString());
              ui->lineEdit_storeState->setText(qry->value(9).toString());
              ui->lineEdit_StoreZip->setText(qry->value(10).toString());
              tempPhone = qry->value(11).toString();
              ui->lineEdit_PhoneArea->setText(tempPhone.left(3));
              ui->lineEdit_PhoneMiddle->setText(tempPhone.mid(3,3));
              ui->lineEdit_PhoneRight->setText(tempPhone.right(4));
        }
    }

    conn.connClose();
    }
}

MainSettings::~MainSettings()
{
    delete ui;
}

void MainSettings::on_commandLinkButton_save_clicked()
{
    QString phoneNumber = ui->lineEdit_PhoneArea->text()+ ui->lineEdit_PhoneMiddle->text() + ui->lineEdit_PhoneRight->text();

    {
    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'mastertable'"
                << " SET storeAddress1 = '" << ui->lineEdit_storeAddress1->text()
                << "', storeAddress2 = '" << ui->lineEdit_StoreAddress2->text()
                << "', storeCity = '" << ui->lineEdit_storeCity->text()
                << "', storeState = '" << ui->lineEdit_storeState->text()
                << "', storeZip = '" << ui->lineEdit_StoreZip->text()
                << "', storePhone = '" << phoneNumber << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {

    }

    conn.connClose();
    }

    this->hide();
}
