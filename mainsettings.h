#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QDialog>

namespace Ui {
class MainSettings;
}

class MainSettings : public QDialog
{
    Q_OBJECT

public:
    explicit MainSettings(QWidget *parent = 0);
    ~MainSettings();


    QString tempPhone;

private slots:

    void on_commandLinkButton_save_clicked();

private:
    Ui::MainSettings *ui;
};

#endif // MAINSETTINGS_H
