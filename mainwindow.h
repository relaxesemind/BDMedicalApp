#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "patientinputform.h"
#include "searchform.h"
#include "appmodel.h"
#include "appcore.h"
#include "imageeditor.h"

#include <QMainWindow>
#include <QColor>
#include <QTableWidgetItem>
#include <QLineF>
#include <QStack>

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

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void previewImageDidSelected(QTableWidgetItem *item);

    void markImageDidSelected(QTableWidgetItem *item);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void previewImageDidDoubleClicked(QTableWidgetItem *item);

    void on_pushButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

public slots:

    void updateZoomLabel(qreal value);

signals:
    void removePatient(const QModelIndex& idx);
    void removeImage(const QModelIndex& idx, int);
    void addImagesToPatient(const QModelIndex& idx);
    void saveMarksToDataBase(int, const QPixmap& pixmap);

private:
    QModelIndex getSelectedPatientIndex();
    void setupTableView();
    void setupDelegates();
    void setupComboBoxes();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
