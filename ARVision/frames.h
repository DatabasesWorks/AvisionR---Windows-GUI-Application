#ifndef FRAMES_H
#define FRAMES_H

#include <QDialog>
#include "newspectacles.h"

namespace Ui {
class Frames;
}

class Frames : public QDialog
{
    Q_OBJECT

public:
    explicit Frames(QWidget *parent = 0, bool isMain = true);
    ~Frames();

    bool thisIsMain;

    NewSpectacles *thisNewSpectacles;


    void clearHelper();
    void sendNewSpectacles(NewSpectacles *newSpectacles);

private slots:
    void on_commandLinkButton_Search_clicked();

    void on_commandLinkButton_Clear_clicked();

    void on_commandLinkButton_New_clicked();

    void on_commandLinkButton_Done_clicked();

    void on_tableView_frames_doubleClicked(const QModelIndex &index);

private:
    Ui::Frames *ui;
};

#endif // FRAMES_H
