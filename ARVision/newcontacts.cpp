#include "newcontacts.h"
#include "ui_newcontacts.h"
#include "database.h"

NewContacts::NewContacts(QWidget *parent, qint32 Account, customerProfile *profile, QString name) :
    QDialog(parent),
    ui(new Ui::NewContacts)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    globalName = name;
    thisAccount = Account;
    thisProfile = profile;
}

NewContacts::~NewContacts()
{
    delete ui;
}

void NewContacts::on_commandLinkButton_save_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");
    qint32 newTransaction = 0;

    qint32 transaction = 0;
    qint32 balance = 0;
    QString thisStatus = "";
    qint32 total = ui->lineEdit_Total->text().toInt();
    qint32 depositPayment = ui->lineEdit_DepositPayment->text().toInt();

    QString description = ui->lineEdit_Description->text();

    balance = total - depositPayment;

    QString paymentType = "Deposit";

    if(balance < 0)
    {
        QMessageBox::critical(this, tr("Error"), "Balance Cannot Be Greater Than Total Amount");
        return;
    }
    else if(balance == 0)
    {
        thisStatus = "Complete";
        paymentType = "Payment";
    }

    else
        thisStatus = "Pending";

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
   {

       {
        Database conn;
        conn.connOpen("customersDetail");
        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "INSERT INTO '" << thisAccount << "'"

                   << " (SphereOD, CylinderOD, AxisOD, PrismOD, BCOD, DecInOD, OutOD, SphereOS, CylinderOS, AxisOS, "
                   << "PrismOS, BCOS, DecInOS, OutOS, Notes, Balance, Status, Lens, "
                   << "Date, Description, Cost, Type, \"Transaction\", "
                   << paymentType
                   << ", Discount) "

                   << "VALUES"

                   << " ('"
                   << ui->lineEdit_sphereOD->text() << "', '"
                   << ui->lineEdit_cylinderOD->text() << "', '"
                   << ui->lineEdit_axisOD->text() << "', '"
                   << ui->lineEdit_prismOD->text() << "', '"
                   << ui->lineEdit_BCOD->text() << "', '"
                   << ui->lineEdit_DecInOD->text() << "', '"
                   << ui->lineEdit_OutOD->text() << "', '"
                   << ui->lineEdit_sphereOS->text() << "', '"
                   << ui->lineEdit_cylinderOS->text() << "', '"
                   << ui->lineEdit_axisOS->text() << "', '"
                   << ui->lineEdit_prismOS->text() << "', '"
                   << ui->lineEdit_BCOS->text() << "', '"
                   << ui->lineEdit_DecInOS->text() << "', '"
                   << ui->lineEdit_OutOS->text() << "', '"
                   << ui->textEdit_Notes->toPlainText() << "', '"
                   << balance << "', '"
                   << thisStatus << "', '"
                   << ui->lineEdit_Lens->text() << "', '"
                   << timeStamp << "', '"
                   << description << "', '"
                   << total << "', '"
                   << ui->label_type->text() << "', '"
                   << newTransaction << "', '"
                   << ui->lineEdit_DepositPayment->text() << "', '"
                   << ui->lineEdit_Discount->text() << "')";


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

    }

    qint32 newLog = 0;
    {

    qint32 log = 0;
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
                << thisAccount << "', '"
                << description << "', '"
                << paymentType << "', '"
                << "+" << "', '"
                << depositPayment << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {
        QMessageBox::information(this, tr("AvisionR - Contacts"), "Save Successful");
        thisProfile->setup();
        this->hide();
    }

    conn.connClose();
    }
}

void NewContacts::on_lineEdit_Lens_textChanged(const QString &arg1)
{
    qint32 lens = arg1.toInt();
    qint32 discount = ui->lineEdit_Discount->text().toInt();

    qint32 total = lens - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}


void NewContacts::on_lineEdit_Discount_textChanged(const QString &arg1)
{
    qint32 discount = arg1.toInt();
    qint32 lens = ui->lineEdit_Lens->text().toInt();

    qint32 total = lens - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}
