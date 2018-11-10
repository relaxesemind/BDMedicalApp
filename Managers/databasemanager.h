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

signals:

public slots:
    bool insert(const QString& tableName, const Entity& content);
    bool remove(const QString& tableName, const Entity& content);
    bool remove(const QString& tableName, int id);
    void optimizeTable(const QString& tableName);

    QVector<pEntity> select(const QString& table, const QString& param = "");

private: //properties
    QSqlDatabase db;
    QueryRipper ripper;

private: //methods
    bool openDataBase();
    void closeDataBase();
    bool createTable(const QString& tableName);
};

#endif // DATABASEMANAGER_H














