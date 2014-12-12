#include "newaccount.h"
#include "ui_newaccount.h"
#include "database.h"
#include "customerprofile.h"
#include "optimize.h"
//#include <QtTest/QTest>

NewAccount::NewAccount(QWidget *parent, Customers *client) :
    QDialog(parent),
    ui(new Ui::NewAccount)
{
    ui->setupUi(this);
    thisClient = client;

    {
        QPixmap pix("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/Optimize.png");
        QIcon icon(pix);
        ui->pushButton_Optimize->setIcon(icon);
        ui->pushButton_Optimize->setIconSize(pix.size());
    }
}

NewAccount::~NewAccount()
{
    delete ui;
}

void NewAccount::on_commandLinkButton_clicked()
{
    qint32 account = 0;
    QString Last = ui->lineEdit_Last->text();
    QString First = ui->lineEdit_First->text();
    QString Phone = "(" + ui->lineEdit_PhoneArea->text() + ")"
            + ui->lineEdit_PhoneMiddle->text() + "-" + ui->lineEdit_PhoneRight->text();
    QString Address1 = ui->lineEdit_StreetAddress->text();
    QString Address2 = ui->lineEdit_City->text() + " " + ui->lineEdit_State->text() + " "
            + ui->lineEdit_ZipCode->text();

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
              newAccount = qry->value(0).toInt();
        }
    }
    queryString = "";
    account = newAccount + 1;
    queryStream << "UPDATE mastertable"
                << " SET \"Account\" = '" << account << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "First " + qry->lastError().text());
    }
    else
    {}

    conn.connClose();
   }
    {
    Database conn;

    conn.connOpen("customersBasic");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO customersBasic (Last, First, Phone, Account, Address1, Address2) "
                << "VALUES ('"
                << Last << "', '"
                << First << "', '"
                << Phone << "', '"
                << newAccount << "', '"
                << Address1 << "', '"
                << Address2 << "')";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "Second " +  qry->lastError().text());
    }
    else{}
    conn.connClose();
    }

    Database conn;

    conn.connOpen("customersDetail");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "CREATE TABLE '" << newAccount << "' ('Transaction' INTEGER,'Date' DATETIME,'Description'"
                << " VARCHAR,'Cost' DOUBLE,'Status' VARCHAR,'SphereOD' DOUBLE,'CylinderOD' DOUBLE,'AxisOD'"
                << " INTEGER,'PrismOD' VARCHAR,'BCOD' DOUBLE,'DecInOD' DOUBLE,'OutOD' INTEGER,'SphereOS' DOUBLE,'CylinderOS'"
                << " DOUBLE,'AxisOS' INTEGER,'PrismOS' VARCHAR,'BCOS' DOUBLE,'DecInOS' DOUBLE,'OutOS' INTEGER,'AddOD'"
                << " DOUBLE,'AddOS' DOUBLE,'SegHeightOD' DOUBLE,'SegHeightOS' DOUBLE,'InsetOD' DOUBLE,'InsetOS' DOUBLE,'TotalInsetOD'"
                << " DOUBLE,'TotalInsetOS' DOUBLE,'DPDTotal' DOUBLE,'DPDOD' DOUBLE,'DPDOS' DOUBLE,'NPDTotal' DOUBLE,'NPDOD'"
                << " DOUBLE,'NPDOS' DOUBLE,'EyeBridge' DOUBLE,'Temple' VARCHAR DEFAULT (null) ,'B' DOUBLE,'ED' DOUBLE,'LensMaterial'"
                << " VARCHAR,'FrameStyle' VARCHAR,'ColorTrim' VARCHAR,'StraightTop' BOOL,'RoundSegment' BOOL,'TriFocal'"
                << " BOOL DEFAULT (null) ,'Blended' BOOL,'Progressive' BOOL,'Executive' BOOL,'UVProtection' BOOL,'ScratchCoat'"
                << " BOOL,'HighIndex' BOOL,'AntiReflective' BOOL,'PGX' BOOL,'Transition' BOOL,'Tint' VARCHAR,'Account' INTEGER,'Type'"
                << " VARCHAR,'Balance' INTEGER,'Notes' VARCHAR,'Lens' DOUBLE,'Frame' DOUBLE, 'Deposit' INTEGER, 'Payment' INTEGER)";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "THIRD " + qry->lastError().text());
    }
    else
    {
        this->hide();
        customerProfile *customerprofile = new customerProfile(0, newAccount, Last, First, Phone, Address1, Address2);
        customerprofile->setup();
        customerprofile->setModal(true);
        customerprofile->show();
    }

    conn.connClose();
    thisClient->link();
}

void NewAccount::optimize()
{
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
              ui->lineEdit_PhoneArea->setText(qry->value(2).toString());
              ui->lineEdit_City->setText(qry->value(3).toString());
              ui->lineEdit_ZipCode->setText(qry->value(4).toString());
              ui->lineEdit_State->setText(qry->value(5).toString());
        }
    }

    conn.connClose();
    }
}


void NewAccount::on_pushButton_Optimize_clicked()
{
    Optimize *optimize = new Optimize(0, this);
    optimize->setModal(true);
    optimize->show();
}

