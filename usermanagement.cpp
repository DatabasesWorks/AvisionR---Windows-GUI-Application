#include "usermanagement.h"
#include "ui_usermanagement.h"
#include "database.h"
#include "selectuser.h"
#include "newuser.h"

UserManagement::UserManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManagement)
{
    ui->setupUi(this);


}

void UserManagement::setup()
{
    {
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Employee");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT Name, ID from Employees");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Users->setModel(model);
    ui->tableView_Users->setColumnWidth(0, 340);
    ui->tableView_Users->horizontalHeader()->setStretchLastSection(true);
    conn.connClose();
    }

    {
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Employee");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT Name, ID from Employees WHERE ONCLOCK = '1'");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_clock->setModel(model);
    ui->tableView_clock->horizontalHeader()->setStretchLastSection(true);
    conn.connClose();
    }


}

UserManagement::~UserManagement()
{
    delete ui;
}

void UserManagement::on_tableView_Users_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString name = index.sibling(row, 0).data(Qt::DisplayRole).toString();
    QString id = index.sibling(row, 1).data(Qt::DisplayRole).toString();

    SelectUser *selectUser = new SelectUser(0, name, id);
    selectUser->setModal(true);
    selectUser->show();
}


void UserManagement::on_commandLinkButton_forceCLockOut_clicked()
{
    QDate currentDate = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    int hour = currentTime.toString("HH").toInt();
    int minutes = currentTime.toString("mm").toInt();

    if(minutes > 30)
    {
        hour++;
    }

    currentTime = currentTime.fromString(QString::number(hour) + ":" + "00", "HH:mm");

    QString date = currentDate.toString("yyyy-MM-dd");
    QString time = currentTime.toString("HH:mm");
    {
        Database conn;

        conn.connOpen("Clock");

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "UPDATE '" << currentEmpId <<"'"
                      << " SET 'Time Out' = '" << time << "' where Date ='" << date << "'";


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }
        else
        {}

        conn.connClose();
    }

    {
    Database conn;

    if(!conn.connOpen("Employee"))
    {
        qDebug () << "Database Connection Fatal Error";
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'Employees'"
                << " SET ONCLOCK = '0' where ID = '" << currentEmpId << "'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }

    this->setup();
}

void UserManagement::on_tableView_clock_clicked(const QModelIndex &index)
{
    ui->commandLinkButton_forceCLockOut->setEnabled(true);

    int row = index.row();
    currentEmpId = index.sibling(row, 1).data(Qt::DisplayRole).toInt();
}

void UserManagement::on_commandLinkButton_newUser_clicked()
{
    NewUser *newUser = new NewUser(0, this);
    newUser->setModal(true);
    newUser->show();
}

void UserManagement::on_commandLinkButton_done_clicked()
{
    this->hide();
}
