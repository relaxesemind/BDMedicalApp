#ifndef RECTMODEL_H
#define RECTMODEL_H

#include "entity.h"
#include "imagemodel.h"

class RectModel : public Entity
{
public:
    RectModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

    int id;
    short thickness;
    QString color;
    int point_x1;
    int point_y1;
    int point_x2;
    int point_y2;
    ImageModel *image;
};

#endif // RECTMODEL_H
