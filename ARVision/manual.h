#ifndef MANUAL_H
#define MANUAL_H

#include <QDialog>
#include "log.h"

namespace Ui {
class Manual;
}

class Manual : public QDialog
{
    Q_OBJECT

public:
    explicit Manual(QWidget *parent = 0, QString name = "", Log *log = new Log());
    ~Manual();

    QString globalName;
    Log *thisLog;

private slots:
    void on_commandLinkButton_Log_clicked();

private:
    Ui::Manual *ui;
};

#endif // MANUAL_H
