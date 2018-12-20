#include "searchform.h"
#include "ui_searchform.h"

SearchForm::SearchForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
}

SearchForm::~SearchForm()
{
    delete ui;
}


void SearchForm::on_buttonBox_accepted()
{
    int min = 0;
    int max = 1000;
    QString name = ui->lineEdit->text();
    QString sex("X");

    if (ui->radioButton_2->isChecked())
    {
        max = 20;
    }
    if (ui->radioButton_3->isChecked())
    {
        min = 21;
        max = 30;
    }
    if (ui->radioButton_4->isChecked())
    {
        min = 31;
        max = 40;
    }
    if (ui->radioButton_5->isChecked())
    {
        min = 41;
    }
    if (ui->radioButton_7->isChecked())
    {
        sex = "M";
    }
    if (ui->radioButton_8->isChecked())
    {
        sex = "F";
    }

    emit queryData(name,min,max,sex);
}

void SearchForm::on_buttonBox_rejected()
{
    this->close();
}
