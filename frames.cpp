#include "frames.h"
#include "ui_frames.h"
#include "database.h"
#include "newframes.h"
#include "editframe.h"

Frames::Frames(QWidget *parent, bool isMain) :
    QDialog(parent),
    ui(new Ui::Frames)
{
    ui->setupUi(this);

    thisIsMain = isMain;

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    ui->lineEdit_Frame->setPlaceholderText("Frame #");
    ui->lineEdit_Brand->setPlaceholderText("Brand");
    ui->lineEdit_Model->setPlaceholderText("Model");

    if(!isMain)
    {
        ui->commandLinkButton_Done->setVisible(false);
        ui->commandLinkButton_New->setVisible(false);
    }

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Frames");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from Frames");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_frames->setModel(model);
    conn.connClose();
    ui->tableView_frames->setColumnWidth(0, 45);
    ui->tableView_frames->horizontalHeader()->setStretchLastSection(true);
}

Frames::~Frames()
{
    delete ui;
}

void Frames::on_commandLinkButton_Search_clicked()
{
    Database conn;

    conn.connOpen("Frames");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    QSqlQueryModel * model = new QSqlQueryModel();

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT * FROM Frames WHERE \"#\" LIKE '%" << ui->lineEdit_Frame->text()
                << "%' AND \"Brand\" LIKE '%" << ui->lineEdit_Brand->text()
                << "%' AND \"Model\" LIKE '%" << ui->lineEdit_Model->text() << "%'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        model->setQuery(*qry);
        ui->tableView_frames->setModel(model);
    }

    conn.connClose();
}

void Frames::clearHelper()
{
    this->on_commandLinkButton_Clear_clicked();
}

void Frames::on_commandLinkButton_Clear_clicked()
{
    ui->lineEdit_Brand->setText("");
    ui->lineEdit_Frame->setText("");
    ui->lineEdit_Model->setText("");
    this->on_commandLinkButton_Search_clicked();
}

void Frames::on_commandLinkButton_New_clicked()
{
    NewFrames *newFrames = new NewFrames(0, this);
    newFrames->setModal(true);
    newFrames->show();
}

void Frames::on_commandLinkButton_Done_clicked()
{
    this->hide();
}

void Frames::sendNewSpectacles(NewSpectacles *newSpectacles)
{
    thisNewSpectacles = newSpectacles;
}

void Frames::on_tableView_frames_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    qint32 frameNumber = index.sibling(row, 0).data(Qt::DisplayRole).toInt();

    QString brand = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    QString model = index.sibling(row, 2).data(Qt::DisplayRole).toString();
    QString color = index.sibling(row, 3).data(Qt::DisplayRole).toString();
    QString price = index.sibling(row, 4).data(Qt::DisplayRole).toString();
    qint32 units = index.sibling(row, 5).data(Qt::DisplayRole).toInt();


    if(!thisIsMain)
    {
        if(units <= 0)
        {
            QMessageBox::critical(this, tr("Error"), "This Frame has 0 Units, Cannot Import to Customer unless you add more Units");
            return;
        }
        else
        {
            thisNewSpectacles->sendFrame(QString::number(frameNumber), price, brand + " " + model, color);
            this->hide();
        }
    }
    else
    {
        EditFrame *editFrame = new EditFrame(0, this, frameNumber);
        editFrame->setModal(true);
        editFrame->show();
    }

}
