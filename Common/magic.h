#ifndef MAGIC_H
#define MAGIC_H

#include <QObject>
#include <QMessageBox>
#include <memory>

#define quo QString("'")

#define str(__STRING__) QString("__STRING__")

#define repeat(counter, count) \
    for (int counter = 0; counter < count; ++counter)

#define AppMessage(__title__, __description__) \
     QMessageBox::information(nullptr,QString(__title__), QString(__description__));

#define AppConfirmDialog(_title_,_okAction_) \
    QMessageBox _box; \
    QPushButton *_okBut = _box.addButton(QMessageBox::Ok); \
    QPushButton *_cancelBut = _box.addButton(QMessageBox::Cancel); \
    _box.setText(_title_); \
    _box.exec(); \
    if (_box.clickedButton() == _okBut) \
    {\
        _okAction_(); \
    }\
 \
    if (_box.clickedButton() == _cancelBut)\
    {\
        qDebug() << "cancel";\
    }\

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

#define makeFromEntity(_class_,_variable_,_entity_) _class_* _variable_ = dynamic_cast<_class_ *>(_entity_.get())

#define attr(__name__,__params__) \
    std::make_pair(QString( __name__),QString(__params__))

#define nullattr std::make_pair(QString(""), QString(""))
#define IDattr std::make_pair(QString("id"), \
                    QString("INT UNSIGNED AUTO_INCREMENT PRIMARY KEY"))

//reference_cascade("users", "user_id")
#define attr_reference_cascade(__destination_table_name__,__self__) \
    std::make_pair(QString(__self__), \
                   QString(QString(" INT UNSIGNED NOT NULL, \n FOREIGN KEY (") + __self__ + QString(") REFERENCES ") +  \
                   __destination_table_name__ + QString("(id)") + QString(" on delete cascade")))

#endif // MAGIC_H
