#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "workoutmodel/excercisemodel.h"
#include "apireader.h"
#include "databasemanager.h"
#include "user.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ExcerciseModel* excerciseModel READ getExcerciseModel)

public:
    explicit Controller(QObject *parent = 0);

    ExcerciseModel* getExcerciseModel();

signals:

public slots:

private:
    ExcerciseModel* myExcerciseModel;
    DatabaseManager* mydbmanager;
    APIReader* myapireader;

};

#endif // CONTROLLER_H
