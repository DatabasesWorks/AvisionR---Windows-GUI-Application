#include "labprint.h"
#include "ui_labprint.h"
#include "database.h"

LabPrint::LabPrint(QWidget *parent, qint32 transaction, QString date, QString description, QString type,
                   QString fullName, QString Phone, qint32 account,
                   QString Address1, QString Address2) :
    QDialog(parent),
    ui(new Ui::LabPrint)
{
    ui->setupUi(this);

    QPixmap windowIconPix("/pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    ui->label_fullName->setText(fullName);
    ui->label_phoneNumber->setText(Phone);
    ui->label_Date->setText(date.left(10));
    ui->label_Transaction->setText(QString::number(transaction));
    ui->groupBox_Client->setTitle("Client " + QString::number(account));
    ui->label_type->setText(type);
    ui->label_Description->setText(description);
    ui->label_Address1->setText(Address1);
    ui->label_Address2->setText(Address2);

    {
    Database conn;
    conn.connOpen("Master");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "Select * from mastertable";


    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
            QString tempPhone = qry->value(11).toString();
            ui->label_bottom->setText("AvisionR " + qry->value(6).toString() + "" + qry->value(7).toString() +
                      " " + qry->value(8).toString() + ", " + qry->value(9).toString() + " "  +
                      qry->value(10).toString() + " (" + tempPhone.left(3) + ")" + tempPhone.mid(3,3) + "-" +
                      tempPhone.right(4));
        }
    }

    conn.connClose();
   }

    Database conn;
    conn.connOpen("customersDetail");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "SELECT * from '" << account << "' WHERE \"Transaction\" = " << transaction;

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {
        while(qry->next())
        {
            ui->lineEdit_sphereOD->setText(qry->value(5).toString());
            ui->lineEdit_cylinderOD->setText(qry->value(6).toString());
            ui->lineEdit_axisOD->setText(qry->value(7).toString());
            ui->lineEdit_prismOD->setText(qry->value(8).toString());
            ui->lineEdit_BCOD->setText(qry->value(9).toString());
            ui->lineEdit_DecInOD->setText(qry->value(10).toString());
            ui->lineEdit_OutOD->setText(qry->value(11).toString());
            ui->lineEdit_sphereOS->setText(qry->value(12).toString());
            ui->lineEdit_cylinderOS->setText(qry->value(13).toString());
            ui->lineEdit_axisOS->setText(qry->value(14).toString());
            ui->lineEdit_prismOS->setText(qry->value(15).toString());
            ui->lineEdit_BCOS->setText(qry->value(16).toString());
            ui->lineEdit_DecInOS->setText(qry->value(17).toString());
            ui->lineEdit_OutOS->setText(qry->value(18).toString());
            ui->lineEdit_AddOD->setText(qry->value(19).toString());
            ui->lineEdit_AddOS->setText(qry->value(20).toString());
            ui->lineEdit_SegHeighOD->setText(qry->value(21).toString());
            ui->lineEdit_SegHeightOS->setText(qry->value(22).toString());
            ui->lineEdit_InsetOD->setText(qry->value(23).toString());
            ui->lineEdit_InsetOS->setText(qry->value(24).toString());
            ui->lineEdit_TotalInsetOD->setText(qry->value(25).toString());
            ui->lineEdit_TotalInsetOS->setText(qry->value(26).toString());
            ui->lineEdit_DPDTotal->setText(qry->value(27).toString());
            ui->lineEdit_DPDOD->setText(qry->value(28).toString());
            ui->lineEdit_DPDOS->setText(qry->value(29).toString());
            ui->lineEdit_NPDTotal->setText(qry->value(30).toString());
            ui->lineEdit_NPDOD->setText(qry->value(31).toString());
            ui->lineEdit_NPDOS->setText(qry->value(32).toString());
            ui->lineEdit_EyeBridge_2->setText(qry->value(33).toString());
            ui->lineEdit_Temple_2->setText(qry->value(34).toString());
            ui->lineEdit_B_2->setText(qry->value(35).toString());
            ui->lineEdit_ED_2->setText(qry->value(36).toString());
            ui->lineEdit_LensMaterialLeft_2->setText(qry->value(37).toString());
            ui->lineEdit_LensMaterialRight_2->setText(qry->value(38).toString());
            ui->lineEdit_FrameStyle ->setText(qry->value(39).toString());
            ui->lineEdit_ColorTrim->setText(qry->value(40).toString());

            ui->checkBox_StraightTop->setChecked(qry->value(41).toBool());
            ui->checkBox_RoundSegment->setChecked(qry->value(42).toBool());
            ui->checkBox_TriFocal->setChecked(qry->value(43).toBool());
            ui->checkBox_Blended->setChecked(qry->value(44).toBool());
            ui->checkBox_Progressive->setChecked(qry->value(45).toBool());
            ui->checkBox_Executive->setChecked(qry->value(46).toBool());
            ui->checkBox_UVProtection->setChecked(qry->value(47).toBool());
            ui->checkBox_ScratchCoat->setChecked(qry->value(48).toBool());
            ui->checkBox_HighIndex->setChecked(qry->value(49).toBool());
            ui->checkBox_AntiReflective->setChecked(qry->value(50).toBool());
            ui->checkBox_PGX->setChecked(qry->value(51).toBool());
            ui->checkBox_Transition->setChecked(qry->value(52).toBool());

            ui->lineEdit_Tint->setText(qry->value(53).toString());
            ui->textEdit_Notes->setText(qry->value(56).toString());
        }
    }
}

LabPrint::~LabPrint()
{
    delete ui;
}
