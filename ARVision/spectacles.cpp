#include "spectacles.h"
#include "ui_spectacles.h"
#include "database.h"
#include "customerprofile.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QPainter>
#include "spectaclesprint.h"

Spectacles::Spectacles(QWidget *parent, qint32 transaction, QString date, QString description, int total, QString type,
                       QString Last, QString First, QString Phone, qint32 account, QString status, customerProfile *profile,
                       QString Address1, QString Address2, QString name) :
    QDialog(parent),
    ui(new Ui::Spectacles)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    globalName = name;
    thisStatus = status;
    thisAccount = account;
    thisTransaction = QString::number(transaction);
    ui->label_fullName->setText(First + " " + Last);
    ui->label_phoneNumber->setText(Phone);
    ui->label_Date->setText(date.left(10));
    ui->label_Transaction->setText(QString::number(transaction));
    ui->groupBox_Client->setTitle("Client " + QString::number(account));
    ui->label_type->setText("Type: " + type);
    ui->label_Description->setText("Description: " + description);
    ui->lineEdit_Total->setText(QString::number(total));
    ui->label_Address1->setText(Address1);
    ui->label_Address2->setText(Address2);

    thisProfile = profile;

    if(type == "Custom")
    {
        ui->label_LensMaterialLeft->setText("Item 1");
        ui->label_FrameStyle->setText("Item 2");
        ui->lineEdit_LensMaterialRight->setEnabled(false);

        ui->label_LensPrice_2->setText("Item 1  $");
        ui->label_FramePrice->setText("Item 2  $");
        ui->lineEdit_LensRight->setEnabled(false);
    }

    else if(type == "Contacts")
    {
        setWindowTitle("AvisionR - Contacts");
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
            ui->lineEdit_EyeBridge->setText(qry->value(33).toString());
            ui->lineEdit_Temple->setText(qry->value(34).toString());
            ui->lineEdit_B->setText(qry->value(35).toString());
            ui->lineEdit_ED->setText(qry->value(36).toString());
            ui->lineEdit_LensMaterialLeft->setText(qry->value(37).toString());
            ui->lineEdit_LensMaterialRight->setText(qry->value(38).toString());
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

            balance = qry->value(56).toInt();
            ui->lineEdit_Balance->setText(QString::number(balance));
            ui->textEdit_Notes->setText(qry->value(57).toString());
            ui->lineEdit_LensLeft->setText(qry->value(58).toString());
            ui->lineEdit_LensRight->setText(qry->value(59).toString());
            ui->lineEdit_Frame->setText(qry->value(60).toString());
            ui->lineEdit_Discount->setText(qry->value(63).toString());
        }
    }
}
Spectacles::~Spectacles()
{
    delete ui;
}

void Spectacles::on_commandLinkButton_cancel_clicked()
{
    this->hide();
}

