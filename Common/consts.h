#ifndef CONSTS_H
#define CONSTS_H

#include <QString>

namespace Global
{
    const QString CHOOSE_IMAGE_WINDOW_TITLE = "Выберите BMP файл";
    const QString CHOOSE_IMAGE_TYPES        = "Bitmap files (*.bmp);;All files (*.*)";
};

namespace DBConst
{
    const QString DATABASE_HOSTNAME            = "localhost";
    const QString DATABASE_NAME                = "APPDATA";
    const QString DATABASE_DRIVER_TYPE         = "QMYSQL";
    const QString DATABASE_USER_NAME           = "root";
    const QString DATABASE_USER_PASSWORD       = "0000";
    const qint32  DATABASE_HOST_PORT           = 3306;
    const QString QUERY_CREATE_DATABASE        = "CREATE DATABASE IF NOT EXISTS ";
    const QString QUERY_CREATE_TABLE           = "CREATE TABLE IF NOT EXISTS ";
    const QString QUERY_INSERT                 = "INSERT INTO ";
    const QString QUERY_SELECT                 = "SELECT ";
    const QString TABLE_NAME_PATIENT           = "PATIENT_TABLE";
    const QString TABLE_NAME_IMAGE             = "IMAGE_TABLE";
    const QString TABLE_NAME_CIRCLE            = "CIRCLE_TABLE";
    const QString TABLE_NAME_RECT              = "RECT_TABLE";
    const QString TABLE_ID_ATTR_NAME           = "id";
    const QString TABLE_DEFAULT_ATTR           = "id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY";
    const QString TABLE_REFERENCE_ATTR_IMAGE   = "patient_id";
    const QString TABLE_REFERENCE_ATTR_CIRCLE  = "image_id";
    const QString TABLE_REFERENCE_ATTR_RECT    = "image_id";
    const QString COMMA_SYMBOL                 = ",";
    int TABLE_NUMBER_OF_ATTR(const QString& table_name);
    const std::pair<QString, QString> ATTRIBUTE(const QString& table_name, int index);
};

#endif // CONSTS_H
