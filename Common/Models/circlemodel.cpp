#include "circlemodel.h"

CircleModel::~CircleModel()
{

}

QVariantList CircleModel::getData()const
{
    QVariantList data;
    data << id << thickness << color <<
            center_x << center_y << radius;
    return data;
}

QVector<int> CircleModel::attr_type_mask()const
{
    return QVector<int>
    {
         BDTypes::IDtype,
         BDTypes::Int,
         BDTypes::Varchar,
         BDTypes::Int,
         BDTypes::Int,
         BDTypes::Int
    };
}
