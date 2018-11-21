#include "linemodel.h"


QVariantList LineModel::getData()const
{
    return QVariantList
    {
        id, thickness, colorName, point_x1, point_y1, point_x2, point_y2, imageID
    };
}

QVector<int> LineModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Int,
         BDTypes::Varchar,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int
    };
}
