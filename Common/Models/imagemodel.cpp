#include "imagemodel.h"

QVariantList ImageModel::getData()const
{
    QVariantList data;
    data << id << path << value << kernels
         << cells << scattered_cells
         << structures << bare_kernels << comment;
    return data;
}

QVector<int> ImageModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Int,
         BDTypes::Varchar,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Reference
    };
}
