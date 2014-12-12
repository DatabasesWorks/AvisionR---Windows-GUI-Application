#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "customers.h"
#include "mainsettings.h"
#include "usermanagement.h"
#include <QDateTime>
#include "database.h"

MainWindow::MainWindow(QWidget *parent, QString empID) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentEmpID = empID;

    this->setStyleSheet("background-color: #262626;");

    QPixmap pix("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/logout_icon.png");
    QIcon icon(pix);
    ui->pushButton_Logout->setIcon(icon);
    ui->pushButton_Logout->setIconSize(pix.size());

    QPixmap pix2("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/customers_Icon.png");
    QIcon icon2(pix2);
    ui->pushButton_Customers->setIcon(icon2);
    ui->pushButton_Customers->setIconSize(pix2.size());

    QPixmap pix3("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/settings.png");
    QIcon icon3(pix3);
    ui->pushButton_Settings->setIcon(icon3);
    ui->pushButton_Settings->setIconSize(pix3.size());

    QPixmap pix4("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/users.png");
    QIcon icon4(pix4);
    ui->pushButton_Users->setIcon(icon4);
    ui->pushButton_Users->setIconSize(pix4.size());

    QPixmap pix5("C:/Users/Andrew/Dropbox/Computer Science/Projects/ARVision/pixMap/clock.png");
    QIcon icon5(pix5);
    ui->pushButton_ClockOut->setIcon(icon5);
    ui->pushButton_ClockOut->setIconSize(pix5.size());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Logout_clicked()
{
    this->hide();

    Login *login = new Login();
    login->show();
}

void MainWindow::on_pushButton_Customers_clicked()
{
    Customers *customers = new Customers();
    customers->setModal(true);
    customers->show();
}

void MainWindow::on_pushButton_Settings_clicked()
{
    MainSettings * mainSettings = new MainSettings();
    mainSettings->setModal(true);

    mainSettings->show();
}

void MainWindow::on_pushButton_Users_clicked()
{
    UserManagement *userManagement = new UserManagement();
    userManagement->setup();
    userManagement->setModal(true);
    userManagement->show();

}

void MainWindow::on_pushButton_ClockOut_clicked()
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

        queryStream << "UPDATE '" << currentEmpID <<"'"
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
        qDebug () << "Database Connection Fatal Error in Login";
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE 'Employees'"
                << " SET ONCLOCK = '0' where ID = '" << currentEmpID << "'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {}

    conn.connClose();
    }



    this->hide();

    Login *login = new Login();
    login->show();
}
