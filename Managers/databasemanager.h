#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "Common/Models/models.h"
#include "Common/magic.h"
#include "Common/consts.h"

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

class QueryRipper
{
public:
    QString prepareCreateDataBaseQueryStr();
    QString prepareSelectFromTableQueryStr(const QString& tableName, const QString& param = "");
    QString prepareCreateTableQuerryStr(const QString& tableName);
    QString prepareDeleteRowQueryStr(const QString& tableName, int id);
    QStack<QString> prepareInsertQuerry(const QString& tableName, const Entity& obj);
    bool variantIsInt(const QVariant& variant);
    bool variantIsStr(const QVariant& variant);
    bool variantIsChar(const QVariant& variant);
};

class DataBaseManager : public QObject
{
    Q_OBJECT
    MakeSingletonFromClass(DataBaseManager)
public: //methods
    using pEntity = std::shared_ptr<Entity>;

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














