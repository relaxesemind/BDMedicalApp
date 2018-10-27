#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QStringList>

#include "Managers/databasemanager.h"
#include "Common/magic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTableView();
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
            this,&MainWindow::addPatientToTableView);
    form->show();
}

void MainWindow::addPatientToTableView(const PatientModel &patient)//slot
{
    DataBaseManager::shared().insert(DBConst::TABLE_NAME_PATIENT, patient);
    APPModel::shared().update();
}

void MainWindow::on_pushButton_8_clicked() //add images to patient
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,tr("BMP files"),
                                                          QDir::currentPath(),tr("Bitmap files (*.bmp);;All files (*.*)") );
    if (!filenames.empty()) {

    }
}

void MainWindow::setupTableView()
{
    DataBaseManager::shared().connectToDataBase();
    DataBaseManager::shared().init();
    APPModel::shared().initModels();
    ui->tableView->setModel(&APPModel::shared().patientTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    APPModel::shared().update();
}

void MainWindow::on_pushButton_7_clicked() // remove buttn
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    for (int i = 0; i < selection.count(); ++i) {
        QModelIndex idx = selection.at(i);
        int d = APPModel::shared().patientTableModel.data(idx).toInt();
        DataBaseManager::shared().remove(DBConst::TABLE_NAME_PATIENT,d);
    }
    APPModel::shared().update();
}

void MainWindow::on_pushButton_9_clicked() // refresh
{
    DataBaseManager::shared().optimizeTable(DBConst::TABLE_NAME_PATIENT);
    APPModel::shared().update();
}













