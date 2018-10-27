#include "foldermodel.h"

QVariantList FolderModel::getData()const
{
    QVariantList data;
    // data << id << description << folders << image;
    return data;
}

QVector<int> FolderModel::attr_type_mask()const
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
