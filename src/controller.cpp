#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    mydbmanager = new DatabaseManager(this);
    mydbmanager->setUpDB();

    myExcerciseModel = new ExcerciseModel(this, mydbmanager);
    myapireader = new APIReader(this, mydbmanager);

}

ExcerciseModel* Controller::getExcerciseModel() {
    return myExcerciseModel;
}

