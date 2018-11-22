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
    setupComboBoxes();
    ui->imageEditorWidget_2->setActivity(false);
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
    emit addImagesToPatient( getSelectedPatientIndex() );
}

void MainWindow::setupTableView()
{
    ui->tableView->setModel(&APPModel::shared().patientTableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    APPModel::shared().update();
}

void MainWindow::setupDelegates()
{
    connect(this,&MainWindow::removePatient,
            &APPCore::shared(),&APPCore::removePatient);
    connect(this,&MainWindow::addImagesToPatient,
            &APPCore::shared(),&APPCore::addImagesToPatient);
    connect(ui->tableWidget,&QTableWidget::itemClicked,this,&MainWindow::previewImageDidSelected);
    connect(ui->tableWidget_2,&QTableWidget::itemClicked,this,&MainWindow::markImageDidSelected);
    connect(ui->imageEditorWidget,&ImageEditor::imageDidZoomed,this,&MainWindow::updateZoomLabel);
    connect(this,&MainWindow::saveMarksToDataBase,&APPCore::shared(),&APPCore::saveMarkToDB);
    connect(&APPCore::shared(),&APPCore::activateImageForEdit,ui->imageEditorWidget,&ImageEditor::setActivity);
}

void MainWindow::setupComboBoxes()
{
    ui->comboBox->addItems(QStringList{"black", "red", "blue", "green", "yellow", "magenta", "darkblue", "darkgreen"});
    ui->comboBox_2->addItems(QStringList{"1","2","3","4","5","6","7","8","9","10"});
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
    APPModel::shared().update();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) // select tab - images
{
    if (index == 1)
    {
        QModelIndex patientIndex = getSelectedPatientIndex();
        if (!patientIndex.isValid())
        {
            ui->tabWidget->setCurrentIndex(0);
            return;
        }
        QVector<pImageModel> images = APPCore::shared().getPreviewImagesForPatient(patientIndex);

        ui->tableWidget->setColumnCount(images.count());
        ui->tableWidget->setRowCount(1);

        repeat(i,images.count())
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            ui->tableWidget->setRowHeight(i,110);
            ui->tableWidget->setColumnWidth(i,110);
            QPixmap pixmap(images.at(i).get()->path);
            if (i == 0)
            {
                ui->imageEditorWidget->setImage(pixmap);
                ui->imageEditorWidget->currentImageID = images.at(i)->id;
            }
            item->setData(Qt::DecorationRole, pixmap.scaled(100, 100,Qt::KeepAspectRatio));
            ui->tableWidget->setItem(0,i,item);
        }
    }

    if (index == 2)
    {
        qDebug() << "tab marks did tap";
        int imageID = ui->imageEditorWidget->currentImageID;
        if (imageID == 0)
        {
            AppMessage("Выбор изображения", "Неверно выбрано изображение");
            return;
        }
        else
        {
            QVector<pMarkModel> marks = APPCore::shared().getMarkImagesForImage(imageID);
            qDebug() << "marks count = " << marks.count();

            ui->tableWidget_2->setColumnCount(marks.count());
            ui->tableWidget_2->setRowCount(1);

            repeat(i,marks.count())
            {
                QTableWidgetItem *item = new QTableWidgetItem;
                ui->tableWidget_2->setRowHeight(i,110);
                ui->tableWidget_2->setColumnWidth(i,110);
                QPixmap pixmap(marks.at(i)->path);
                if (i == 0)
                {
                    ui->imageEditorWidget_2->setImage(pixmap);
                    ui->imageEditorWidget_2->currentImageID = marks.at(i)->id;
                }
                item->setData(Qt::DecorationRole, pixmap.scaled(100, 100,Qt::KeepAspectRatio));
                ui->tableWidget_2->setItem(0,i,item);
            }
        }
    }
}

void MainWindow::previewImageDidSelected(QTableWidgetItem *item)
{
    int position = item->column();
    QModelIndex patientIndex = getSelectedPatientIndex();
    pImageModel imageModel = APPCore::shared().getSourceImageForPatient(patientIndex, position);

    ui->imageEditorWidget->setImage(QPixmap(imageModel->path));
    ui->imageEditorWidget->currentImageID = imageModel->id;
}

void MainWindow::markImageDidSelected(QTableWidgetItem *item)
{
    int position = item->column();
    pMarkModel mark = APPCore::shared().getSourceMarkImage(ui->imageEditorWidget->currentImageID, position);

    ui->imageEditorWidget_2->setImage(QPixmap(mark->path));
    ui->imageEditorWidget_2->currentImageID = mark->id;
}

void MainWindow::updateZoomLabel(qreal value)
{
    ui->label_9->setText(QString::number(value,'G',5) + "%");
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

void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    ui->imageEditorWidget->thickness = arg1.toDouble();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->imageEditorWidget->color = QColor(arg1);
}

void MainWindow::on_pushButton_3_clicked() // save marks
{
    if (ui->imageEditorWidget->isActive())
    {
        qDebug() << "imageID = " << ui->imageEditorWidget->currentImageID << " grab = " << !ui->imageEditorWidget->grab().isNull();
        emit saveMarksToDataBase(ui->imageEditorWidget->currentImageID,
                                 ui->imageEditorWidget->grab());
    }
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->imageEditorWidget->setTool(DrawTool::Rect);
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->imageEditorWidget->setTool(DrawTool::Pencil);
}

void MainWindow::on_radioButton_6_clicked()
{
    ui->imageEditorWidget->setTool(DrawTool::Line);
}
