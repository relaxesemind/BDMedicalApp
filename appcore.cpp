#include "appcore.h"

void APPCore::init()
{
    initDataBase();
}

QStack<QPixmap> APPCore::getImagesForPatient(const QModelIndex &idx)
{
     int id = APPModel::shared().patientTableModel.data(idx).toInt();
     QVector<pEntity> pointers =  DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,
              "WHERE " + DBConst::TABLE_REFERENCE_ATTR_IMAGE + " = " + QString::number(id));
     if (pointers.isEmpty())
     {
         return QStack<QPixmap>();
     }

     QStack<QPixmap> stack;

     repeat(i,pointers.size())
     {
         ImageModel *image = dynamic_cast<ImageModel *>(pointers.at(i).get());
         QString path = image->path;
         QPixmap px(path);
         stack.push(px);
     }

  return stack;
}

void APPCore::removePatient(const QModelIndex &idx)
{
    int id = APPModel::shared().patientTableModel.data(idx).toInt();
    DataBaseManager::shared().remove(DBConst::TABLE_NAME_PATIENT,id);
    APPModel::shared().patientTableModel.select();
}

void APPCore::addPatient(const PatientModel &patient)
{
    DataBaseManager::shared().insert(DBConst::TABLE_NAME_PATIENT, patient);
    APPModel::shared().update();
}

void APPCore::addImagesToPatient(const QModelIndex &idx)
{
    int patientID = idx.data().toInt();
    bool flag = true;

    QStringList filenames = QFileDialog::getOpenFileNames(nullptr,Global::CHOOSE_IMAGE_WINDOW_TITLE,
                                                          QDir::currentPath(),Global::CHOOSE_IMAGE_TYPES);

    while (!filenames.empty()) {
        ImageModel image;
        image.path = filenames.last();
        image.patientID = patientID;
        image.comment = "comment comment";
        filenames.removeLast();
        if (!DataBaseManager::shared().insert(DBConst::TABLE_NAME_IMAGE,image))
        {
            flag = false;
        };
    }
    if (flag)
    {
       AppMessage("Сообщение", "Изображения успешно добавлены");
    }
    else
    {
       AppMessage("Сообщение", "Во время добавления произошли ошибки");
    }
}

void APPCore::initDataBase()
{
    DataBaseManager::shared().connectToDataBase();
    DataBaseManager::shared().init();
}
