#include "rectmodel.h"

QVariantList RectModel::getData()const
{
    return QVariantList
    {
        id, thickness, color, point_x1, point_y1, point_x2, point_y2, imageID
    };
}

QVector<int> RectModel::attr_type_mask()const
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
