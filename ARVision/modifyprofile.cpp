#include "modifyprofile.h"
#include "ui_modifyprofile.h"
#include "database.h"

ModifyProfile::ModifyProfile(QWidget *parent, qint32 account, customerProfile *profile) :
    QDialog(parent),
    ui(new Ui::ModifyProfile)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisProfile = profile;

    thisAccount = account;
    {
    Database conn;
    conn.connOpen("customersBasic");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from customersBasic WHERE Account = '" << thisAccount << "'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
            ui->lineEdit_First->setText(qry->value(1).toString());
            ui->lineEdit_Last->setText(qry->value(0).toString());

            QString tempPhone = qry->value(2).toString();
            ui->lineEdit_PhoneArea->setText(tempPhone.mid(1,3));
            ui->lineEdit_PhoneMiddle->setText(tempPhone.mid(5,3));
            ui->lineEdit_PhoneRight->setText(tempPhone.right(4));

            ui->lineEdit_StreetAddress->setText(qry->value(4).toString());

            QString tempAddress = qry->value(5).toString();
            ui->lineEdit_ZipCode->setText(tempAddress.right(5));
            QString tempState = tempAddress.right(9).left(2);
            ui->lineEdit_State->setText(tempState);
            qDebug() << tempAddress.length();
            ui->lineEdit_City->setText(tempAddress.left(tempAddress.length()-10));
        }
    }

    conn.connClose();
    }
}

ModifyProfile::~ModifyProfile()
{
    delete ui;
}

void ModifyProfile::on_commandLinkButton_Update_clicked()
{
    {
    QString phoneNumber = "(" + ui->lineEdit_PhoneArea->text()+ ")" +
            ui->lineEdit_PhoneMiddle->text() + "-" + ui->lineEdit_PhoneRight->text();
    QString Address2 = ui->lineEdit_City->text() + " " + ui->lineEdit_State->text() + ", "
            + ui->lineEdit_ZipCode->text();
    Database conn;

    conn.connOpen("customersBasic");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'customersBasic'"
                << " SET Last = '" << ui->lineEdit_Last->text()
                << "', First = '" << ui->lineEdit_First->text()
                << "', Phone = '" << phoneNumber
                << "', Address1 = '" << ui->lineEdit_StreetAddress->text()
                << "', Address2 = '" << Address2 << "'"
                << " WHERE Account = '" << thisAccount << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else{}
    conn.connClose();
    }
    QMessageBox::information(this, tr("AvisionR - Modify Prodile"), "Customer Profile will now Exit to Update Profile");
    thisProfile->hide();
    this->hide();

}

void ModifyProfile::on_commandLinkButton_cancel_clicked()
{
    this->hide();
}

void ModifyProfile::on_commandLinkButton_Delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "AvisionR - Delete",
                                  "Are you sure you want to DELETE this Client?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        {
            Database conn;
            if(!conn.connOpen("customersBasic"))
            {
                qDebug()<<"Failed to open Data";
                return;
            }

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "DELETE FROM customersBasic WHERE \"Account\" = " << thisAccount;

            qry->prepare(queryString);

            if(qry->exec())
            {}
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }

        {
            Database conn;
            if(!conn.connOpen("customersDetail"))
            {
                qDebug()<<"Failed to open Data";
                return;
            }

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "DROP TABLE '" << thisAccount << "'";

            qry->prepare(queryString);

            if(qry->exec())
            {
                QMessageBox::information(this, tr("AvisionR - Delete"), "Client Deleted");
            }
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }

        thisProfile->hide();
        this->hide();
    }
}
