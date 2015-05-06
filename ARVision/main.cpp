#include "login.h"
#include <QApplication>
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString target;

    {
    Database conn;
    conn.connOpen("Main");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select Location from Main";

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

    queryString = "";

    queryStream << "UPDATE 'Main'"
                << " SET Target = '" << target << "'";

    qry->prepare(queryString);
    qry->exec();

    conn.connClose();
    }

    Login w(0, target);
    w.show();

    return a.exec();
}
