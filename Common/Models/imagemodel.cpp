#include "imagemodel.h"

QVariantList ImageModel::getData()const
{
    return QVariantList
    {
        id, path, value, kernels, cells, scattered_cells,
        structures, bare_kernels, comment, patientID
    };
}

QVector<int> ImageModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Varchar,
         BDTypes::Int,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Varchar,
         BDTypes::Int
    };
}
