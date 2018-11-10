#include "databasemanager.h"

void DataBaseManager::connectToDataBase()
{
//    if(!QFile(QCoreApplication::applicationDirPath()+ "/" + DBConst::DATABASE_NAME).exists()){
//           this->openDataBase();
//        } else {
            this->openDataBase();
 //   }
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
  QStack<QString> queryStack = ripper.insertQuery(tableName, content);
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
   QString queryStr = ripper.deleteRowQuery(tableName,id);
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

QVector<pEntity> DataBaseManager::select(const QString &table, const QString &param)
{
    QSqlQuery query(db);
    QVector<pEntity> result;

    query.prepare(ripper.selectFromTableQuery(table,param));
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
        q.exec(ripper.createDataBaseQuery());
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
    if (!querry.exec(ripper.createTableQuerry(tableName)))
    {
        qDebug() << "Table create error " + tableName;
        qDebug() << querry.lastError().text();
        return false;
    }
    else return true;
}









