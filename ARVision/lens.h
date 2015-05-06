#ifndef LENS_H
#define LENS_H

#include <QDialog>
#include "newspectacles.h"

namespace Ui {
class Lens;
}

class Lens : public QDialog
{
    Q_OBJECT

public:
    explicit Lens(QWidget *parent = 0, bool isMain= true);
    ~Lens();
    bool thisIsMain;
    NewSpectacles *thisNewSpectacles;
    QString thisSide;

    void clearHelper();
    void sendNewSpecatacles(NewSpectacles *newSpectacles, QString side);

private slots:
    void on_commandLinkButton_Search_clicked();

    void on_commandLinkButton_Clear_clicked();

    void on_commandLinkButton_Done_clicked();

    void on_commandLinkButton_New_clicked();

    void on_tableView_lens_doubleClicked(const QModelIndex &index);

private:
    Ui::Lens *ui;
};

#endif // LENS_H
