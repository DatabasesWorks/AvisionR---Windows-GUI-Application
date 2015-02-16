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
        QString target;
        {
            QSqlDatabase mydbb;
            mydbb=QSqlDatabase::addDatabase("QSQLITE");

            mydbb.setDatabaseName("C:/SQL/Main.db");

            mydbb.open();

            QSqlQuery * qry = new QSqlQuery(mydbb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "Select Target from Main";

            qry->prepare(queryString);

            if(!qry->exec())
            {
            }
            else
            {
                while(qry->next())
                {
                      target = qry->value(0).toString();
                }
            }

            mydbb.close();
            mydbb.removeDatabase(QSqlDatabase::defaultConnection);
        }
        qDebug() << "target: ";
        qDebug() << target;
        if(select == "customersBasic")
        {
            mydb=QSqlDatabase::addDatabase("QSQLITE");

            mydb.setDatabaseName(target + "/SQL/customersBasic.db");

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

            mydb.setDatabaseName(target + "/SQL/Customers.db");

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

            mydb.setDatabaseName(target + "/SQL/Employees.db");

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

           mydb.setDatabaseName(target + "/SQL/Master.db");

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

           mydb.setDatabaseName(target + "/SQL/Clock.db");

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
       else if(select == "Frames")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName(target + "/SQL/Frames.db");

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

           mydb.setDatabaseName(target + "/SQL/Log.db");

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

       else if(select == "Lens")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName(target + "/SQL/Lens.db");

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
       else if(select == "Main")
       {
           mydb=QSqlDatabase::addDatabase("QSQLITE");

           mydb.setDatabaseName("C:/SQL/Main.db");

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
