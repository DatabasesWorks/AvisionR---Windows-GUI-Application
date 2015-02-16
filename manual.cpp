#include "manual.h"
#include "ui_manual.h"
#include "database.h"

Manual::Manual(QWidget *parent, QString name, Log *log) :
    QDialog(parent),
    ui(new Ui::Manual)
{
    ui->setupUi(this);

    globalName = name;
    thisLog = log;

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    ui->comboBox_InOut->addItem("+");
    ui->comboBox_InOut->addItem("-");

}

Manual::~Manual()
{
    delete ui;
}

void Manual::on_commandLinkButton_Log_clicked()
{
    qint32 transaction = 0;
    qint32 newTransaction = 0;
    qint32 newLog = 0;
    qint32 log = 0;

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
              newTransaction = qry->value(1).toInt();
        }
    }
    queryString = "";
    transaction = newTransaction + 1;
    queryStream << "UPDATE mastertable"
                << " SET \"Transaction\" = '" << transaction << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text());
    }
    else
    {}

    conn.connClose();
   }

    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");


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
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 1");
    }
    else
    {
        while(qry->next())
        {
              newLog = qry->value(15).toInt();
        }
    }
    queryString = "";
    log = newLog + 1;
    queryStream << "UPDATE mastertable"
                << " SET Log = '" << log << "'";

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
    conn.connOpen("Log");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Log ('#', \"Date/Time\", User, \"Transaction\", Client, Description,"
                << " Type, \"+/-\", Amount) "
                << "VALUES ('"
                << newLog << "', '"
                << timeStamp << "', '"
                << globalName << "', '"
                << newTransaction << "', '"
                << ui->lineEdit_Client->text() << "', '"
                << ui->lineEdit_Description->text() << "', '"
                << ui->lineEdit_Type->text() << "', '"
                << ui->comboBox_InOut->currentText() << "', '"
                << ui->lineEdit_Amount->text() << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {
        thisLog->clearHelper();
        this->hide();
    }

    conn.connClose();
    }
}
