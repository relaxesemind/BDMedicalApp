#include "consts.h"

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
    if (table_name == DBConst::TABLE_NAME_LINE)
    {
        return 8;
    }
    if (table_name == DBConst::TABLE_NAME_MARKS)
    {
        return 3;
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
             case 1: return attr("NAME"," VARCHAR(150) NOT NULL ");
             case 2: return attr("IMAGES", " INT DEFAULT 0 ");
             case 3: return attr("MARKS"," INT DEFAULT 0");
             case 4: return attr("DIAG_CITO"," VARCHAR(100) DEFAULT 'empty'");
             case 5: return attr("DIAG_GISTO"," VARCHAR(100) DEFAULT 'empty' ");
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
            case 1: return attr("PATH"," VARCHAR(256) NOT NULL ");
            case 2: return attr("value", " INT ");
            case 3: return attr("kernels", " VARCHAR(150) ");
            case 4: return attr("cells", " VARCHAR(150) ");
            case 5: return attr("scattered_cells", " VARCHAR(150) ");
            case 6: return attr("structures", " VARCHAR(256) ");
            case 7: return attr("bare_kernels", " VARCHAR(256) ");
            case 8: return attr("comment", " VARCHAR(256) ");
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

    if (table_name == DBConst::TABLE_NAME_LINE)
    {
        switch (index) {
        case 0: return IDattr;
        case 1: return attr("THICKNESS","INT NOT NULL");
        case 2: return attr("COLOR","VARCHAR(15)");
        case 3: return attr("POINT_X1","INT");
        case 4: return attr("POINT_Y1","INT");
        case 5: return attr("POINT_X2","INT");
        case 6: return attr("POINT_Y2","INT");
        case 7: return attr_reference_cascade(DBConst::TABLE_NAME_IMAGE,
                                              DBConst::TABLE_REFERENCE_ATTR_LINE);
        default: return nullattr;
        }
    }

    if (table_name == DBConst::TABLE_NAME_MARKS)
    {
        switch (index) {
        case 0: return IDattr;
        case 1: return attr("PATH"," VARCHAR(256) NOT NULL");
        case 2: return attr_reference_cascade(DBConst::TABLE_NAME_IMAGE,
                                              DBConst::TABLE_REFERENCE_ATTR_MARKS);
        default: return nullattr;
        }
    }

    return nullattr;
}








