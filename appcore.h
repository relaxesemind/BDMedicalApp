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

class APPCore : public QObject
{
    Q_OBJECT
    MakeSingletonFromClass(APPCore)

public:
   void init();
   QStack<QPixmap> getImagesForPatient(const QModelIndex& idx);

signals:

public slots:
    void removePatient(const QModelIndex& idx);
    void addPatient(const PatientModel& patient);
    void addImagesToPatient(const QModelIndex& idx);

private:
    void initDataBase();
};

#endif // APPCORE_H
