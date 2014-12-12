#include "newspectacles.h"
#include "ui_newspectacles.h"
#include "database.h"

NewSpectacles::NewSpectacles(QWidget *parent, QString type, QString Address1,
                             QString Address2, qint32 Account, customerProfile *profile) :
    QDialog(parent),
    ui(new Ui::NewSpectacles)
{
    ui->setupUi(this);

    thisAddress1 = Address1;
    thisAddress2 = Address2;
    thisAccount = Account;
    thisProfile = profile;

    ui->label_type->setText(type);

    if(type == "Single Vision")
    {
        ui->lineEdit_SegHeighOD->setEnabled(false);
        ui->lineEdit_SegHeighOD->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_SegHeightOS->setEnabled(false);
        ui->lineEdit_SegHeightOS->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_AddOD->setEnabled(false);
        ui->lineEdit_AddOD->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_AddOS->setEnabled(false);
        ui->lineEdit_AddOS->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_InsetOD->setEnabled(false);
        ui->lineEdit_InsetOD->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_InsetOS->setEnabled(false);
        ui->lineEdit_InsetOS->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_TotalInsetOD->setEnabled(false);
        ui->lineEdit_TotalInsetOD->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->lineEdit_TotalInsetOS->setEnabled(false);
        ui->lineEdit_TotalInsetOS->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");
    }

}

NewSpectacles::~NewSpectacles()
{
    delete ui;
}

void NewSpectacles::on_commandLinkButton_cancel_clicked()
{
    this->hide();
}

