#include "queryripper.h"

QString QueryRipper::createDataBaseQuery()
{
    return QString("CREATE DATABASE IF NOT EXISTS " + DBConst::DATABASE_NAME);
}

QString QueryRipper::selectFromTableQuery(const QString &tableName, const QString& param)
{
    return " SELECT * FROM " + tableName + " " + param + ";";
}

QString QueryRipper::createTableQuerry(const QString &tableName)
{
    QString attributes = QString();
    for (int index = 0; index < DBConst::TABLE_NUMBER_OF_ATTR(tableName); ++index)
    {
        attributes += DBConst::ATTRIBUTE(tableName, index).first + " " +
                      DBConst::ATTRIBUTE(tableName, index).second + ",";
    }
    attributes.chop(1);
    QString createTableString("CREATE TABLE IF NOT EXISTS ");
    createTableString += tableName + " ( " + attributes + " );";
    return createTableString;
}

QString QueryRipper::deleteRowQuery(const QString &tableName, int id)
{
    return "DELETE FROM " + tableName + " WHERE " + DBConst::TABLE_ID_ATTR_NAME + " = " + QString::number(id);
}

QStack<QString> QueryRipper::insertQuery(const QString &tableName, const Entity &obj)
{
    QStack<QString> stack;
    QVariantList data  = obj.getData();
    QVector<int> mask_types = obj.attr_type_mask();
    QString attributes = QString();
    QString values     = QString(" VALUES(");
    QString insertQueryStr("INSERT INTO " + tableName);


    for (int index = 0; index < DBConst::TABLE_NUMBER_OF_ATTR(tableName); ++index)
    {
        if (mask_types[index] == BDTypes::IDtype) {
            continue;
        }

        QString attribute = DBConst::ATTRIBUTE(tableName,index).first;
        attributes += attribute + ",";
        QString bind = QString(":" + attribute);
        values += bind + ",";
        stack.push(bind);
    }

    values.chop(1);
    attributes.chop(1);
    values += ")";
    insertQueryStr += "(" + attributes + ")" + values;

    stack.push(insertQueryStr);
    return stack;
}

QVector<pEntity> QueryRipper::parseObjects(QSqlQuery &query, const QString &tableName)
{
    QVector<pEntity> result;

    if (tableName == DBConst::TABLE_NAME_PATIENT)
    {
        while(query.next())
        {
            smartPointer(PatientModel,patient);

            patient->name = query.value(1).toString();
            patient->images = query.value(2).toInt();
            patient->marks = query.value(3).toInt();
            patient->diag_cito = query.value(4).toString();
            patient->diag_gisto = query.value(5).toString();
            patient->sex = query.value(6).toChar();
            patient->age = query.value(7).toInt();

            result.append(patient);
        }
        return result;
    }

    if (tableName == DBConst::TABLE_NAME_IMAGE)
    {
        while(query.next())
        {
           smartPointer(ImageModel,image);

           image->path = query.value(1).toString();
           image->value = query.value(2).toInt();
           image->kernels = query.value(3).toString();
           image->cells = query.value(4).toString();
           image->scattered_cells = query.value(5).toString();
           image->structures = query.value(6).toString();
           image->bare_kernels = query.value(7).toString();
           image->comment = query.value(8).toString();
           image->kernels = query.value(9).toString();

           result.append(image);
        }
        return result;
    }

    return QVector<pEntity>();
}

bool QueryRipper::variantIsInt(const QVariant &variant)
{
    switch (variant.userType())
        {
            case QMetaType::Int:
            case QMetaType::UInt:
            case QMetaType::LongLong:
            case QMetaType::ULongLong:
                return true;
        }
        return false;
}

bool QueryRipper::variantIsStr(const QVariant &variant)
{
    return variant.userType() == QMetaType::QString;
}

bool QueryRipper::variantIsChar(const QVariant &variant)
{
    return variant.userType() == QMetaType::QChar;
}
