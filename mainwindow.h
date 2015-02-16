#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, QString empID = "", QString name = "",
                        bool admin = true, QString target = "");
    ~MainWindow();

    QString currentEmpID;
    QString globalName;
    QString thisTarget;
    bool isAdmin;

private slots:

    void on_pushButton_Logout_clicked();

    void on_pushButton_Customers_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Users_clicked();

    void on_pushButton_ClockOut_clicked();

    void on_pushButton_Frames_clicked();

    void on_pushButton_Lens_clicked();

    void on_pushButton_Log_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
