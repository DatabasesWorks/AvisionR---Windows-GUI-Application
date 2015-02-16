#ifndef NEWFRAMES_H
#define NEWFRAMES_H

#include <QDialog>
#include "frames.h"

namespace Ui {
class NewFrames;
}

class NewFrames : public QDialog
{
    Q_OBJECT

public:
    explicit NewFrames(QWidget *parent = 0, Frames *frames = new Frames());
    ~NewFrames();

    Frames *thisFrame;

private slots:
    void on_commandLinkButton_add_clicked();

    void on_commandLinkButton_cancel_clicked();

private:
    Ui::NewFrames *ui;
};

#endif // NEWFRAMES_H
