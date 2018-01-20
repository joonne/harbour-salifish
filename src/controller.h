#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "workoutmodel/exercisemodel.h"
#include "workoutmodel/workoutmodel.h"
#include "apireader.h"
#include "databasemanager.h"
#include "user.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ExerciseModel* exerciseModel READ getExerciseModel)
    Q_PROPERTY(WorkoutModel* workoutModel READ getWorkoutModel)
    Q_PROPERTY(User* user READ getUser)

public:
    explicit Controller(QObject *parent = 0);

    ExerciseModel* getExerciseModel();
    WorkoutModel* getWorkoutModel();
    User* getUser();

    Q_INVOKABLE QVariantList getMuscleModel();
    Q_INVOKABLE QVariantList getCategoryModel();

signals:

public slots:

private:
    ExerciseModel* myExerciseModel;
    WorkoutModel* myWorkoutModel;
    DatabaseManager* mydbmanager;
    APIReader* myapireader;
    User* myUser;

};

#endif // CONTROLLER_H
