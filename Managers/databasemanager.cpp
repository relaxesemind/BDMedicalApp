#include "databasemanager.h"

void DataBaseManager::connectToDataBase()
{
   openDataBase();
}

void DataBaseManager::init()
{
    createTable(DBConst::TABLE_NAME_PATIENT);
    createTable(DBConst::TABLE_NAME_IMAGE);
    createTable(DBConst::TABLE_NAME_MARKS);
//    removeDataBase();
}

DataBaseManager::~DataBaseManager()
{
    db.close();
}

bool DataBaseManager::insert(const QString &tableName, const Entity &content)
{
  QSqlQuery query(db);
  QStack<QString> queryStack = ripper.insertQuery(tableName, content);
  QString queryStr = queryStack.pop();
  QVariantList data = content.getData();
  query.prepare(queryStr);
  bindValuesForQuery(query,queryStack,data);

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

bool DataBaseManager::update(const QString &tableName, const Entity &newObject)
{
    if (newObject.getData().value(0).toInt() == 0)
    {
        qDebug() << "update Entity failed id = 0";
        return false;
    }
    QSqlQuery query(db);
    QStack<QString> stack = ripper.updateTableQuery(tableName,newObject.getData().value(0).toInt(),newObject);
    QVariantList data = newObject.getData();

    if (stack.isEmpty())
    {
        qDebug()<<"update stack is empty";
        return false;
    }

    QString queryStr = stack.pop();
    qDebug() << queryStr;
    query.prepare(queryStr);
    bindValuesForQuery(query,stack,data);

    if (!query.exec())
    {
        qDebug()<< "update row error!" << query.lastError();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBaseManager::remove(const QString &tableName, const Entity &content)
{
    return remove(tableName,content.getData().first().toInt());
}

bool DataBaseManager::remove(const QString &tableName, int id)
{
    return baseQuery(ripper.deleteRowQuery(tableName,id),"remove row query");
}

bool DataBaseManager::removeTable(const QString &tableName)
{
    return baseQuery(ripper.removeTableQuery(tableName),"drop table query");
}

bool DataBaseManager::removeDataBase()
{
    return baseQuery(ripper.removeDataBase(),"Drop DataBase");
}

void DataBaseManager::optimizeTable(const QString &tableName)
{
    QSqlQuery query(db);
    QString queryStr = "REPAIR TABLE " + tableName;
    query.exec(queryStr);
}

QVector<pEntity> DataBaseManager::select(const QString &table, const QString &param)
{
    QSqlQuery query(db);
    QString qstr = ripper.selectFromTableQuery(table,param);

    query.prepare(qstr);
    if (!query.exec())
    {
        qDebug() << "SELECT ERROR !!!" << query.lastError();
        return QVector<pEntity>();
    }
    if (!query.isSelect())
    {
        qDebug() << "bad select query";
        return QVector<pEntity>();
    }

    return ripper.parseObjects(query,table);
}

pEntity DataBaseManager::select(const QString &table, int id)
{
    QVector<pEntity> vector = select(table," WHERE id = " + QString::number(id));
    if (!vector.isEmpty())
    {
        return vector.first();
    }
    else
    {
        return nullptr;
    }
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
        baseQuery(ripper.createDataBaseQuery(),"Create DataBase " + DBConst::DATABASE_NAME);
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
    return baseQuery(ripper.createTableQuerry(tableName),"Create table " + tableName);
}

bool DataBaseManager::baseQuery(const QString &queryStr, const QString &title)
{
    QSqlQuery query(db);

    if (!query.exec(queryStr))
    {
        qDebug()<< title + " error!" << query.lastError();
        return false;
    }
    else
    {
        return true;
    }
}

bool DataBaseManager::bindValuesForQuery(QSqlQuery &query, QStack<QString> &binds, QVariantList &values)
{
    while (!binds.isEmpty())
    {
        QString bind = binds.pop();
        QVariant var = values.constLast();
        values.removeLast();

        if (ripper.variantIsInt(var))
        {
            query.bindValue(bind,var.toInt());
        }
        if (ripper.variantIsStr(var))
        {
            query.bindValue(bind,var.toString());
        }
    }
    return true;
}









