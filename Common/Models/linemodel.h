#ifndef LINEMODEL_H
#define LINEMODEL_H

#include "entity.h"

class LineModel : public Entity
{
public:
    LineModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

    int id;
    int thickness;
    QString colorName;
    int point_x1;
    int point_y1;
    int point_x2;
    int point_y2;
    int imageID;
};

#endif // LINEMODEL_H
