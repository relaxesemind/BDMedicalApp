#include "appcore.h"

void APPCore::init()
{
    initDataBase();
}

QVector<pImageModel> APPCore::getPreviewImagesForPatient(const QModelIndex &idx)
{
     int id = APPModel::shared().patientTableModel.data(idx).toInt();
     QVector<pEntity> pointers =  DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,
              "WHERE " + DBConst::TABLE_REFERENCE_ATTR_IMAGE + " = " + QString::number(id));
     if (pointers.isEmpty())
     {
         return QVector<pImageModel>();
     }

     QVector<pImageModel> vector;

     repeat(i,pointers.size())
     {
         pImageModel image = std::static_pointer_cast<ImageModel,Entity>(pointers.at(i));
         vector.append(image);
     }

     return vector;
}

QVector<pMarkModel> APPCore::getMarkImagesForImage(int imageID)
{
    QVector<pEntity> array = DataBaseManager::shared().select(DBConst::TABLE_NAME_MARKS,"WHERE " +
                                                              DBConst::TABLE_REFERENCE_ATTR_MARKS + " = " + QString::number(imageID));
    if (array.isEmpty())
    {
        return QVector<pMarkModel>();
    }

    QVector<pMarkModel> marks;

    repeat(i,array.size())
    {
        pMarkModel mark = std::static_pointer_cast<MarkModel, Entity>(array.at(i));
        marks.append(mark);
    }
    return marks;
}

pImageModel APPCore::getSourceImageForPatient(const QModelIndex& patentId, int position)
{
    int pid = APPModel::shared().patientTableModel.data(patentId).toInt();
    QVector<pEntity> pointers =  DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,
             "WHERE " + DBConst::TABLE_REFERENCE_ATTR_IMAGE + " = " + QString::number(pid));
    if (pointers.count() < position + 1)
    {
        qDebug() << "nullptr preview image";
        return nullptr;
    }
    qDebug() << "preview image did selected";
    return std::static_pointer_cast<ImageModel,Entity>(pointers.at(position));
}

pMarkModel APPCore::getSourceMarkImage(int imageID, int position)
{
    QVector<pEntity> pointers =  DataBaseManager::shared().select(DBConst::TABLE_NAME_MARKS,
             "WHERE " + DBConst::TABLE_REFERENCE_ATTR_MARKS + " = " + QString::number(imageID));
    if (pointers.count() < position + 1)
    {
        qDebug() << "nullptr preview mark";
        return nullptr;
    }
    qDebug() << "mark did selected";
    return std::static_pointer_cast<MarkModel,Entity>(pointers.at(position));
}

void APPCore::removePatient(const QModelIndex &idx)
{
    int id = APPModel::shared().patientTableModel.data(idx).toInt();
//    QString name = APPModel::shared().patientTableModel.data(QModelIndex()).toString();
    DataBaseManager::shared().remove(DBConst::TABLE_NAME_PATIENT,id);
    APPModel::shared().patientTableModel.select();
}

void APPCore::addPatient(const PatientModel &patient)
{
    qDebug()<<"APPCore::addPatient name = " << patient.name;
    DataBaseManager::shared().insert(DBConst::TABLE_NAME_PATIENT, patient);
    APPModel::shared().update();
}

void APPCore::addImagesToPatient(const QModelIndex &idx)
{
    if (!idx.isValid())
    {
        return;
    }

    int patientID = idx.data().toInt();
    bool flag = true;

    QStringList filenames = QFileDialog::getOpenFileNames(nullptr,Global::CHOOSE_IMAGE_WINDOW_TITLE,
                                                          QDir::currentPath(),Global::CHOOSE_IMAGE_TYPES);
    if (filenames.isEmpty())
    {
        return;
    }
    int numberOfNewImages = filenames.count();

    while (!filenames.empty()) {
        ImageModel image;
        image.path = filenames.last();
        image.value = 0;
        image.patientID = patientID;
        filenames.removeLast();
        if (!DataBaseManager::shared().insert(DBConst::TABLE_NAME_IMAGE,image))
        {
            flag = false;
        };
    }

    if (flag)
    {
       AppMessage("Сообщение", "Изображения успешно добавлены");
       pEntity entity = DataBaseManager::shared().select(DBConst::TABLE_NAME_PATIENT, patientID);
       makeFromEntity(PatientModel,patient,entity);

       QVector<pEntity> pointers =  DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE,
                "WHERE " + DBConst::TABLE_REFERENCE_ATTR_IMAGE + " = " + QString::number(patientID));
       if (pointers.isEmpty())
       {
           return;
       }

       patient->images = pointers.count();
       qDebug()<<"APPCore:: add images to patient " << patient->name << numberOfNewImages << " of new images";
       DataBaseManager::shared().update(DBConst::TABLE_NAME_PATIENT, *patient);
       APPModel::shared().update();
    }
    else
    {
       AppMessage("Сообщение", "Во время добавления произошли ошибки");
    }
}

void APPCore::saveMarkToDB(int imageID, const QPixmap &pixmap)
{
    if (pixmap.isNull() || imageID == 0)
    {
        return;
    }

   emit activateImageForEdit(false);

   pEntity entity = DataBaseManager::shared().select(DBConst::TABLE_NAME_IMAGE, imageID);
   pImageModel image = std::static_pointer_cast<ImageModel,Entity>(entity);

   pEntity entity1 = DataBaseManager::shared().select(DBConst::TABLE_NAME_PATIENT, image->patientID);
   pPatientModel patient = std::static_pointer_cast<PatientModel,Entity>(entity1);

   if (patient == nullptr)
   {
       qDebug() << "patient is null" << " id " << image->patientID;
       return;
   }

   QString initialPath = QCoreApplication::applicationDirPath() + "/Marks";
   QString folder = "/" + patient->name + "_image_" + QString::number(image->id) + "_";
   QString fileName = "mark_" + QString::number(++image->value) + ".png";

   if (!QDir(initialPath).exists())
   {
       QDir().mkdir(initialPath);
   }

   if (!QDir(initialPath + folder).exists())
   {
       QDir().mkdir(initialPath + folder);
   }

   if (pixmap.save(initialPath + folder + "/"+ fileName,"PNG"))
   {
       qDebug() << "did save img " << fileName;
       MarkModel mark;
       mark.path = initialPath + folder + "/"+ fileName;
       mark.imageID = imageID;

      if (DataBaseManager::shared().insert(DBConst::TABLE_NAME_MARKS, mark))
      {
          ++patient->marks;
          DataBaseManager::shared().update(DBConst::TABLE_NAME_PATIENT,*patient);
          DataBaseManager::shared().update(DBConst::TABLE_NAME_IMAGE,*image);
          APPModel::shared().update();
          qDebug() << "mark did inserted " << " patient name = " << patient->name << " marks = " << patient->marks;
      }
   }

   emit activateImageForEdit(true);
}

void APPCore::initDataBase()
{
    DataBaseManager::shared().connectToDataBase();
    DataBaseManager::shared().init();
}













