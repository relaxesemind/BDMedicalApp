#include "databasemanager.h"

int DBConst::TABLE_NUMBER_OF_ATTR(const QString &table_name)
{
    if (table_name == DBConst::TABLE_NAME_PATIENT)
    {
        return 8;
    }
    if (table_name == DBConst::TABLE_NAME_IMAGE)
    {
        return 10;
    }
    if (table_name == DBConst::TABLE_NAME_CIRCLE)
    {
        return 7;
    }
    if (table_name == DBConst::TABLE_NAME_RECT)
    {
        return 8;
    }
    return 0;
}

const std::pair<QString, QString> DBConst::ATTRIBUTE(const QString &table_name, int index)
{
    if (table_name == DBConst::TABLE_NAME_PATIENT)
    {
        switch (index)
        {
             case 0: return IDattr;
             case 1: return attr("NAME"," VARCHAR(30) NOT NULL ");
             case 2: return attr("IMAGES", " INT DEFAULT 0 ");
             case 3: return attr("MARKS"," INT DEFAULT 0");
             case 4: return attr("DIAG_CITO"," VARCHAR(30) DEFAULT 'empty'");
             case 5: return attr("DIAG_GISTO"," VARCHAR(30) DEFAULT 'empty' ");
             case 6: return attr("SEX", " CHAR(1) DEFAULT 'F'");
             case 7: return attr("AGE", " INT ");
             default:return nullattr;
        }
    }

    if (table_name == DBConst::TABLE_NAME_IMAGE)
    {
        switch (index)
        {
            case 0: return IDattr;
            case 1: return attr("PATH"," VARCHAR(50) NOT NULL ");
            case 2: return attr("value", " INT ");
            case 3: return attr("kernels", " VARCHAR(30) ");
            case 4: return attr("cells", " VARCHAR(40) ");
            case 5: return attr("scattered_cells", " VARCHAR(20) ");
            case 6: return attr("structures", " VARCHAR(20) ");
            case 7: return attr("bare_kernels", " VARCHAR(20) ");
            case 8: return attr("comment", " VARCHAR(50) ");
            case 9: return attr_reference_cascade(DBConst::TABLE_NAME_PATIENT,
                                                  DBConst::TABLE_REFERENCE_ATTR_IMAGE);
            default: return nullattr;
        }
    }

    if (table_name == DBConst::TABLE_NAME_CIRCLE)
    {
        switch (index)
        {
            case 0: return IDattr;
            case 1: return attr(" THICKNESS "," TINYINT ");
            case 2: return attr(" COLOR ", " VARCHAR(20) ");
            case 3: return attr(" CENTER_X "," INT NOT NULL ");
            case 4: return attr(" CENTER_Y "," INT NOT NULL ");
            case 5: return attr(" RADIUS "," INT NOT NULL ");
            case 6: return attr_reference_cascade(DBConst::TABLE_NAME_IMAGE,
                                                  DBConst::TABLE_REFERENCE_ATTR_CIRCLE);
            default:return nullattr;
        }
    }

    if (table_name == DBConst::TABLE_NAME_RECT)
    {
        switch (index)
        {
            case 0: return IDattr;
            case 1: return attr(" THICKNESS "," TINYINT ");
            case 2: return attr(" COLOR ", " VARCHAR(20) ");
            case 3: return attr(" POINT_X1 "," INT NOT NULL ");
            case 4: return attr(" POINT_Y1 "," INT NOT NULL ");
            case 5: return attr(" POINT_X2 "," INT NOT NULL ");
            case 6: return attr(" POINT_Y2 "," INT NOT NULL ");
            case 7: return attr_reference_cascade(DBConst::TABLE_NAME_IMAGE,
                                                  DBConst::TABLE_REFERENCE_ATTR_RECT);
            default:return nullattr;
        }
    }

    return nullattr;
}

void DataBaseManager::connectToDataBase()
{
    if(!QFile(QCoreApplication::applicationDirPath()+ "/" + DBConst::DATABASE_NAME).exists()){
           this->openDataBase();
        } else {
            this->openDataBase();
    }
}

void DataBaseManager::init()
{
    createTable(DBConst::TABLE_NAME_PATIENT);
    createTable(DBConst::TABLE_NAME_IMAGE);
}

DataBaseManager::~DataBaseManager()
{
    db.close();
}

bool DataBaseManager::insert(const QString &tableName, const Entity &content)
{
  QSqlQuery query(db);
  QStack<QString> queryStack = ripper.prepareInsertQuerry(tableName, content);
  QString queryStr = queryStack.pop();
  QVariantList data = content.getData();
  query.prepare(queryStr);

  while (!queryStack.isEmpty()) {
      QString bind = queryStack.pop();
      QVariant var = data.constLast();
      data.removeLast();

     if (ripper.variantIsChar(var))
     {
         query.bindValue(bind, var.toChar());
     }
     else if (ripper.variantIsInt(var))
     {
         query.bindValue(bind, var.toInt());
     }
     else if (ripper.variantIsStr(var))
     {
         query.bindValue(bind,var.toString());
     }
  }

  if(!query.exec())
  {
      qDebug() << "error insert into " << tableName;
      qDebug() << query.lastError().text();
      qDebug() << "sql query:" << query.executedQuery();
      return false;
  }
  else
  {
      return true;
  }
}

