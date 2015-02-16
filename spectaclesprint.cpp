#include "spectaclesprint.h"
#include "ui_spectaclesprint.h"
#include "clientprint.h"
#include "labprint.h"
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QDialog>
#include <QtDebug>


SpectaclesPrint::SpectaclesPrint(QWidget *parent, qint32 transaction, QString date, QString description, QString type,
                                 QString fullName, QString Phone, qint32 account,
                                 QString Address1, QString Address2) :
    QDialog(parent),
    ui(new Ui::SpectaclesPrint)
{
    ui->setupUi(this);


    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisTransaction = transaction;
    thisDate = date;
    thisDescription = description;
    thisType = type;
    thisFullName = fullName;
    thisPhone = Phone;
    thisAccount = account;
    thisAddress1 = Address1;
    thisAddress2 = Address2;

    {
        QPixmap pix("pixMap/C.png");
        QIcon icon(pix);
        ui->pushButton_Client->setIcon(icon);
        ui->pushButton_Client->setIconSize(pix.size());
    }
    {
        QPixmap pix("pixMap/L.png");
        QIcon icon(pix);
        ui->pushButton_Lab->setIcon(icon);
        ui->pushButton_Lab->setIconSize(pix.size());
    }
    {
        QPixmap pix("pixMap/B.png");
        QIcon icon(pix);
        ui->pushButton_Both->setIcon(icon);
        ui->pushButton_Both->setIconSize(pix.size());
    }


}

SpectaclesPrint::~SpectaclesPrint()
{
    delete ui;
}

void SpectaclesPrint::on_pushButton_Lab_clicked()
{
    LabPrint *labPrint = new LabPrint(0, thisTransaction,  thisDate, thisDescription, thisType,
                                      thisFullName, thisPhone, thisAccount,
                                      thisAddress1, thisAddress2);

    labPrint->grab().save("C:/SQL/printLabTemp.png");

    QPrinter printer;
    //printer.setPaperSize(QSizeF(140, 216), QPrinter::Millimeter);

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() != QDialog::Accepted)
    {
        return;
    }

    QImage img("C:/SQL/printLabTemp.png");
    qDebug() << "width: " << img.width();
    qDebug() << "height: " << img.height();
    //img = img.scaled(img.width(), img.height());
    QPainter painter(&printer);
    //painter.drawImage(QPoint(0,0),img);

    QSize size = img.size();
    painter.translate(size.height()/2,size.height()/2);

    // Rotate the painter 90 degrees
    painter.rotate(90);

    // Set origo back to upper left corner
    painter.translate(-size.height()/2,-size.height()/2);

    // Draw your original pixmap on it
    painter.drawImage(QPoint(10, 50),img); //Vertical, Horizontal

    painter.end();
    this->hide();
    return;
}

void SpectaclesPrint::on_pushButton_Client_clicked()
{
    ClientPrint *clientPrint = new ClientPrint(0, thisTransaction,  thisDate,
                                               thisFullName, thisPhone, thisAccount,
                                               thisAddress1, thisAddress2);

    clientPrint->grab().save("C:/SQL/printClientTemp.png");

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() != QDialog::Accepted)
    {
        return;
    }

    QImage img("C:/SQL/printClientTemp.png");
    qDebug() << "width: " << img.width();
    qDebug() << "height: " << img.height();
    img = img.scaled(img.width(), img.height());
    QPainter painter(&printer);
    //painter.drawImage(QPoint(0,0),img);

    /*QSize size = img.size();
    painter.translate(size.height()/2,size.height()/2);

    // Rotate the painter 90 degrees
    painter.rotate(90);

    // Set origo back to upper left corner
    painter.translate(-size.height()/2,-size.height()/2);

    // Draw your original pixmap on it
    painter.drawImage(QPoint(10, 50),img); //Vertical, Horizontal*/

    painter.drawImage(QPoint(0, 10), img);

    painter.end();
    this->hide();
    return;
}


void SpectaclesPrint::on_pushButton_Both_clicked()
{
    LabPrint *labPrint = new LabPrint(0, thisTransaction,  thisDate, thisDescription, thisType,
                                      thisFullName, thisPhone, thisAccount,
                                      thisAddress1, thisAddress2);

    labPrint->grab().save("C:/SQL/printLabTemp.png");

    ClientPrint *clientPrint = new ClientPrint(0, thisTransaction,  thisDate,
                                               thisFullName, thisPhone, thisAccount,
                                               thisAddress1, thisAddress2);

    clientPrint->grab().save("C:/SQL/printClientTemp.png");


    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer);
    dialog->setWindowTitle("Print Document");

    if (dialog->exec() != QDialog::Accepted)
        return;

    {
        QImage img("C:/SQL/printLabTemp.png");
        qDebug() << "width: " << img.width();
        qDebug() << "height: " << img.height();
        //img = img.scaled(img.width(), img.height());
        QPainter painter(&printer);
        //painter.drawImage(QPoint(0,0),img);

        QSize size = img.size();
        painter.translate(size.height()/2,size.height()/2);

        // Rotate the painter 90 degrees
        painter.rotate(90);

        // Set origo back to upper left corner
        painter.translate(-size.height()/2,-size.height()/2);

        // Draw your original pixmap on it
        painter.drawImage(QPoint(10, 50),img); //Vertical, Horizontal

        painter.end();
    }

    printer.newPage();

    {
        QImage img("C:/SQL/printClientTemp.png");
        qDebug() << "width: " << img.width();
        qDebug() << "height: " << img.height();
        img = img.scaled(img.width(), img.height());
        QPainter painter(&printer);
        //painter.drawImage(QPoint(0,0),img);

        //painter.drawImage(QPoint(0,0),img);

        /*QSize size = img.size();
        painter.translate(size.height()/2,size.height()/2);

        // Rotate the painter 90 degrees
        painter.rotate(90);

        // Set origo back to upper left corner
        painter.translate(-size.height()/2,-size.height()/2);

        // Draw your original pixmap on it
        painter.drawImage(QPoint(10, 50),img); //Vertical, Horizontal*/

        painter.drawImage(QPoint(0, 10), img);

        painter.end();
    }
    this->hide();
    return;

}
