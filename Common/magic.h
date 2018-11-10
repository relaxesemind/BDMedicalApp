#ifndef MAGIC_H
#define MAGIC_H

#include <QObject>
#include <QMessageBox>
#include <memory>

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

#define repeat(counter, count) \
    for (int counter = 0; counter < count; ++counter)

#define AppMessage(__title__, __description__) \
     QMessageBox::information(nullptr,QString(__title__), QString(__description__));

#define smartPointer(className, variable) std::shared_ptr<className> \
                                variable = std::make_shared<className>();

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
#define attr_reference_cascade(__destination_table_name__,__self__) \
    std::make_pair(QString(__self__), \
                   QString(QString(" INT UNSIGNED NOT NULL, \n FOREIGN KEY (") + __self__ + QString(") REFERENCES ") +  \
                   __destination_table_name__ + QString("(id)") + QString(" on delete cascade")))

#endif // MAGIC_H
