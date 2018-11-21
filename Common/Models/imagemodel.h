#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "entity.h"

class ImageModel : public Entity
{
public:
    ImageModel() = default;
    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

    int id;
    QString path;
    int value;
    QString kernels;
    QString cells;
    QString scattered_cells;
    QString structures;
    QString bare_kernels;
    QString comment;
    int patientID;
};

using pImageModel = std::shared_ptr<ImageModel>;

#endif // IMAGEMODEL_H
