#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "Common/magic.h"
#include "Common/Models/models.h"
#include "appmodel.h"
#include "Managers/databasemanager.h"
#include <QFileDialog>
#include <QStack>
#include <QPixmap>
#include <QLineF>
#include <QDir>

class APPCore : public QObject
{
    Q_OBJECT
    MakeSingletonFromClass(APPCore)

public:
   void init();
   QVector<pImageModel> getPreviewImagesForPatient(const QModelIndex& idx);
   QVector<pMarkModel> getMarkImagesForImage(int imageID);
   pImageModel getSourceImageForPatient(const QModelIndex& patentId,int id);
   pMarkModel getSourceMarkImage(int imageID, int position);


signals:
   void activateImageForEdit(bool activate);

public slots:
    void removePatient(const QModelIndex& idx);
    void addPatient(const PatientModel& patient);
    void addImagesToPatient(const QModelIndex& idx);
    void saveMarkToDB(int imageID, const QPixmap& pixmap);

private:
    void initDataBase();
};

#endif // APPCORE_H
