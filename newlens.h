#ifndef NEWLENS_H
#define NEWLENS_H

#include <QDialog>
#include "lens.h"

namespace Ui {
class NewLens;
}

class NewLens : public QDialog
{
    Q_OBJECT

public:
    explicit NewLens(QWidget *parent = 0, Lens *lens = new Lens());
    ~NewLens();

    Lens *thisLens;

private slots:
    void on_commandLinkButton_add_2_clicked();

    void on_commandLinkButton_cancel_2_clicked();

private:
    Ui::NewLens *ui;
};

#endif // NEWLENS_H
