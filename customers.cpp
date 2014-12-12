#include "customers.h"
#include "ui_customers.h"
#include "database.h"
#include <QMessageBox>
#include "customerprofile.h"
#include "newaccount.h"

Customers::Customers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customers)
{
    ui->setupUi(this);
    ui->lineEdit_Account->setPlaceholderText("Account Number");
    ui->lineEdit_First->setPlaceholderText("First Name");
    ui->lineEdit_Last->setPlaceholderText("Last Name");
    ui->lineEdit_Phone->setPlaceholderText("Phone Number");

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("customersBasic");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT Last, First, Phone, Account from customersBasic");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Customers->setModel(model);
    conn.connClose();
    ui->tableView_Customers->horizontalHeader()->setStretchLastSection(true);
}

Customers::~Customers()
{
    delete ui;
}

void Customers::on_lineEdit_Last_selectionChanged()
{
    ui->lineEdit_Last->setText("");
}

void Customers::on_lineEdit_First_selectionChanged()
{
    ui->lineEdit_First->setText("");
}

void Customers::on_lineEdit_Phone_selectionChanged()
{
    ui->lineEdit_Phone->setText("");
}

void Customers::on_lineEdit_Account_selectionChanged()
{
    ui->lineEdit_Account->setText("");
}

void Customers::on_commandLinkButton_Search_clicked()
{
    QString first, last, phone;
    qint32 account;

    Database conn;

    conn.connOpen("customersBasic");

    account = ui->lineEdit_Account->text().toInt();
    first = ui->lineEdit_First->text();
    last = ui->lineEdit_Last->text();
    phone = ui->lineEdit_Phone->text();

    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    QSqlQueryModel * model = new QSqlQueryModel();

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT Last, First, Phone, Account FROM customersBasic WHERE \"First\" LIKE '%"+first+"%' AND \"Last\" LIKE '%"+last+"%' AND"
                << "\"Phone\" LIKE '%"+phone+"%' AND \"Account\" LIKE '%" << account << "%'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        model->setQuery(*qry);
        ui->tableView_Customers->setModel(model);
    }

    conn.connClose();
}

void Customers::on_tableView_Customers_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString Last = index.sibling(row, 0).data(Qt::DisplayRole).toString();
    QString First = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    QString Phone = index.sibling(row, 2).data(Qt::DisplayRole).toString();
    qint32 account = index.sibling(row, 3).data(Qt::DisplayRole).toInt();

    Database conn;
    conn.connOpen("customersBasic");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT Address1, Address2 FROM customersBasic WHERE Account = '" << account << "'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
              Address1 = qry->value(0).toString();
              Address2 = qry->value(1).toString();
        }
    }

    conn.connClose();

    customerProfile *customerprofile = new customerProfile(0, account, Last, First, Phone, Address1, Address2);
    customerprofile->setup();
    customerprofile->setModal(true);
    customerprofile->show();
}

void Customers::link()
{
    on_commandLinkButton_Search_clicked();
}

void Customers::on_commandLinkButton_New_clicked()
{
    NewAccount *newAccount = new NewAccount(0, this);
    newAccount->setModal(true);
    newAccount->optimize();
    newAccount->show();
}

void Customers::on_commandLinkButton_Search_2_clicked()
{
    this->hide();
}
