#include "log.h"
#include "ui_log.h"
#include "database.h"
#include "manual.h"

Log::Log(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::Log)
{
    ui->setupUi(this);

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    globalName = name;

    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd");

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "SELECT * from Log WHERE \"Date/Time\" >= '" << timeStamp + " 08:00:00" << "'";
    queryStream << " AND \"Date/Time\" <= '" << timeStamp + " 23:59:59" <<"'";

    qry->prepare(queryString);
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);
    conn.connClose();
    ui->dateTimeEdit_From->setDateTime(QDateTime::fromString(timeStamp + " 08:00:00", "yyyy-MM-dd HH:mm:ss"));
    ui->dateTimeEdit_To->setDateTime(QDateTime::fromString(timeStamp + " 23:59:59", "yyyy-MM-dd HH:mm:ss"));

    ui->tableView_Log->setColumnWidth(0, 45);
    ui->tableView_Log->setColumnWidth(1, 130);
    ui->tableView_Log->setColumnWidth(5, 180);
    ui->tableView_Log->setColumnWidth(7, 30);
    ui->tableView_Log->horizontalHeader()->setStretchLastSection(true);
}

void Log::setup()
{
    {
        Database conn;

        conn.connOpen("Employee");
        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        ui->comboBox_Users->addItem("Select a User");

        qry->prepare("SELECT Name from Employees");
        qry->exec();
        while(qry->next())
        {
            ui->comboBox_Users->addItem(qry->value(0).toString());
        }

        QModelIndex index = ui->comboBox_Users->model()->index(0, 0);
        QVariant v(0);
        ui->comboBox_Users->model()->setData(index, v, Qt::UserRole - 1);

        conn.connClose();
    }

}

Log::~Log()
{
    delete ui;
}

void Log::on_commandLinkButton_Search_clicked()
{
    QString from = ui->dateTimeEdit_From->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    QString to = ui->dateTimeEdit_To->dateTime().toString("yyyy-MM-dd HH:mm:ss");
    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "SELECT * from Log WHERE \"Date/Time\" >= '" << from << "'";
    queryStream << " AND \"Date/Time\" <= '"+to+"'";

    if(ui->comboBox_Users->currentText() != "Select a User")
    {
        queryStream << " AND User='" << ui->comboBox_Users->currentText() << "'";
    }

    queryStream << " AND \"Transaction\" LIKE '%" << ui->lineEdit_Transaction->text()
                << "%' AND \"Description\" LIKE '%" << ui->lineEdit_Description->text()
                << "%' AND \"Client\" LIKE '%" << ui->lineEdit_Client->text() << "%'";

    qry->prepare(queryString);
    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);

    conn.connClose();
}

void Log::on_commandLinkButton_Clear_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd");

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Log");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);
    queryStream << "SELECT * from Log WHERE \"Date/Time\" >= '" << timeStamp + " 08:00:00" << "'";
    queryStream << " AND \"Date/Time\" <= '" << timeStamp + " 23:59:59" <<"'";

    qry->prepare(queryString);
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_Log->setModel(model);
    conn.connClose();
    ui->dateTimeEdit_From->setDateTime(QDateTime::fromString(timeStamp + " 08:00:00", "yyyy-MM-dd HH:mm:ss"));
    ui->dateTimeEdit_To->setDateTime(QDateTime::fromString(timeStamp + " 23:59:59", "yyyy-MM-dd HH:mm:ss"));

    ui->tableView_Log->setColumnWidth(0, 45);
    ui->tableView_Log->setColumnWidth(1, 130);
    ui->tableView_Log->setColumnWidth(5, 180);
    ui->tableView_Log->setColumnWidth(7, 30);
    ui->tableView_Log->horizontalHeader()->setStretchLastSection(true);

    ui->comboBox_Users->setCurrentIndex(0);
    ui->lineEdit_Client->clear();
    ui->lineEdit_Description->clear();
    ui->lineEdit_Transaction->clear();

}

void Log::clearHelper()
{
    this->on_commandLinkButton_Clear_clicked();
}

void Log::on_commandLinkButton_Manual_clicked()
{
    Manual *manual = new Manual(0, globalName, this);
    manual->setModal(true);
    manual->show();
}
