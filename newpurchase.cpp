#include "newpurchase.h"
#include "ui_newpurchase.h"
#include "newspectacles.h"
#include "customerprofile.h"
#include "newcontacts.h"

NewPurchase::NewPurchase(QWidget *parent, QString Address1,
                         QString Address2, qint32 Account, customerProfile *profile, QString name) :
    QDialog(parent),
    ui(new Ui::NewPurchase)
{
    ui->setupUi(this);

    QPixmap windowIconPix("pixMap/eye.png");
    QIcon windowIcon(windowIconPix);
    this->setWindowIcon(windowIcon);

    globalName = name;
    thisAddress1 = Address1;
    thisAddress2 = Address2;
    thisAccount = Account;
    thisProfile = profile;

    {
        QPixmap pix("pixMap/S.png");
        QIcon icon(pix);
        ui->pushButton_SingleVision->setIcon(icon);
        ui->pushButton_SingleVision->setIconSize(pix.size());
    }
    {
        QPixmap pix("pixMap/M.png");
        QIcon icon(pix);
        ui->pushButton_MultiFocal->setIcon(icon);
        ui->pushButton_MultiFocal->setIconSize(pix.size());
    }
    {
        QPixmap pix("pixMap/Contacts.png");
        QIcon icon(pix);
        ui->pushButton_Contacts->setIcon(icon);
        ui->pushButton_Contacts->setIconSize(pix.size());
    }
    {
        QPixmap pix("pixMap/C.png");
        QIcon icon(pix);
        ui->pushButton_Custom->setIcon(icon);
        ui->pushButton_Custom->setIconSize(pix.size());
    }
}

NewPurchase::~NewPurchase()
{
    delete ui;
}

void NewPurchase::on_pushButton_SingleVision_clicked()
{
    NewSpectacles *newspectacles = new NewSpectacles(0, "Single Vision",
                              thisAddress1, thisAddress2, thisAccount, thisProfile, globalName);
    newspectacles->setModal(true);
    newspectacles->show();
    this->hide();
}

void NewPurchase::on_pushButton_MultiFocal_clicked()
{
    NewSpectacles *newspectacles = new NewSpectacles(0, "MultiFocal",
                        thisAddress1, thisAddress2, thisAccount, thisProfile, globalName);
    newspectacles->setModal(true);
    newspectacles->show();
    this->hide();
}

void NewPurchase::on_pushButton_Contacts_clicked()
{
    NewContacts * newContacts = new NewContacts(0, thisAccount, thisProfile, globalName);
    newContacts->setModal(true);
    newContacts->show();
    this->hide();
}

void NewPurchase::on_pushButton_Custom_clicked()
{
    NewSpectacles *newspectacles = new NewSpectacles(0, "Custom",
                              thisAddress1, thisAddress2, thisAccount, thisProfile, globalName);
    newspectacles->setModal(true);
    newspectacles->show();
    this->hide();
}
