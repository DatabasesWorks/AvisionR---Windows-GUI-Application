#include "newframes.h"
#include "ui_newframes.h"
#include "database.h"

NewFrames::NewFrames(QWidget *parent, Frames *frames) :
    QDialog(parent),
    ui(new Ui::NewFrames)
{
    ui->setupUi(this);

    thisFrame = frames;

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

}

NewFrames::~NewFrames()
{
    delete ui;
}

void NewFrames::on_commandLinkButton_add_clicked()
{
    qint32 newFrame = 0;
    {

    qint32 frame = 0;

    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from mastertable";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 1");
    }
    else
    {
        while(qry->next())
        {
              newFrame = qry->value(13).toInt();
        }
    }
    queryString = "";
    frame = newFrame + 1;
    queryStream << "UPDATE mastertable"
                << " SET Frame = '" << frame << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text() + " 2");
    }
    else
    {}

    conn.connClose();
    }

    {
    Database conn;
    conn.connOpen("Frames");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Frames ('#', Brand, Model, Color, Price, Units) "
                << "VALUES ('"
                << newFrame << "', '"
                << ui->lineEdit_Brand->text() << "', '"
                << ui->lineEdit_Model->text() << "', '"
                << ui->lineEdit_Color->text() << "', '"
                << ui->lineEdit_Price->text() << "', '"
                << QString::number(ui->spinBox_units->value()) << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {}

    conn.connClose();
    }

    thisFrame->clearHelper();
    this->hide();
}

void NewFrames::on_commandLinkButton_cancel_clicked()
{
    this->hide();
}
