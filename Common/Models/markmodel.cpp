#include "markmodel.h"

QVariantList MarkModel::getData()const
{
    return QVariantList
    {
        id, path, imageID
    };
}

QVector<int> MarkModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Varchar,
         BDTypes::Int
    };
}
