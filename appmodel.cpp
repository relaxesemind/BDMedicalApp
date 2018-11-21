#include "appmodel.h"
#include "Common/consts.h"

void APPModel::initModels()
{
    setupPatientTableModel();
}

void APPModel::update()
{
    patientTableModel.select();
}

void APPModel::setupPatientTableModel()
{
    patientTableModel.setTable(DBConst::TABLE_NAME_PATIENT);
    patientTableModel.setEditStrategy(QSqlTableModel::OnFieldChange);
    patientTableModel.setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    patientTableModel.setHeaderData(1,Qt::Horizontal,QObject::tr("Имя"));
    patientTableModel.setHeaderData(2,Qt::Horizontal,QObject::tr("Изображения"));
    patientTableModel.setHeaderData(3,Qt::Horizontal,QObject::tr("Метки"));
    patientTableModel.setHeaderData(4,Qt::Horizontal,QObject::tr("Цитологический диагноз"));
    patientTableModel.setHeaderData(5,Qt::Horizontal,QObject::tr("Гистологический диагноз"));
    patientTableModel.setHeaderData(6,Qt::Horizontal,QObject::tr("Пол"));
    patientTableModel.setHeaderData(7,Qt::Horizontal,QObject::tr("Возраст"));
}
