#ifndef PATIENTINPUTFORM_H
#define PATIENTINPUTFORM_H

#include <QDialog>
#include <QString>
#include <QAbstractButton>
#include "Common/Models/patientmodel.h"

namespace Ui {
class PatientInputForm;
}

class PatientInputForm : public QDialog
{
    Q_OBJECT

public:
    explicit PatientInputForm(QWidget *parent = 0);
    ~PatientInputForm();

signals:
    void patientData(const PatientModel& patient);

private slots:


    void on_buttonBox_accepted();

private:
    Ui::PatientInputForm *ui;
};

#endif // PATIENTINPUTFORM_H
