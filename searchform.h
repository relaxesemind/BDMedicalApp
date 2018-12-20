#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QDialog>
#include "Common/Models/models.h"
#include <QString>

namespace Ui {
class SearchForm;
}

class SearchForm : public QDialog
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = 0);
    ~SearchForm();

signals:
    void queryData(const QString& name, int min, int max, const QString& sex);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::SearchForm *ui;
};

#endif // SEARCHFORM_H
