#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "patientinputform.h"
#include "appmodel.h"
#include "Common/Models/models.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_6_clicked();

    void addPatientToTableView(const PatientModel& patient);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

private:
    void setupTableView();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
