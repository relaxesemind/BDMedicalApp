#ifndef QUERYRIPPER_H
#define QUERYRIPPER_H

#include "Common/Models/models.h"
#include "Common/magic.h"
#include "Common/consts.h"

#include <QString>
#include <QVariant>
#include <QStack>
#include <QSqlQuery>

class QueryRipper
{
public:
    QueryRipper() = default;
    //
    QString createDataBaseQuery();
    QString selectFromTableQuery(const QString& tableName, const QString& param = "");
    QString createTableQuerry(const QString& tableName);
    QString deleteRowQuery(const QString& tableName, int id);
    QStack<QString> insertQuery(const QString& tableName, const Entity& obj);
    //
    QVector<pEntity> parseObjects(QSqlQuery &query, const QString& tableName);

    //
    bool variantIsInt(const QVariant& variant);
    bool variantIsStr(const QVariant& variant);
    bool variantIsChar(const QVariant& variant);
};

#endif // QUERYRIPPER_H
