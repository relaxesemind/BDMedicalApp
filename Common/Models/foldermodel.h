#ifndef FOLDERMODEL_H
#define FOLDERMODEL_H


#include "models.h"


class FolderModel : public Entity
{
public:
    FolderModel() = default;
    int id;
    QVector<QString> description;
    QVector<FolderModel *> folders;
    ImageModel *image;

    QVariantList getData()const override;
    QVector<int> attr_type_mask()const override;

};

#endif // FOLDERMODEL_H
