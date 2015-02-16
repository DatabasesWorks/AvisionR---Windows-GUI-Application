#include "editframe.h"
#include "ui_editframe.h"
#include "database.h"

EditFrame::EditFrame(QWidget *parent, Frames *frames, qint32 frameNumber) :
    QDialog(parent),
    ui(new Ui::EditFrame)
{
    ui->setupUi(this);

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisFrame = frames;
    thisFrameNumber = frameNumber;

    {
    Database conn;
    conn.connOpen("Frames");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    qDebug() << frameNumber;
    queryStream << "Select * from Frames WHERE \"#\" = " << frameNumber;


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
              ui->lineEdit_Brand_3->setText(qry->value(1).toString());
              ui->lineEdit_model->setText(qry->value(2).toString());
              ui->lineEdit_Color_3->setText(qry->value(3).toString());
              ui->lineEdit_Price_3->setText(qry->value(4).toString());
              ui->spinBox_units_3->setValue(qry->value(5).toInt());
        }
    }

    conn.connClose();
    }
}

EditFrame::~EditFrame()
{
    delete ui;
}

void EditFrame::on_commandLinkButton_cancel_3_clicked()
{
    this->hide();
}

void EditFrame::on_commandLinkButton_Update_clicked()
{
    {
    Database conn;
    conn.connOpen("Frames");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'Frames'"
                << " SET Brand = '" << ui->lineEdit_Brand_3->text()
                << "', Model = '" << ui->lineEdit_model->text()
                << "', Color = '" << ui->lineEdit_Color_3->text()
                << "', Price = '" << ui->lineEdit_Price_3->text()
                << "', Units = '" << QString::number(ui->spinBox_units_3->value())
                << "' WHERE \"#\" = " << thisFrameNumber;

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }

    thisFrame->clearHelper();
    this->hide();
}

void EditFrame::on_commandLinkButton_Delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "AvisionR - Delete",
                                  "Are you sure you want to DELETE this Frame?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        {
            Database conn;
            if(!conn.connOpen("Frames"))
            {
                qDebug()<<"Failed to open Data";
                return;
            }

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "DELETE FROM Frames WHERE \"#\" = " << thisFrameNumber;

            qry->prepare(queryString);

            if(qry->exec())
            {
                QMessageBox::information(this, tr("AvisionR - Delete"), "Frame Deleted");
            }
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }

        thisFrame->clearHelper();
        this->hide();
    }
}
