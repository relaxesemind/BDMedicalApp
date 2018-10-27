#ifndef APPMODEL_H
#define APPMODEL_H

#include <QObject>
#include "Common/magic.h"
#include <QSqlTableModel>

class APPModel : public QObject
{
    Q_OBJECT
    MakeSingletonFromClass(APPModel)
public:
     void initModels();
     void update();

public:
     QSqlTableModel patientTableModel;

signals:

public slots:

private:
    void setupPatientTableModel();
};

#endif // APPMODEL_H
