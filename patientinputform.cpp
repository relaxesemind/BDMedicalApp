#include "patientinputform.h"
#include "ui_patientinputform.h"

PatientInputForm::PatientInputForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PatientInputForm)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Female",QVariant(QChar('F')));
    ui->comboBox->addItem("Male",QVariant(QChar('M')));
}

PatientInputForm::~PatientInputForm()
{
    delete ui;
}

void PatientInputForm::on_buttonBox_accepted()
{
    PatientModel patient;
    patient.name = ui->lineEdit->text();
    patient.diag_cito = ui->lineEdit_2->text();
    patient.diag_gisto = ui->lineEdit_3->text();
    patient.age = ui->lineEdit_4->text().toInt();
    patient.sex = ui->comboBox->currentData().toChar();
    emit patientData(patient);
}
