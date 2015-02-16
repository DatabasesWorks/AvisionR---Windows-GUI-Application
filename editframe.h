#ifndef EDITFRAME_H
#define EDITFRAME_H

#include <QDialog>
#include "frames.h"

namespace Ui {
class EditFrame;
}

class EditFrame : public QDialog
{
    Q_OBJECT

public:
    explicit EditFrame(QWidget *parent = 0, Frames *frames = new Frames(), qint32 frameNumber = 0);
    ~EditFrame();

    Frames *thisFrame;
    qint32 thisFrameNumber;

private slots:
    void on_commandLinkButton_cancel_3_clicked();

    void on_commandLinkButton_Update_clicked();

    void on_commandLinkButton_Delete_clicked();

private:
    Ui::EditFrame *ui;
};

#endif // EDITFRAME_H
