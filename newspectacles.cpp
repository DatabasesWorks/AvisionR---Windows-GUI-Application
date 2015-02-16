#include "newspectacles.h"
#include "ui_newspectacles.h"
#include "database.h"
#include "frames.h"
#include "lens.h"

NewSpectacles::NewSpectacles(QWidget *parent, QString type, QString Address1,
                             QString Address2, qint32 Account, customerProfile *profile, QString name) :
    QDialog(parent),
    ui(new Ui::NewSpectacles)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    {
        QPixmap pix("pixMap/LensSmallLeft.png");
        QIcon icon(pix);
        ui->pushButton_LensLeft->setIcon(icon);
        ui->pushButton_LensLeft->setIconSize(pix.size());
    }

    {
        QPixmap pix("pixMap/LensSmallRight.png");
        QIcon icon(pix);
        ui->pushButton_LensRight->setIcon(icon);
        ui->pushButton_LensRight->setIconSize(pix.size());
    }

    {
        QPixmap pix("pixMap/FramesSmall.png");
        QIcon icon(pix);
        ui->pushButton_Frames->setIcon(icon);
        ui->pushButton_Frames->setIconSize(pix.size());
    }


    globalName = name;
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

    else if(type == "Custom")
    {
        ui->label_LensMaterial->setText("Item 1");
        ui->label_FrameStyle->setText("Item 2");
        ui->lineEdit_LensMaterialRight->setEnabled(false);
        ui->lineEdit_LensMaterialRight->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");

        ui->label_LensPrice->setText("Item 1  $");
        ui->label_FramePrice->setText("Item 2  $");
        ui->lineEdit_LensRight->setEnabled(false);
        ui->lineEdit_LensRight->setStyleSheet("background-color: #686868; \nborder: 1px solid #686868;");
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

    QString description;
    qint32 transaction = 0;
    qint32 balance = 0;
    QString thisStatus = "";
    qint32 total = ui->lineEdit_Total->text().toInt();
    qint32 depositPayment = ui->lineEdit_DepositPayment->text().toInt();

    QString LensMaterialLeft = ui->lineEdit_LensMaterialLeft->text();
    QString LensMaterialRight = ui->lineEdit_LensMaterialRight->text();
    QString frameStyle = ui->lineEdit_FrameStyle->text();

    if(LensMaterialLeft == LensMaterialRight)
        description = LensMaterialLeft + " " + frameStyle;
    else
        description = LensMaterialRight + " " + LensMaterialLeft + " " + frameStyle;

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
                   << "TotalInsetOS, DPDTotal, DPDOD, DPDOS, NPDTotal, NPDOD, NPDOS, EyeBridge, Temple, B, ED, "
                   << "FrameStyle, ColorTrim, StraightTop, RoundSegment, Trifocal, Blended, Progressive, Executive, UVProtection, "
                   << "ScratchCoat, HighIndex, AntiReflective, PGX, Transition, Tint, Notes, Balance, Status, Frame, LensLeft, "
                   << "LensRight, LensMaterialLeft, LensMaterialRight, Date, Description, Cost, Type, \"Transaction\", "
                   << paymentType
                   << ", Discount) "


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

                   << ui->lineEdit_Frame->text() << "', '"
                   << ui->lineEdit_LensLeft->text() << "', '"
                   << ui->lineEdit_LensRight->text() << "', '"
                   << LensMaterialLeft << "', '"
                   << LensMaterialRight << "', '"
                   << timeStamp << "', '"
                   << description << "', '"
                   << total << "', '"
                   << ui->label_type->text() << "', '"
                   << newTransaction << "', '"
                   << ui->lineEdit_DepositPayment->text() << "', '"
                   << ui->lineEdit_Discount->text() << "')";


        qry->prepare(queryString);

        if(!qry->exec())
        {
            QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " in Update");
        }
        else
        {}

        conn.connClose();
       }

       if(thisLensLeft != "")
       {
            Database conn;

            conn.connOpen("Lens");

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "UPDATE Lens SET Units=Units-1 WHERE \"#\" = '" << thisLensLeft << "'";

            qry->prepare(queryString);

            if(!qry->exec())
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text()+ " In Left");
            }
            else
            {
            }

            conn.connClose();
       }

       if(thisLensRight != "")
       {
            Database conn;

            conn.connOpen("Lens");

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "UPDATE Lens SET Units=Units-1 WHERE \"#\" = '" << thisLensRight << "'";

            qry->prepare(queryString);

            if(!qry->exec())
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " In Right");
            }
            else
            {
            }

            conn.connClose();
       }

       if(thisFrame != "")
       {
            Database conn;

            conn.connOpen("Frames");

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "UPDATE Frames SET Units=Units-1 WHERE \"#\" = '" << thisFrame << "'";

            qry->prepare(queryString);

            if(!qry->exec())
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }
            else
            {
            }

            conn.connClose();
       }

    }
    qint32 newLog = 0;
    {

    qint32 log = 0;
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
              newLog = qry->value(15).toInt();
        }
    }
    queryString = "";
    log = newLog + 1;
    queryStream << "UPDATE mastertable"
                << " SET Log = '" << log << "'";

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
    conn.connOpen("Log");

    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "INSERT INTO Log ('#', \"Date/Time\", User, \"Transaction\", Client, Description,"
                << " Type, \"+/-\", Amount) "
                << "VALUES ('"
                << newLog << "', '"
                << timeStamp << "', '"
                << globalName << "', '"
                << newTransaction << "', '"
                << thisAccount << "', '"
                << description << "', '"
                << paymentType << "', '"
                << "+" << "', '"
                << depositPayment << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {
        thisProfile->setup();
        this->hide();
    }

    conn.connClose();
    }
}

