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

    PatientModel patient = DataBaseManager::shared().selectObject<PatientModel>(0);
    qDebug() << "patient name = " << patient.id;
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString GetRandomString()
{
   const QString possibleCharacters("АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя");
   const int randomStringLength = 16; // assuming you want random strings of 12 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

void MainWindow::on_pushButton_6_clicked()//add patient
{
//    PatientInputForm *form = new PatientInputForm(this);
//    form->setModal(true);
//    connect(form,&PatientInputForm::patientData,
//            &APPCore::shared(),&APPCore::addPatient);
//    form->show();
    QStringList list
    {
        "Капустина Светлана Игоревна",
        "Сулимова Анастасия Всеволодовна",
        "Ягешев Эрнст Изяславович",
        "Жданов Алексей Измаилович",
        "Антонович Кир Леонович",
        "Сазонтов Тарас Никитевич",
        "Изотов Аким Даниилович",
        "Истомина Любовь Родионовна",
        "Челомеев Аскольд Самсонович",
        "Сюкосева Регина Вячеславовна",
        "Серебров Михаил Филиппович",
        "Машира Нона Игнатиевна",
        "Шульгин Осип Вадимович",
        "Жиглов Никон Эмилевич",
        "Ясаев Кондратий Вадимович",
        "Ажикелямова Алина Трофимовна",
        "Ершова Дина Романовна",
        "Курбанова Анисья Потаповна",
        "Желдин Петр Серафимович",
        "Драчёв Матвей Данилевич",
        "Грехов Валентин Федотович",
        "Седова Ника Ефимовна",
        "Степихова Каролина Виталиевна",
        "Швецова Анфиса Александровна",
        "Лагошина Варвара Карповна",
        "Гречко Ярослава Данииловна",
        "Иноземцева Мария Геннадиевна",
        "Пушкин Варфоломей Ростиславович",
        "Бельтюков Варфоломей Онуфриевич",
        "Курдин Андрон Адамович",
        "Устимовича Нина Святославовна",
        "Антонович Максим Александрович",
        "Роговский Пимен Родионович",
        "Рошет Гавриил Левович",
        "Леонидов Анатолий Сергеевич",
        "Ясюлевича Людмила Степановна",
        "Удома Арина Мефодиевна",
        "Агабабян Сергей Леонтиевич",
        "Бок Мстислав Куприянович",
        "Можаева Любава Владленовна",
        "Якунчиков Феофан Ипатович",
        "Чечёткина Рената Ефимовна",
        "Цыганкова Валентина Игнатиевна",
        "Яикбаева Агния Ипполитовна",
        "Януковича Полина Борисовна",
        "Лукашенко Адриан Ермолаевич",
        "Дудченко Роза Леонидовна",
        "Цехановецкий Ираклий Несторович",
        "Кожухова Ксения Мефодиевна",
        "Эйлера Алла Святославовна",
        "Суворкин Владлен Иннокентиевич",
        "Яценко Игорь Ипполитович",
        "Дорохов Всеслав Ефремович",
        "Ляпин Емельян Гордеевич",
        "Приходько Лада Виталиевна",
        "Благово Марина Карповна",
        "Саламатова Берта Захаровна",
        "Соломинцева Елена Виталиевна",
        "Дегтярев Архип Гордеевич",
        "Богачёва Алина Юлиевна",
        "Куприянова Александра Владиленовна",
        "Мазурин Якуб Мирославович",
        "Колобова Доминика Ивановна",
        "Воейков Адам Владимирович",
        "Созонтова Лариса Константиновна",
        "Яндарбиев Онуфрий Филимонович",
        "Овчинников Иван Казимирович",
        "Харькова Альбина Всеволодовна",
        "Цветкова Стела Елизаровна",
        "Будылин Мстислав Ермолаевич",
        "Шуляк Эмиль Елисеевич",
        "Ястребенецкий Лукьян Самуилович",
        "Агальцов Федор Проклович",
        "Новожилова Диана Никитевна",
        "Каржаубаев Герасим Феликсович",
        "Кантонистов Максимильян Адрианович",
        "Сотников Рубен Даниилович",
        "Кривова Марианна Тихоновна",
        "Канкия Бронислав Кириллович",
        "Котова Христина Афанасиевна",
        "Ягеман Эдуард Никитевич",
        "Тотенкова Доминика Николаевна",
        "Былинкина Зоя Серафимовна",
        "Мутовин Николай Пахомович",
        "Божко Анфиса Глебовна",
        "Юдицкий Савелий Герасимович",
        "Опринчук Петр Федосиевич",
        "Сусоев Роман Гордеевич",
        "Крылова Татьяна Елисеевна",
        "Бухаров Потап Олегович",
        "Николаева Ирина Емельяновна",
        "Колотушкин Петр Ефремович",
        "Арсеньев Родион Пахомович",
        "Соловьева Варвара Ираклиевна",
        "Мажулина Берта Брониславовна",
        "Угличинина Доминика Тимуровна",
        "Мосина Злата Тихоновна",
        "Деменкова Всеслава Павеловна",
        "Сьянова Влада Семеновна",
        "Лавлинский Никон Эмилевич"
    };

    for ( const QString& name : list)
    {
        PatientModel patient;
        patient.name = name;
        patient.diag_cito = GetRandomString();
        patient.diag_gisto = GetRandomString();
        if (name.endsWith("а"))
        {
            patient.sex = "F";
        }
        else
        {
            patient.sex = "M";
        }
        patient.age = 9 + (rand() % static_cast<int>(92 - 9 + 1));
        APPCore::shared().addPatient(patient);
    }

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
//        ui->imageEditorWidget_2->clearEditor();
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
}


