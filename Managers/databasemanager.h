#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Common/Models/models.h"
#include "Common/magic.h"
#include "Common/consts.h"
#include "Helpers/queryripper.h"

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QtSql/QSqlRecord>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <typeinfo>
#include <QVector>
#include <QStack>

class DataBaseManager : public QObject
{
    Q_OBJECT
    MakeSingletonFromClass(DataBaseManager)

public: //methods
    void connectToDataBase();
    void init();
    ~DataBaseManager();
    template<class T>
    QVector<T> selectObjects();

    template<class T>
    T selectObject(int id);

signals:

public slots:
    bool insert(const QString& tableName, const Entity&);
    bool update(const QString& tableName, const Entity& newObject);
    bool remove(const QString& tableName, const Entity&);
    bool remove(const QString& tableName, int id);
    bool removeTable(const QString& tableName);
    bool removeDataBase();
    void optimizeTable(const QString& tableName);

    QVector<pEntity> select(const QString& table, const QString& param = "");
    pEntity select(const QString& table, int id);

private: //properties
    QSqlDatabase db;
    QueryRipper ripper;

private: //methods
    bool openDataBase();
    void closeDataBase();
    bool createTable(const QString& tableName);
    bool baseQuery(const QString& queryStr, const QString& title);
    bool bindValuesForQuery(QSqlQuery &query, QStack<QString> &binds, QVariantList& values);
};

template<class T>
QVector<T> DataBaseManager::selectObjects()
{
   if (!std::is_base_of<Entity,T>::value)
   {
       qDebug() << "failed template select << not derived class";
       return QVector<T>();
   }

    QString tableName;

    if (std::is_same<T,PatientModel>::value)
    {
       tableName = DBConst::TABLE_NAME_PATIENT;
    } else if (std::is_same<T,ImageModel>::value)
    {
       tableName = DBConst::TABLE_NAME_IMAGE;
    } else  if (std::is_same<T,MarkModel>::value)
    {
       tableName = DBConst::TABLE_NAME_MARKS;
    } else
    {
        return QVector<T>();
    }

    QVector<pEntity> array = select(tableName);
    QVector<T> result;

    repeat(i, array.count())
    {
        result.append(*std::static_pointer_cast<T,Entity>(array[i]));
    }
    return result;
}

template<class T>
T DataBaseManager::selectObject(int id)
{
    if (!std::is_base_of<Entity,T>::value)
    {
        qDebug() << "failed template select << not derived class";
        return T();
    }

   QVector<T> array = selectObjects<T>();



   if (id > array.count() - 1)
   {
       return T();
   }
   else
   {
       return array[id];
   }
}

#endif // DATABASEMANAGER_H














