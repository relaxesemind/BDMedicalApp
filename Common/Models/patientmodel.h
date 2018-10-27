#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H

#include "entity.h"
#include <QChar>

class PatientModel : public Entity
{
public:
    PatientModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

    int id;
    QString name;
    int images = 0;
    int marks = 0;
    QString diag_cito;
    QString diag_gisto;
    QChar sex;
    int age;
};

#endif // PATIENTMODEL_H
