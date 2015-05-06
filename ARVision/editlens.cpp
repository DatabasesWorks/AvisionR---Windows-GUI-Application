#include "editlens.h"
#include "ui_editlens.h"
#include "database.h"

EditLens::EditLens(QWidget *parent, Lens *lens, qint32 lensNumber) :
    QDialog(parent),
    ui(new Ui::EditLens)
{
    ui->setupUi(this);


    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisLens = lens;
    thisLensNumber = lensNumber;

    {
    Database conn;
    conn.connOpen("Lens");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from Lens WHERE \"#\" = " << lensNumber;


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
              ui->lineEdit_Type->setText(qry->value(1).toString());
              ui->lineEdit_AddOns->setText(qry->value(2).toString());
              ui->lineEdit_Price_2->setText(qry->value(3).toString());
              ui->spinBox_units_2->setValue(qry->value(4).toInt());
        }
    }

    conn.connClose();
    }
}

EditLens::~EditLens()
{
    delete ui;
}

void EditLens::on_commandLinkButton_cancel_2_clicked()
{
    this->hide();
}

void EditLens::on_commandLinkButton_Update_clicked()
{
    {
    Database conn;
    conn.connOpen("Lens");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'Lens'"
                << " SET Type = '" << ui->lineEdit_Type->text()
                << "', \"Add-Ons\" = '" << ui->lineEdit_AddOns->text()
                << "', Price = '" << ui->lineEdit_Price_2->text()
                << "', Units = '" << QString::number(ui->spinBox_units_2->value())
                << "' WHERE \"#\" = " << thisLensNumber;

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }

    thisLens->clearHelper();
    this->hide();
}

void EditLens::on_commandLinkButton_Delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "AvisionR - Delete",
                                  "Are you sure you want to DELETE this Lens?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        {
            Database conn;
            if(!conn.connOpen("Lens"))
            {
                qDebug()<<"Failed to open Data";
                return;
            }

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "DELETE FROM Lens WHERE \"#\" = " << thisLensNumber;

            qry->prepare(queryString);

            if(qry->exec())
            {
                QMessageBox::information(this, tr("AvisionR - Delete"), "Lens Deleted");
            }
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }

        thisLens->clearHelper();
        this->hide();
    }
}
