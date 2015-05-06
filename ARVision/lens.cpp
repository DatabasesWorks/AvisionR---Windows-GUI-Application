#include "lens.h"
#include "ui_lens.h"
#include "database.h"
#include "newlens.h"
#include "editlens.h"

Lens::Lens(QWidget *parent, bool isMain) :
    QDialog(parent),
    ui(new Ui::Lens)
{
    ui->setupUi(this);

    thisIsMain = isMain;

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    ui->lineEdit_Lens->setPlaceholderText("#");
    ui->lineEdit_Type->setPlaceholderText("Type");
    ui->lineEdit_AddOns->setPlaceholderText("Add-Ons");

    if(!isMain)
    {
        ui->commandLinkButton_Done->setVisible(false);
        ui->commandLinkButton_New->setVisible(false);
    }

    Database conn;
    QSqlQueryModel * model = new QSqlQueryModel();

    conn.connOpen("Lens");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    qry->prepare("SELECT * from Lens");
    qry->exec();
    model->setQuery(*qry);
    ui->tableView_lens->setModel(model);
    conn.connClose();
    ui->tableView_lens->setColumnWidth(0, 100);
    ui->tableView_lens->setColumnWidth(1, 180);
    ui->tableView_lens->setColumnWidth(2, 280);
    ui->tableView_lens->setColumnWidth(3, 100);
    ui->tableView_lens->horizontalHeader()->setStretchLastSection(true);
}

Lens::~Lens()
{
    delete ui;
}

void Lens::on_commandLinkButton_Search_clicked()
{
    Database conn;

    conn.connOpen("Lens");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);
    QSqlQueryModel * model = new QSqlQueryModel();

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT * FROM Lens WHERE \"#\" LIKE '%" << ui->lineEdit_Lens->text()
                << "%' AND \"Type\" LIKE '%" << ui->lineEdit_Type->text()
                << "%' AND \"Add-Ons\" LIKE '%" << ui->lineEdit_AddOns->text() << "%'";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        model->setQuery(*qry);
        ui->tableView_lens->setModel(model);
    }

    conn.connClose();
}

void Lens::on_commandLinkButton_Clear_clicked()
{
    ui->lineEdit_AddOns->setText("");
    ui->lineEdit_Lens->setText("");
    ui->lineEdit_Type->setText("");
    this->on_commandLinkButton_Search_clicked();
}

void Lens::clearHelper()
{
    this->on_commandLinkButton_Clear_clicked();
}

void Lens::on_commandLinkButton_Done_clicked()
{
    this->hide();
}

void Lens::on_commandLinkButton_New_clicked()
{
    NewLens *newLens = new NewLens(0, this);
    newLens->setModal(true);
    newLens->show();
}

void Lens::sendNewSpecatacles(NewSpectacles *newSpectacles, QString side)
{
    thisNewSpectacles = newSpectacles;
    thisSide = side;
}

void Lens::on_tableView_lens_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    qint32 lensNumber = index.sibling(row, 0).data(Qt::DisplayRole).toInt();
    QString price = index.sibling(row, 3).data(Qt::DisplayRole).toString();
    QString type = index.sibling(row, 1).data(Qt::DisplayRole).toString();
    qint32 units = index.sibling(row, 4).data(Qt::DisplayRole).toInt();

    if(!thisIsMain)
    {
        if(units <= 0)
        {
            QMessageBox::critical(this, tr("Error"), "This Lens has 0 Units, Cannot Import to Customer unless you add more Units");
            return;
        }
        else
        {
            thisNewSpectacles->sendLens(QString::number(lensNumber), price, type, thisSide);
            this->hide();
        }
    }
    else
    {
        EditLens *editLens = new EditLens(0, this, lensNumber);
        editLens->setModal(true);
        editLens->show();
    }

}
