#ifndef ENTITY_H
#define ENTITY_H

#include <QStringList>
#include <QVariantList>
#include <QSqlQuery>
#include <QVector>
#include <memory>

enum BDTypes {
    Int, Varchar, Char1, IDtype
};

class Entity
{
public:
    virtual QVariantList getData()const;
    virtual QVector<int> attr_type_mask()const;
    virtual ~Entity(){}
};

using pEntity = std::shared_ptr<Entity>;

#endif // ENTITY_H