void NewSpectacles::on_lineEdit_Frame_textChanged(const QString &arg1)
{
    qint32 lensLeft = ui->lineEdit_LensLeft->text().toInt();
    qint32 lensRight = ui->lineEdit_LensRight->text().toInt();
    qint32 discount = ui->lineEdit_Discount->text().toInt();
    qint32 frame = arg1.toInt();
    qint32 total = lensLeft + lensRight + frame - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}

void NewSpectacles::on_lineEdit_LensLeft_textChanged(const QString &arg1)
{
    qint32 lensLeft = arg1.toInt();
    qint32 lensRight = ui->lineEdit_LensRight->text().toInt();
    qint32 frame = ui->lineEdit_Frame->text().toInt();
    qint32 discount = ui->lineEdit_Discount->text().toInt();
    qint32 total = lensLeft + lensRight + frame - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}

void NewSpectacles::on_lineEdit_LensRight_textChanged(const QString &arg1)
{
    qint32 lensRight = arg1.toInt();
    qint32 lensLeft = ui->lineEdit_LensLeft->text().toInt();
    qint32 frame = ui->lineEdit_Frame->text().toInt();
    qint32 discount = ui->lineEdit_Discount->text().toInt();
    qint32 total = lensRight + lensLeft + frame - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}

void NewSpectacles::on_pushButton_Frames_clicked()
{
    Frames *frames = new Frames(0, false);
    frames->setModal(true);
    frames->sendNewSpectacles(this);
    frames->show();
}

void NewSpectacles::on_pushButton_LensLeft_clicked()
{
    Lens *lens = new Lens(0, false);
    lens->setModal(true);
    lens->sendNewSpecatacles(this, "l");
    lens->show();
}

void NewSpectacles::on_pushButton_LensRight_clicked()
{
    Lens *lens = new Lens(0, false);
    lens->setModal(true);
    lens->sendNewSpecatacles(this, "r");
    lens->show();
}

void NewSpectacles::sendLens(QString lens, QString price, QString type, QString side)
{
    if(side == "l"){
        thisLensLeft = lens;
        ui->lineEdit_LensLeft->setText(price);
        ui->lineEdit_LensMaterialLeft->setText(type);
        ui->lineEdit_LensMaterialLeft->setEnabled(false);
        ui->lineEdit_LensLeft->setEnabled(false);
    }
    else if(side == "r"){
        thisLensRight = lens;
        ui->lineEdit_LensRight->setText(price);
        ui->lineEdit_LensMaterialRight->setText(type);
        ui->lineEdit_LensMaterialRight->setEnabled(false);
        ui->lineEdit_LensRight->setEnabled(false);
    }
}

void NewSpectacles::sendFrame(QString frame, QString price, QString type, QString color)
{
    thisFrame = frame;
    ui->lineEdit_Frame->setText(price);
    ui->lineEdit_FrameStyle->setText(type);
    ui->lineEdit_ColorTrim->setText(color);
    ui->lineEdit_Frame->setEnabled(false);
    ui->lineEdit_FrameStyle->setEnabled(false);
}




void NewSpectacles::on_lineEdit_Discount_textChanged(const QString &arg1)
{
    qint32 discount = arg1.toInt();
    qint32 frame = ui->lineEdit_Frame->text().toInt();
    qint32 lensLeft = ui->lineEdit_LensLeft->text().toInt();
    qint32 lensRight = ui->lineEdit_LensRight->text().toInt();
    qint32 total = lensRight + lensLeft + frame - discount;

    ui->lineEdit_Total->setText(QString::number(total));
    ui->lineEdit_Balance->setText(QString::number(total));
}

