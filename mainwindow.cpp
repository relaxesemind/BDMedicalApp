#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>

#include "Managers/databasemanager.h"
#include "Common/magic.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupTableView();
    setupDelegates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_6_clicked()//add patient
{
    PatientInputForm *form = new PatientInputForm(this);
    form->setModal(true);
    connect(form,&PatientInputForm::patientData,
            &APPCore::shared(),&APPCore::addPatient);
    form->show();
}

void MainWindow::on_pushButton_8_clicked() //add images to patient
{
    QModelIndex index = getSelectedPatientIndex();
    emit addImagesToPatient(index);
}

void MainWindow::setupTableView()
{
    ui->tableView->setModel(&APPModel::shared().patientTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0,true);
    APPModel::shared().update();
}

void MainWindow::setupDelegates()
{
    connect(this,&MainWindow::removePatient,
            &APPCore::shared(),&APPCore::removePatient);
    connect(this,&MainWindow::addImagesToPatient,
            &APPCore::shared(),&APPCore::addImagesToPatient);
}

void MainWindow::on_pushButton_7_clicked() // remove buttn
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();

    repeat(i,selection.count())
    {
        emit removePatient(selection.at(i));
    }
}

void MainWindow::on_pushButton_9_clicked() // refresh
{
}

void MainWindow::on_tabWidget_tabBarClicked(int index) // select tab - images
{
    if (index != 1) {
        return;
    }

    QModelIndex patientIndex = getSelectedPatientIndex();
    QStack<QPixmap> images = APPCore::shared().getImagesForPatient(patientIndex);

    ui->tableWidget->setColumnCount(images.count());
    ui->tableWidget->setRowCount(1);
    int i = 0;

    while (!images.isEmpty())
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        ui->tableWidget->setRowHeight(i,110);
        ui->tableWidget->setColumnWidth(i,110);

        item->setData(Qt::DecorationRole, images.pop().scaled(100, 100,Qt::KeepAspectRatio));
        ui->tableWidget->setItem(0,i,item);
        ++i;
    }
}

QModelIndex MainWindow::getSelectedPatientIndex()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();

    if (selection.empty() || selection.size() > 1) {
        AppMessage("Ошибка","Неверно выбран пациент");
        return QModelIndex();
    }
    else
    {
        return selection.first();
    }
}









