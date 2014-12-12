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
    explicit MainWindow(QWidget *parent = 0, QString empID = "");
    ~MainWindow();

    QString currentEmpID;

private slots:

    void on_pushButton_Logout_clicked();

    void on_pushButton_Customers_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_Users_clicked();

    void on_pushButton_ClockOut_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
