#include "newuser.h"
#include "ui_newuser.h"
#include "database.h"

NewUser::NewUser(QWidget *parent, UserManagement *user) :
    QDialog(parent),
    ui(new Ui::NewUser)
{
    ui->setupUi(this);
    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    thisUser = user;
}

NewUser::~NewUser()
{
    delete ui;
}

void NewUser::on_commandLinkButton_save_clicked()
{
    {

    qint32 id = 0;
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
              newID = qry->value(12).toInt();
        }
    }
    queryString = "";
    id = newID + 1;
    queryStream << "UPDATE mastertable"
                << " SET empID = '" << id << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text() + " 2");
    }
    else
    {}

    conn.connClose();
   }

    QString admin;
    if(ui->checkBox_admin->isChecked())
        admin = "1";
    else
        admin = "0";
    {
    Database conn;
    conn.connOpen("Employee");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Employees (Name, ID, Username, Password, Admin, 'Pay Rate', Position) "
                << "VALUES ('"
                << ui->lineEdit_name->text() << "', '"
                << newID << "', '"
                << ui->lineEdit_username->text() << "', '"
                << ui->lineEdit_password->text() << "', '"
                << admin << "', '"
                << ui->lineEdit_hourlySalary->text() << "', '"
                << ui->lineEdit_position->text() << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {}

    conn.connClose();
    }
    {
    Database conn;

    if(!conn.connOpen("Clock"))
    {
        qDebug () << "Database Connection Fatal Error in Login";
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "CREATE TABLE '" << newID << "' ('Date' DATETIME, 'Time In' DATETIME,"
                << " 'Time Out' DATETIME)";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 4");
    }
    else
    {}

    conn.connClose();
    }

    thisUser->setup();
    this->hide();
}
