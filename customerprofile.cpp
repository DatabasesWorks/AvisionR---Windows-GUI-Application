#include "customerprofile.h"
#include "ui_customerprofile.h"
#include "database.h"
#include "spectacles.h"
#include "newpurchase.h"
#include "modifyprofile.h"

customerProfile::customerProfile(QWidget *parent, qint32 account, QString Last, QString First, QString Phone,
                                 QString Address1, QString Address2, QString name) :
    QDialog(parent),
    ui(new Ui::customerProfile)
{
    ui->setupUi(this);

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    globalName = name;
    ui->label_addressLine1->setText(Address1);
    ui->label_addressLine2->setText(Address2);

    thisAddress1 = Address1;
    thisAddress2 = Address2;

    thisLast = Last;
    thisFirst = First;
    thisPhone = Phone;
    thisAccount = account;
    ui->label_Fullname->setText(First + " " + Last);


    ui->label_account->setText(QString::number(account));
    ui->label_phoneNumber->setText(Phone);
}

void customerProfile :: setup()
{
    qint32 balance = 0;
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("customersDetail");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    qDebug() << thisAccount;

    queryStream << "SELECT \"Transaction\", Date, Description, Cost, Type, Status from '" << thisAccount << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "FIRST" + qry->lastError().text());
    }
    else
    {
        model->setQuery(*qry);
        ui->tableView_History->setModel(model);
    }

    queryString = "";
    queryStream << "SELECT Balance from '" << thisAccount << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
            balance += qry->value(0).toInt();
        }
    }

    ui->label_balance->setText(QString::number(balance));
    ui->tableView_History->horizontalHeader()->setStretchLastSection(true);
    conn.connClose();


}

customerProfile::~customerProfile()
{
    delete ui;
}

void customerProfile::on_tableView_History_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    qint32 transaction = index.sibling(row, 0).data(Qt::DisplayRole).toInt();
    QString date = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    QString description = index.sibling(row, 2).data(Qt::DisplayRole).toString();
    qint32 total = index.sibling(row, 3).data(Qt::DisplayRole).toDouble();
    QString type = index.sibling(row, 4).data(Qt::DisplayRole).toString();
    QString status = index.sibling(row, 5).data(Qt::DisplayRole).toString();

    Spectacles *spectacles = new Spectacles(0, transaction, date, description, total, type, thisLast,
                                            thisFirst, thisPhone, thisAccount, status, this,
                                            thisAddress1, thisAddress2, globalName);
    spectacles->setModal(true);
    spectacles->show();
}


void customerProfile::on_commandLinkButton_newPurchase_clicked()
{
    NewPurchase *newPurchase = new NewPurchase(0, thisAddress1, thisAddress2, thisAccount, this, globalName);
    newPurchase->setModal(true);
    newPurchase->setWindowFlags(Qt::Tool | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    newPurchase->show();
}

void customerProfile::on_commandLinkButton_3_clicked()
{
    this->hide();
}

void customerProfile::on_commandLinkButton_modify_clicked()
{
    ModifyProfile *modifyProfile = new ModifyProfile(0, thisAccount, this);
    modifyProfile->setModal(true);
    modifyProfile->show();
}