void NewSpectacles::on_commandLinkButton_save_clicked()
{
    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");

    qint32 transaction = 0;
    qint32 balance = 0;
    QString thisStatus = "";
    qint32 total = ui->lineEdit_Total->text().toInt();
    qint32 depositPayment = ui->lineEdit_DepositPayment->text().toInt();

    QString lensMaterial = ui->lineEdit_LensMaterial->text();
    QString frameStyle = ui->lineEdit_FrameStyle->text();
    QString description = lensMaterial + " " + frameStyle;

    balance = total - depositPayment;

    QString paymentType = "Deposit";

    if(balance < 0)
    {
        QMessageBox::critical(this, tr("Error"), "Balance Cannot Be Greater Than Total Amount");
        return;
    }
    else if(balance == 0)
    {
        thisStatus = "Complete";
        paymentType = "Payment";
    }

    else
        thisStatus = "Pending";

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
              newTransaction = qry->value(1).toInt();
        }
    }
    queryString = "";
    transaction = newTransaction + 1;
    queryStream << "UPDATE mastertable"
                << " SET \"Transaction\" = '" << transaction << "'";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), "SECOND " + qry->lastError().text());
    }
    else
    {}

    conn.connClose();
   }
   {

       {
        Database conn;
        conn.connOpen("customersDetail");
        QSqlQuery * qry = new QSqlQuery(conn.mydb);

        QString queryString;
        QTextStream queryStream(&queryString);

        queryStream << "INSERT INTO '" << thisAccount << "'"

                   << " (SphereOD, CylinderOD, AxisOD, PrismOD, BCOD, DecInOD, OutOD, SphereOS, CylinderOS, AxisOS, "
                   << "PrismOS, BCOS, DecInOS, OutOS, AddOD, AddOS, SegHeightOD, SegHeightOS, InsetOD, InsetOS, TotalInsetOD, "
                   << "TotalInsetOS, DPDTotal, DPDOD, DPDOS, NPDTotal, NPDOD, NPDOS, EyeBridge, Temple, B, ED, LensMaterial, "
                   << "FrameStyle, ColorTrim, StraightTop, RoundSegment, Trifocal, Blended, Progressive, Executive, UVProtection, "
                   << "ScratchCoat, HighIndex, AntiReflective, PGX, Transition, Tint, Notes, Balance, Status, Lens, Frame, "
                   << " Date, Description, Cost, Type, \"Transaction\", "
                   << paymentType
                   << ") "

                   << "VALUES"

                   << " ('"
                   << ui->lineEdit_sphereOD->text() << "', '"
                   << ui->lineEdit_cylinderOD->text() << "', '"
                   << ui->lineEdit_axisOD->text() << "', '"
                   << ui->lineEdit_prismOD->text() << "', '"
                   << ui->lineEdit_BCOD->text() << "', '"
                   << ui->lineEdit_DecInOD->text() << "', '"
                   << ui->lineEdit_OutOD->text() << "', '"
                   << ui->lineEdit_sphereOS->text() << "', '"
                   << ui->lineEdit_cylinderOS->text() << "', '"
                   << ui->lineEdit_axisOS->text() << "', '"
                   << ui->lineEdit_prismOS->text() << "', '"
                   << ui->lineEdit_BCOS->text() << "', '"
                   << ui->lineEdit_DecInOS->text() << "', '"
                   << ui->lineEdit_OutOS->text() << "', '"
                   << ui->lineEdit_AddOD->text() << "', '"
                   << ui->lineEdit_AddOS->text() << "', '"
                   << ui->lineEdit_SegHeighOD->text() << "', '"
                   << ui->lineEdit_SegHeightOS->text() << "', '"
                   << ui->lineEdit_InsetOD->text() << "', '"
                   << ui->lineEdit_InsetOS->text() << "', '"
                   << ui->lineEdit_TotalInsetOD->text() << "', '"
                   << ui->lineEdit_TotalInsetOS->text() << "', '"
                   << ui->lineEdit_DPDTotal->text() << "', '"
                   << ui->lineEdit_DPDOD->text() << "', '"
                   << ui->lineEdit_DPDOS->text() << "', '"
                   << ui->lineEdit_NPDTotal->text() << "', '"
                   << ui->lineEdit_NPDOD->text() << "', '"
                   << ui->lineEdit_NPDOS->text() << "', '"
                   << ui->lineEdit_EyeBridge->text() << "', '"
                   << ui->lineEdit_Temple->text() << "', '"
                   << ui->lineEdit_B->text() << "', '"
                   << ui->lineEdit_ED->text() << "', '"
                   << lensMaterial << "', '"
                   << frameStyle << "', '"
                   << ui->lineEdit_ColorTrim->text() << "', '"
                   << ui->checkBox_StraightTop->isChecked() << "', '"
                   << ui->checkBox_RoundSegment->isChecked() << "', '"
                   << ui->checkBox_TriFocal->isChecked() << "', '"
                   << ui->checkBox_Blended->isChecked() << "', '"
                   << ui->checkBox_Progressive->isChecked() << "', '"
                   << ui->checkBox_Executive->isChecked() << "', '"
                   << ui->checkBox_UVProtection->isChecked() << "', '"
                   << ui->checkBox_ScratchCoat->isChecked() << "', '"
                   << ui->checkBox_HighIndex->isChecked() << "', '"
                   << ui->checkBox_AntiReflective->isChecked() << "', '"
                   << ui->checkBox_PGX->isChecked() << "', '"
                   << ui->checkBox_Transition->isChecked() << "', '"
                   << ui->lineEdit_Tint->text() << "', '"
                   << ui->textEdit_Notes->toPlainText() << "', '"
                   << balance << "', '"
                   << thisStatus << "', '"
                   << ui->lineEdit_Lens->text() << "', '"
                   << ui->lineEdit_Frame->text() << "', '"
                   << timeStamp << "', '"
                   << description << "', '"
                   << total << "', '"
                   << ui->label_type->text() << "', '"
                   << newTransaction << "', '"
                   << ui->lineEdit_DepositPayment->text() << "')";


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text());
        }
        else
        {
            QMessageBox::information(this, tr("AvisionR - Spectacles"), "Save Successful");
            thisProfile->setup();
            this->hide();
        }

        conn.connClose();
       }

    }
}

void NewSpectacles::on_lineEdit_Frame_textChanged(const QString &arg1)
{
    qint32 lens = ui->lineEdit_Lens->text().toInt();
    qint32 frame = arg1.toInt();
    qint32 total = lens + frame;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}

void NewSpectacles::on_lineEdit_Lens_textChanged(const QString &arg1)
{
    qint32 lens = arg1.toInt();
    qint32 frame = ui->lineEdit_Frame->text().toInt();
    qint32 total = lens + frame;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}
