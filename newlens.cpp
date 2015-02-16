#include "newlens.h"
#include "ui_newlens.h"
#include "database.h"

NewLens::NewLens(QWidget *parent, Lens *lens) :
    QDialog(parent),
    ui(new Ui::NewLens)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisLens = lens;
}

NewLens::~NewLens()
{
    delete ui;
}

void NewLens::on_commandLinkButton_add_2_clicked()
{
    qint32 newLens = 0;
    {

    qint32 lens = 0;

    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from mastertable";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 1");
    }
    else
    {
        while(qry->next())
        {
              newLens = qry->value(14).toInt();
        }
    }
    queryString = "";
    lens = newLens + 1;
    queryStream << "UPDATE mastertable"
                << " SET Lens = '" << lens << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text() + " 2");
    }
    else
    {}

    conn.connClose();
    }

    {
    Database conn;
    conn.connOpen("Lens");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Lens ('#', Type, \"Add-Ons\", Price, Units) "
                << "VALUES ('"
                << newLens << "', '"
                << ui->lineEdit_Type->text() << "', '"
                << ui->lineEdit_AddOns->text() << "', '"
                << ui->lineEdit_Price_2->text() << "', '"
                << QString::number(ui->spinBox_units_2->value()) << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {}

    conn.connClose();
    }

    thisLens->clearHelper();
    this->hide();
}

void NewLens::on_commandLinkButton_cancel_2_clicked()
{
    this->hide();
}
