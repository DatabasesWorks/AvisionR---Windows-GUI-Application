#include "selectuser.h"
#include "ui_selectuser.h"
#include "database.h"

SelectUser::SelectUser(QWidget *parent, QString name, QString id, UserManagement *user) :
    QDialog(parent),
    ui(new Ui::SelectUser)
{
    ui->setupUi(this);
    ui->label_id->setText(id);
    thisUser = user;

    {
    Database conn;
    conn.connOpen("Employee");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from Employees WHERE ID = '" << id << "'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
            ui->lineEdit_name->setText(qry->value(0).toString());
            ui->lineEdit_username->setText(qry->value(2).toString());
            ui->lineEdit_password->setText(qry->value(3).toString());
            ui->lineEdit_position->setText(qry->value(5).toString());
            ui->lineEdit_hourlySalary->setText(qry->value(6).toString());
            ui->checkBox_admin->setChecked(qry->value(4).toBool());
        }
    }

    conn.connClose();
    }
}

SelectUser::~SelectUser()
{
    delete ui;
}

void SelectUser::on_commandLinkButton_update_clicked()
{
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

    queryStream << "UPDATE 'Employees'"
                << " SET Name = '" << ui->lineEdit_name->text()
                << "', Username = '" << ui->lineEdit_username->text()
                << "', Password = '" << ui->lineEdit_password->text()
                << "', Admin = '" << admin
                << "', 'Pay Rate' = '" << ui->lineEdit_hourlySalary->text()
                << "', Position = '" << ui->lineEdit_position->text() << "'"
                << "WHERE ID = '" << ui->label_id->text() << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }

    thisUser->setup();
    this->hide();
}
