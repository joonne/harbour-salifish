#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mydbmanager = new DatabaseManager(this);
    mydbmanager->setUpDB();

    myExcerciseModel = new ExcerciseModel(this, mydbmanager);
    myWorkoutModel = new WorkoutModel(this, mydbmanager);
    myapireader = new APIReader(this, mydbmanager);
    myUser = new User(this, mydbmanager);

}

ExcerciseModel* Controller::getExcerciseModel() {
    return myExcerciseModel;
}

WorkoutModel* Controller::getWorkoutModel() {
    return myWorkoutModel;
}

User* Controller::getUser() {
    return myUser;
}

