#include "patientmodel.h"

QVariantList PatientModel::getData()const
{
    return QVariantList
    {
      id, name, images, marks, diag_cito, diag_gisto, sex, age
    };
}

QVector<int> PatientModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Varchar,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Int
    };
}