bool DataBaseManager::remove(const QString &tableName, const Entity &content)
{
    QSqlQuery query(db);

}

bool DataBaseManager::remove(const QString &tableName, int id)
{
   QSqlQuery query(db);
   QString queryStr = ripper.prepareDeleteRowQueryStr(tableName,id);
   if (!query.exec(queryStr)) {
       return false;
   }
   else
   {
       return true;
   }
}

void DataBaseManager::optimizeTable(const QString &tableName)
{
    QSqlQuery query(db);
    QString queryStr = "REPAIR TABLE " + tableName;
    query.exec(queryStr);
}

QVector<DataBaseManager::pEntity> DataBaseManager::select(const QString &table, const QString &param)
{
    QSqlQuery query(db);
    QVector<pEntity> result;

    query.prepare(ripper.prepareSelectFromTableQueryStr(table,param));
    if (!query.exec())
    {
        qDebug() << "SELECT ERROR !!!" << query.lastError();
        return QVector<pEntity>();
    }
    if (!query.isSelect())
    {
        qDebug() << "query non select !!!";
        return QVector<pEntity>();
    }

    if (table == DBConst::TABLE_NAME_IMAGE) {
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
           image->patientID = query.value(10).toInt();

           result.append(image);
        }
        return result;
    }

    while(query.next())
    {
       for (int i = 0; i < query.record().count(); ++i) {
           qDebug() << query.value(i).toString();
       }

    }
   return QVector<pEntity>();
}

bool DataBaseManager::openDataBase()
{
    db = QSqlDatabase::addDatabase(DBConst::DATABASE_DRIVER_TYPE);
    db.setHostName(DBConst::DATABASE_HOSTNAME);
    db.setUserName(DBConst::DATABASE_USER_NAME);
    db.setPassword(DBConst::DATABASE_USER_PASSWORD);
    db.setPort(DBConst::DATABASE_HOST_PORT);

    if(!db.open())
    {
        qDebug() << QObject::tr("Can't open base") << db.lastError().text();
        return false;

    }
    else
    {
        qDebug() << "Connect to MYSQL server!";
        QSqlQuery q;
        q.exec(ripper.prepareCreateDataBaseQueryStr());
        db.setDatabaseName(DBConst::DATABASE_NAME);
        if (db.open())
        {
            qDebug() << "db setup ";
            return true;
        } else
            return false;
    }
}

void DataBaseManager::closeDataBase()
{
    db.close();
}

bool DataBaseManager::createTable(const QString &tableName)
{
    QSqlQuery querry(db);
    if (!querry.exec(ripper.prepareCreateTableQuerryStr(tableName)))
    {
        qDebug() << "Table create error " + tableName;
        qDebug() << querry.lastError().text();
        return false;
    }
    else return true;
}


QString QueryRipper::prepareCreateDataBaseQueryStr()
{
    return QString(DBConst::QUERY_CREATE_DATABASE + DBConst::DATABASE_NAME);
}

QString QueryRipper::prepareSelectFromTableQueryStr(const QString &tableName, const QString& param)
{
    return " SELECT * FROM " + tableName + param + ";";
}

QString QueryRipper::prepareCreateTableQuerryStr(const QString &tableName)
{
    QString attributes = QString();
    for (int index = 0; index < DBConst::TABLE_NUMBER_OF_ATTR(tableName); ++index)
    {
        attributes += DBConst::ATTRIBUTE(tableName, index).first + " " +
                      DBConst::ATTRIBUTE(tableName, index).second + DBConst::COMMA_SYMBOL;
    }
    attributes.chop(1);
    QString createTableString(DBConst::QUERY_CREATE_TABLE);
    createTableString += tableName + " ( " + attributes + " );";
    return createTableString;
}

QString QueryRipper::prepareDeleteRowQueryStr(const QString &tableName, int id)
{
    return "DELETE FROM " + tableName + " WHERE " + DBConst::TABLE_ID_ATTR_NAME + " = " + QString::number(id);
}

QStack<QString> QueryRipper::prepareInsertQuerry(const QString &tableName, const Entity &obj)
{
    QStack<QString> stack;
    QVariantList data  = obj.getData();
    QVector<int> mask_types = obj.attr_type_mask();
    QString attributes = QString();
    QString values     = QString(" VALUES(");
    QString insertQueryStr(DBConst::QUERY_INSERT + tableName);


    for (int index = 0; index < DBConst::TABLE_NUMBER_OF_ATTR(tableName); ++index)
    {
        if (mask_types[index] == BDTypes::IDtype) {
            continue;
        }

        QString attribute = DBConst::ATTRIBUTE(tableName,index).first;
        attributes += attribute + DBConst::COMMA_SYMBOL;
        QString bind = QString(":" + attribute);
        values += bind + DBConst::COMMA_SYMBOL;
        stack.push(bind);
    }

    values.chop(1);
    attributes.chop(1);
    values += ")";
    insertQueryStr += "(" + attributes + ")" + values;

    stack.push(insertQueryStr);
    return stack;
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










