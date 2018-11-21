#ifndef MARKMODEL_H
#define MARKMODEL_H

#include "entity.h"

class MarkModel : public Entity
{
public:
    MarkModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

    int id;
    QString path;
    int imageID;
};

using pMarkModel = std::shared_ptr<MarkModel>;

#endif // MARKMODEL_H
