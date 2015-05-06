#ifndef EDITLENS_H
#define EDITLENS_H

#include <QDialog>
#include "lens.h"

namespace Ui {
class EditLens;
}

class EditLens : public QDialog
{
    Q_OBJECT

public:
    explicit EditLens(QWidget *parent = 0, Lens *lens = new Lens(), qint32 lensNumber = 0);
    ~EditLens();

    Lens *thisLens;
    qint32 thisLensNumber;

private slots:
    void on_commandLinkButton_cancel_2_clicked();

    void on_commandLinkButton_Update_clicked();

    void on_commandLinkButton_Delete_clicked();

private:
    Ui::EditLens *ui;
};

#endif // EDITLENS_H
