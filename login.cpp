#include "login.h"
#include "ui_login.h"
#include "database.h"
#include "qdebug.h"
#include "QMessageBox"
#include "mainwindow.h"

Login::Login(QWidget *parent, QString target) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    thisTarget = target;

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    QPixmap pix("pixMap/eye.png");
    ui->label_6->setPixmap(pix);

    QPixmap pix2("pixMap/Gradientlogin2.png");
    ui->label_3->setPixmap(pix2);

    QPixmap pix3("pixMap/Userlogin1.png");
    ui->label->setPixmap(pix3);

    QPixmap pix4("pixMap/Passwordlogin.png");
    ui->label_2->setPixmap(pix4);

    QPalette palette = ui->label_AvisionR->palette();
    palette.setColor(ui->label_AvisionR->foregroundRole(), Qt::gray);
    ui->label_AvisionR->setPalette(palette);

    ui->lineEdit_User->setPlaceholderText("Username");
    ui->lineEdit_Password->setPlaceholderText("Password");
}

Login::~Login()
{
    delete ui;
}

void Login::on_lineEdit_User_selectionChanged()
{
    ui->lineEdit_User->setText("");
}

void Login::on_lineEdit_Password_selectionChanged()
{
    ui->lineEdit_Password->setText("");
}

void Login::on_commandLinkButton_Login_clicked()
{
    int dateCounter = 0;
    bool onClock = 0;
    QString username, password, name, empID;
    bool admin = false;

    username = ui->lineEdit_User->text();
    password = ui->lineEdit_Password->text();

    Database conn;

    if(!conn.connOpen("Employee"))
    {
        ui->label_Status->setText("Database Connection Fatal Error");
        qDebug () << "Database Connection Fatal Error in Login";
    }

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "select * from Employees where Username = '"+username +"' and Password='"+password +"'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        int count = 0;
        while(qry->next())
        {
            name = qry->value(0).toString();
            empID = qry->value(1).toString();
            admin = qry->value(4).toBool();
            count++;
        }
        if(count == 1)
        {
            ui->label_Status->setText("Username and Password Correct");

            this->hide();
            MainWindow *mainWindow = new MainWindow(0, empID, name, admin, thisTarget);
            mainWindow->showMaximized();

            onClock = 1;

//            if(admin)
//            {
//                qDebug()<<"IS ADMIN\n";
//                qDebug()<< admin;
//                connClose();
//                this->hide();
//                AdminMenu *adminMenu = new AdminMenu(0, name, true);
//                adminMenu->show();

//            }
//            else
//            {
//                qDebug()<<"NOT ADMIN";

//                connClose();
//                this->hide();

//                menu *mainMenu = new menu(0, name, false);
//                mainMenu->show();

//            }
        }
        else if(count > 1)
            ui->label_Status->setText("Duplicate Username and Password");
        else if(count < 1)
        {
            ui->label_Status->setText("Incorrect Username and Password");
            ui->label_Status->setStyleSheet("background-color: rgb(255, 67, 70);");
        }
        else
            ui->label_Status->setText("ERROR" );

    }

    conn.connClose();


    if(onClock)
    {
        {
        Database conn;

        if(!conn.connOpen("Employee"))
        {
            ui->label_Status->setText("Database Connection Fatal Error");
            qDebug () << "Database Connection Fatal Error in Login";
        }

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "UPDATE 'Employees'"
                    << " SET ONCLOCK = '1' where Username = '"+username +"' and Password='"+password +"'";


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }
        else
        {}

        conn.connClose();
        }

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

        if(!conn.connOpen("Clock"))
        {
            ui->label_Status->setText("Database Connection Fatal Error");
            qDebug () << "Database Connection Fatal Error in Login";
        }

        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "SELECT * from '" << empID << "'"
                    << " WHERE Date = '" << date << "'";

        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }
        else
        {
            while(qry->next())
            {
                dateCounter++;
            }
        }

        if(dateCounter == 0)
        {
            queryString = "";
            queryStream << "INSERT INTO '" << empID << "'"
                        << "(Date, 'Time In') VALUES ('"
                        << date << "', '" << time << "')";


            qry->prepare(queryString);

            if(!qry->exec())
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }
            else
            {}
        }

        conn.connClose();
        }
    }
}

void Login::on_lineEdit_User_textChanged()
{
    ui->label_Status->setText("");
    ui->label_Status->setStyleSheet("");
}

void Login::on_lineEdit_Password_textChanged()
{
    ui->label_Status->setText("");
    ui->label_Status->setStyleSheet("");
}
