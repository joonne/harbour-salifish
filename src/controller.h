#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "workoutmodel/excercisemodel.h"
#include "workoutmodel/workoutmodel.h"
#include "apireader.h"
#include "databasemanager.h"
#include "user.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ExcerciseModel* excerciseModel READ getExcerciseModel)
    Q_PROPERTY(WorkoutModel* workoutModel READ getWorkoutModel)
    Q_PROPERTY(User* user READ getUser)

public:
    explicit Controller(QObject *parent = 0);

    ExcerciseModel* getExcerciseModel();
    WorkoutModel* getWorkoutModel();
    User* getUser();

signals:

public slots:

private:
    ExcerciseModel* myExcerciseModel;
    WorkoutModel* myWorkoutModel;
    DatabaseManager* mydbmanager;
    APIReader* myapireader;
    User* myUser;

};

#endif // CONTROLLER_H
