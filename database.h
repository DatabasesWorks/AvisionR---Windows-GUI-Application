#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>

class Database
{
public:
    Database();

    QSqlDatabase mydb;
    void connClose()
    {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool connOpen(QString select)
    {
        if(select == "customersBasic")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName("C:/SQL/customersBasic.db");

            if(!mydb.open())
            {
                qDebug()<<("Database Failed to connect");
                return false;
            }
            else
            {
                qDebug()<<("Connected to Database..");
                return true;
            }
       }
       if(select == "customersDetail")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName("C:/SQL/Customers.db");

            if(!mydb.open())
            {
                qDebug()<<("Database Failed to connect");
                return false;
            }
            else
            {
                qDebug()<<("Connected to Database..");
                return true;
            }
       }
       else if(select == "Log")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName(QDir::currentPath() + "/data/Log.db");

           if(!mydb.open())
           {
               qDebug()<<("Database Failed to connect");
               return false;
           }
           else
           {
               qDebug()<<("Connected to Database..");
               return true;
           }
       }
        else if(select == "Employee")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName("C:/SQL/Employees.db");

            if(!mydb.open())
            {
                qDebug()<<("Database Failed to connect");
                return false;
            }
            else
            {
                qDebug()<<("Connected to Database..");
                return true;
            }
        }
       else if(select == "Master")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName("C:/SQL/Master.db");

           if(!mydb.open())
           {
               qDebug()<<("Database Failed to connect");
               return false;
           }
           else
           {
               qDebug()<<("Connected to Database..");
               return true;
           }
       }
       else if(select == "Clock")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName("C:/SQL/Clock.db");

           if(!mydb.open())
           {
               qDebug()<<("Database Failed to connect");
               return false;
           }
           else
           {
               qDebug()<<("Connected to Database..");
               return true;
           }
       }
       else
       {
           qDebug()<<("Failed: Connection Error");
           return false;
       }
    }

};

#endif // DATABASE_H
