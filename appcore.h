#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>

class APPCore : public QObject
{
    Q_OBJECT
public:
    explicit APPCore(QObject *parent = nullptr);

signals:

public slots:
};

#endif // APPCORE_H