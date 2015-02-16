#include "optimize.h"
#include "ui_optimize.h"
#include "database.h"

Optimize::Optimize(QWidget *parent, NewAccount *newaccount) :
    QDialog(parent),
    ui(new Ui::Optimize)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisNewAccount = newaccount;

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
              ui->lineEdit_Area->setText(qry->value(2).toString());
              ui->lineEdit_City->setText(qry->value(3).toString());
              ui->lineEdit_ZipCode->setText(qry->value(4).toString());
              ui->lineEdit_State->setText(qry->value(5).toString());
        }
    }

    conn.connClose();
    }
}

Optimize::~Optimize()
{
    delete ui;
}

void Optimize::on_commandLinkButton_clicked()
{
    {
    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'mastertable'"
                << " SET Area = '" << ui->lineEdit_Area->text()
                << "', City = '" << ui->lineEdit_City->text()
                << "', Zip = '" << ui->lineEdit_ZipCode->text()
                << "', State = '" << ui->lineEdit_State->text() << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }

    thisNewAccount->optimize();
    this->hide();
}
