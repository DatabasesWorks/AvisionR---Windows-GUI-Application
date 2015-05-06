#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "customers.h"
#include "mainsettings.h"
#include "usermanagement.h"
#include <QDateTime>
#include "database.h"
#include "frames.h"
#include "lens.h"
#include "log.h"

MainWindow::MainWindow(QWidget *parent, QString empID, QString name, bool admin, QString target) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentEmpID = empID;
    globalName = name;
    isAdmin = admin;
    thisTarget = target;



    if(!admin)
    {
        ui->pushButton_Log->setVisible(false);
        ui->label_Log->setVisible(false);

        ui->pushButton_Users->setVisible(false);
        ui->label_Users->setVisible(false);

        ui->pushButton_Settings->setVisible(false);
        ui->label_Settings->setVisible(false);
    }

    this->setStyleSheet("background-color: #262626;");

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    QPixmap pix("pixMap/logout_icon.png");
    QIcon icon(pix);
    ui->pushButton_Logout->setIcon(icon);
    ui->pushButton_Logout->setIconSize(pix.size());

    QPixmap pix2("pixMap/customers_Icon.png");
    QIcon icon2(pix2);
    ui->pushButton_Customers->setIcon(icon2);
    ui->pushButton_Customers->setIconSize(pix2.size());

    QPixmap pix3("pixMap/settings.png");
    QIcon icon3(pix3);
    ui->pushButton_Settings->setIcon(icon3);
    ui->pushButton_Settings->setIconSize(pix3.size());

    QPixmap pix4("pixMap/users.png");
    QIcon icon4(pix4);
    ui->pushButton_Users->setIcon(icon4);
    ui->pushButton_Users->setIconSize(pix4.size());

    QPixmap pix5("pixMap/clock.png");
    QIcon icon5(pix5);
    ui->pushButton_ClockOut->setIcon(icon5);
    ui->pushButton_ClockOut->setIconSize(pix5.size());

    QPixmap pix6("pixMap/log.png");
    QIcon icon6(pix6);
    ui->pushButton_Log->setIcon(icon6);
    ui->pushButton_Log->setIconSize(pix6.size());

    QPixmap pix7("pixMap/frames.png");
    QIcon icon7(pix7);
    ui->pushButton_Frames->setIcon(icon7);
    ui->pushButton_Frames->setIconSize(pix7.size());

    QPixmap pix8("pixMap/lens.png");
    QIcon icon8(pix8);
    ui->pushButton_Lens->setIcon(icon8);
    ui->pushButton_Lens->setIconSize(pix8.size());

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
    Customers *customers = new Customers(0, globalName);
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

void MainWindow::on_pushButton_Frames_clicked()
{
    Frames *frames = new Frames(0, true);
    frames->setModal(true);
    frames->show();
}

void MainWindow::on_pushButton_Lens_clicked()
{
    Lens *lens = new Lens(0, true);
    lens->setModal(true);
    lens->show();
}

void MainWindow::on_pushButton_Log_clicked()
{
    Log *log = new Log(0, globalName);
    log->setModal(true);
    log->setup();
    log->show();

}
