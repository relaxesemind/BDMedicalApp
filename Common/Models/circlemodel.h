#ifndef CIRCLEMODEL_H
#define CIRCLEMODEL_H

#include "entity.h"
#include "imagemodel.h"

class CircleModel : public Entity
{
public:
    CircleModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;
    ~CircleModel();

    int id;
    int thickness;
    QString color;
    int center_x;
    int center_y;
    int radius;
    ImageModel *image;
};


#endif // CIRCLEMODEL_H
