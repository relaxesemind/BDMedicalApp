#ifndef MAGIC_H
#define MAGIC_H

#include <QObject>

#define quo QString("'")

#define class_singleton(__name__) \
class __name__  : public QObject \
{ \
    Q_OBJECT \
private: \
    __name__() = default; \
    __name__(const __name__&); \
    __name__& operator=(__name__&); \
public: \
    static __name__& shared() { \
        static __name__  manager; \
        return manager; \
} \
    ~__name__(); \

#define str(__STRING__) QString("__STRING__")

#define repeat_cycle(__count__) \
    for (int i = 0; i < __count__; ++i)

#define AppMessage(__title__, __description__) \
     QMessageBox::information(nullptr,QString(__title__), QString(__description__));

#define dynamicCreate(className, variable) className *variable = new className();

#define cast(typeNew, variable) static_cast<typeNew> (variable)

#define MakeSingletonFromClass(__name__) \
public: \
    __name__(__name__ const&) = delete; \
    __name__& operator=(__name__ const&) = delete; \
    static __name__& shared() { \
        static __name__ instance; \
        return instance; \
    } \
private: \
    __name__() = default; \

#define attr(__name__,__params__) \
    std::make_pair(QString( __name__),QString(__params__))

#define nullattr std::make_pair(QString(""), QString(""))
#define IDattr std::make_pair(QString("id"), \
                    QString("INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY"))

//reference_cascade("users", "user_id")
#define attr_reference_cascade(__destination_table_name__,__self_id__) \
    std::make_pair(QString( __self_id__ + " INT UNSIGNED NOT NULL, "), \
                   QString(QString(" FOREIGN KEY (") + __self_id__ + QString(") REFERENCES ") +  \
                   __destination_table_name__ + QString("(id)") + QString(" on delete cascade")))

#endif // MAGIC_H
