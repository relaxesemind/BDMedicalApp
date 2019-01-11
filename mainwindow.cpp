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
    connect(ui->tableWidget,&QTableWidget::itemDoubleClicked,this, &MainWindow::previewImageDidDoubleClicked);
    connect(ui->imageEditorWidget,&ImageEditor::imageDidZoomed,this,&MainWindow::updateZoomLabel);
    connect(this,&MainWindow::removeImage,&APPCore::shared(),&APPCore::removeImage);
    connect(this,&MainWindow::saveMarksToDataBase,&APPCore::shared(),&APPCore::saveMarkToDB);
    connect(&APPCore::shared(),&APPCore::activateImageForEdit,ui->imageEditorWidget,&ImageEditor::setActivity);
}

void MainWindow::setupComboBoxes()
{
    ui->comboBox->addItems(QStringList{"black", "red", "blue", "green", "yellow", "magenta", "darkblue", "darkgreen"});
    ui->comboBox_2->addItems(QStringList{"1","2","3","4","5","6","7","8","9","10"});
}

void MainWindow::clearInfoAboutImage()
{
    ui->plainTextBareKernels->clear();
    ui->plainTextCells->clear();
    ui->plainTextComment->clear();
    ui->plainTextKernels->clear();
    ui->plainTextScaterredCells->clear();
    ui->plainTextStructures->clear();
}

void MainWindow::showInfoAboutImage(pImageModel image)
{
    clearInfoAboutImage();
    ui->plainTextBareKernels->appendPlainText(image->bare_kernels);
    ui->plainTextCells->appendPlainText(image->cells);
    ui->plainTextComment->appendPlainText(image->comment);
    ui->plainTextKernels->appendPlainText(image->kernels);
    ui->plainTextScaterredCells->appendPlainText(image->scattered_cells);
    ui->plainTextStructures->appendPlainText(image->structures);
}

void MainWindow::on_pushButton_7_clicked() // remove buttn
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();

    AppConfirmDialog("Вы уверены, что хотите удалить пациента?", [=]{
            repeat(i,selection.count())
            {
                emit removePatient(selection.at(i));
            }
       });
}

void MainWindow::on_pushButton_9_clicked() // refresh
{
    APPModel::shared().update();
}

void MainWindow::on_tabWidget_tabBarClicked(int index) // select tab - images
{
//    if (index == 0)
//    {
//    }

    if (index == 1)
    {
        ui->tableWidget->clear();
        ui->imageEditorWidget->clearEditor();

        QModelIndex patientIndex = getSelectedPatientIndex();
        if (!patientIndex.isValid())
        {
            ui->tabWidget->setCurrentIndex(0);
            return;
        }
        QVector<pImageModel> images = APPCore::shared().getPreviewImagesForPatient(patientIndex);

        if (images.isEmpty())
        {
            return;
        }

        ui->tableWidget->setColumnCount(images.count());
        ui->tableWidget->setRowCount(1);
        ui->imageEditorWidget->setImage(QPixmap(images.at(0)->path));
        ui->imageEditorWidget->currentImageID = images.at(0)->id;
        showInfoAboutImage(images.at(0));

        repeat(i,images.count())
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            ui->tableWidget->setRowHeight(i,110);
            ui->tableWidget->setColumnWidth(i,110);
            QPixmap pixmap(images.at(i).get()->path);
            item->setData(Qt::DecorationRole, pixmap.scaled(100, 100,Qt::KeepAspectRatio));
            ui->tableWidget->setItem(0,i,item);
        }
    }

    if (index == 2)
    {
        ui->tableWidget_2->clear();
        ui->imageEditorWidget_2->clearEditor();
        clearInfoAboutImage();

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

            if (marks.isEmpty())
            {
                return;
            }

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
    pImageModel image = APPCore::shared().getSourceImageForPatient(patientIndex, position);

    if (image == nullptr)
    {
        return;
    }

    ui->imageEditorWidget->setImage(QPixmap(image->path));
    showInfoAboutImage(image);
    ui->imageEditorWidget->currentImageID = image->id;
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

void MainWindow::previewImageDidDoubleClicked(QTableWidgetItem *item)
{
    AppConfirmDialog("Удалить выбранное изображение?",[&]{
        emit removeImage(getSelectedPatientIndex(),item->column());
        ui->tableWidget->removeColumn(item->column());
    });
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

void MainWindow::on_pushButton_11_clicked()//search
{
    SearchForm *form = new SearchForm(this);
    form->setModal(true);
    connect(form,&SearchForm::queryData,
            &APPCore::shared(),&APPCore::searchPatients);
    form->show();
}

void MainWindow::on_pushButton_10_clicked()//clear filter
{
    APPModel::shared().patientTableModel.setFilter("");
    APPModel::shared().patientTableModel.select();
    qDebug() << "patient filter is empty ";
}

void MainWindow::on_pushButton_clicked() // save__text_comments
{
    int imageid = ui->imageEditorWidget->currentImageID;
    if (imageid == 0)
    {
        return;
    }

   pEntity ent = DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,imageid);
   if (ent == nullptr)
   {
       return;
   }

    pImageModel image = std::static_pointer_cast<ImageModel,Entity>(ent);

    image->comment = ui->plainTextComment->toPlainText();
    image->cells = ui->plainTextCells->toPlainText();
    image->kernels = ui->plainTextKernels->toPlainText();
    image->structures = ui->plainTextStructures->toPlainText();
    image->scattered_cells = ui->plainTextScaterredCells->toPlainText();
    image->bare_kernels = ui->plainTextBareKernels->toPlainText();

    DataBaseManager::shared().update(DBConst::TABLE_NAME_IMAGE,*image);
}

void MainWindow::on_pushButton_2_clicked() // cancel__text__comments
{
    int imageid = ui->imageEditorWidget->currentImageID;
    if (imageid == 0)
    {
        return;
    }

    pEntity ent = DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,imageid);
    if (ent == nullptr)
    {
        return;
    }

    pImageModel image = std::static_pointer_cast<ImageModel,Entity>(ent);
    showInfoAboutImage(image);
}

void MainWindow::on_pushButton_12_clicked() // remove image
{
    QTableWidgetItem *item = ui->tableWidget->selectedItems().first();

    AppConfirmDialog("Удалить выбранное изображение?",[&]{
        emit removeImage(getSelectedPatientIndex(),item->column());
        ui->tableWidget->removeColumn(item->column());
    });
}