void Spectacles::on_commandLinkButton_update_clicked()
{
    qint32 depositPayment = ui->lineEdit_DepositPayment->text().toInt();
    if(depositPayment > balance)
    {
        QMessageBox::critical(this, tr("Error"), "Error: Deposit/Payment Cannot Be Greater Than Current Balance");
        return;
    }
    else{
        balance -= depositPayment;
    }

    if(balance <= 0)
        thisStatus = "Complete";

    QString Temple = "";
            if(ui->lineEdit_Temple->text() != "")
                Temple = ui->lineEdit_Temple->text();
    Database conn;
    conn.connOpen("customersDetail");
    QSqlQuery * qry = new QSqlQuery(conn.mydb);

    QString queryString;
    QTextStream queryStream(&queryString);

    queryStream << "UPDATE '" << thisAccount << "'"
                << " SET SphereOD = '" << ui->lineEdit_sphereOD->text()
                << "', CylinderOD = '" << ui->lineEdit_cylinderOD->text()
                << "', AxisOD = '" << ui->lineEdit_axisOD->text()
                << "', PrismOD = '" << ui->lineEdit_prismOD->text()
                << "', BCOD = '" << ui->lineEdit_BCOD->text()

                << "', DecInOD = '" << ui->lineEdit_DecInOD->text()
                << "', OutOD = '" << ui->lineEdit_OutOD->text()
                << "', SphereOS = '" << ui->lineEdit_sphereOS->text()
                << "', CylinderOS = '" << ui->lineEdit_cylinderOS->text()
                << "', AxisOS = '" << ui->lineEdit_axisOS->text()

                << "', PrismOS = '" << ui->lineEdit_prismOS->text()
                << "', BCOS = '" << ui->lineEdit_BCOS->text()
                << "', DecInOS = '" << ui->lineEdit_DecInOS->text()
                << "', OutOS = '" << ui->lineEdit_OutOS->text()

                << "', AddOD = '" << ui->lineEdit_AddOD->text()
                << "', AddOS = '" << ui->lineEdit_AddOS->text()
                << "', SegHeightOD = '" << ui->lineEdit_SegHeighOD->text()\
                << "', SegHeightOS = '" << ui->lineEdit_SegHeightOS->text()
                << "', InsetOD = '" << ui->lineEdit_InsetOD->text()

                << "', InsetOS = '" << ui->lineEdit_InsetOS->text()
                << "', TotalInsetOD = '" << ui->lineEdit_TotalInsetOD->text()
                << "', TotalInsetOS = '" << ui->lineEdit_TotalInsetOS->text()
                << "', DPDTotal = '" << ui->lineEdit_DPDTotal->text()
                << "', DPDOD = '" << ui->lineEdit_DPDOD->text()

                << "', DPDOS = '" << ui->lineEdit_DPDOS->text()
                << "', NPDTotal = '" << ui->lineEdit_NPDTotal->text()
                << "', NPDOD = '" << ui->lineEdit_NPDOD->text()
                << "', NPDOS = '" << ui->lineEdit_NPDOS->text()
                << "', EyeBridge = '" << ui->lineEdit_EyeBridge->text()

                << "', Temple = '" << Temple
                << "', B = '" << ui->lineEdit_B->text()
                << "', ED = '" << ui->lineEdit_ED->text()
                << "', LensMaterialLeft = '" << ui->lineEdit_LensMaterialLeft->text()
                << "', LensMaterialRight = '" << ui->lineEdit_LensMaterialRight->text()
                << "', FrameStyle = '" << ui->lineEdit_FrameStyle->text()

                << "', ColorTrim = '" << ui->lineEdit_ColorTrim->text()
                << "', StraightTop = '" << ui->checkBox_StraightTop->isChecked()\
                << "', RoundSegment = '" << ui->checkBox_RoundSegment->isChecked()
                << "', Trifocal = '" << ui->checkBox_TriFocal->isChecked()
                << "', Blended = '" << ui->checkBox_Blended->isChecked()

                << "', Progressive = '" << ui->checkBox_Progressive->isChecked()
                << "', Executive = '" << ui->checkBox_Executive->isChecked()
                << "', UVProtection = '" << ui->checkBox_UVProtection->isChecked()
                << "', ScratchCoat = '" << ui->checkBox_ScratchCoat->isChecked()
                << "', HighIndex = '" << ui->checkBox_HighIndex->isChecked()

                << "', AntiReflective = '" << ui->checkBox_AntiReflective->isChecked()
                << "', PGX = '" << ui->checkBox_PGX->isChecked()
                << "', Transition = '" << ui->checkBox_Transition->isChecked()
                << "', Tint = '" << ui->lineEdit_Tint->text()
                << "', Notes = '" << ui->textEdit_Notes->toPlainText()

                << "', Balance = '" << balance
                << "', Status = '" << thisStatus
                << "', Payment = '" << depositPayment

                << "' WHERE \"Transaction\" = " << ui->label_Transaction->text();

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text());
    }
    else
    {

    }

    conn.connClose();

    QDateTime current = current.currentDateTime();
    QString timeStamp = current.toString("yyyy-MM-dd HH:mm:ss");

    QString lensMaterialLeft = ui->lineEdit_LensMaterialLeft->text();
    QString lensMaterialRight = ui->lineEdit_LensMaterialRight->text();
    QString frameStyle = ui->lineEdit_FrameStyle->text();
    QString description;

    if(lensMaterialLeft == lensMaterialRight)
        description = lensMaterialLeft + " " + frameStyle;
    else
        description = lensMaterialLeft + " " + lensMaterialRight + " " + frameStyle;

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
                << ui->label_Transaction->text() << "', '"
                << thisAccount << "', '"
                << description << "', '"
                << "Payment" << "', '"
                << "+" << "', '"
                << depositPayment << "')";

    qry->prepare(queryString);

    if(!qry->exec())
    {
        QMessageBox::critical(this, tr("Error"), qry->lastError().text() + " 3");
    }
    else
    {
        QMessageBox::information(this, tr("AvisionR - Spectacles"), "Update Successful");
        thisProfile->setup();
        this->hide();
    }

    conn.connClose();
    }

}

void Spectacles::on_commandLinkButton_print_clicked()
{
    SpectaclesPrint *spectaclesPrint = new SpectaclesPrint(0, ui->label_Transaction->text().toInt()
               , ui->label_Date->text(), ui->label_Description->text(), ui->label_type->text(),
               ui->label_fullName->text(), ui->label_phoneNumber->text(), thisAccount,
               ui->label_Address1->text(), ui->label_Address2->text());
    spectaclesPrint->setModal(true);
    spectaclesPrint->show();


}

void Spectacles::on_commandLinkButton_delete_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "AvisionR - Delete",
                                  "Are you sure you want to DELETE this Transaction from this Client?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        {
            Database conn;
            if(!conn.connOpen("customersDetail"))
            {
                qDebug()<<"Failed to open Data";
                return;
            }

            QSqlQuery * qry = new QSqlQuery(conn.mydb);

            QString queryString;
            QTextStream queryStream(&queryString);

            queryStream << "DELETE FROM '" << thisAccount << "' WHERE \"Transaction\" = " << thisTransaction;

            qry->prepare(queryString);

            if(qry->exec())
            {
                QMessageBox::information(this, tr("AvisionR - Delete"), "Transaction Deleted");
            }
            else
            {
                QMessageBox::critical(this, tr("Error"), qry->lastError().text());
            }

            conn.connClose();
        }

        thisProfile->setup();
        this->hide();
    }
}
