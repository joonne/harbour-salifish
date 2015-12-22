#include "excercisedata.h"

ExcerciseData::ExcerciseData(QObject *parent, int excerciseId, QString excerciseName, QString excerciseDescription, QString excerciseCategory) :
    QObject(parent)
{
    myExcerciseId = excerciseId;
    myExcerciseName = excerciseName;
    myExcerciseDescription = excerciseDescription;
    myExcerciseCategory = excerciseCategory;
}

ExcerciseData::~ExcerciseData() { }

QString ExcerciseData::getExcerciseName() {
    return myExcerciseName;
}

QString ExcerciseData::getExcerciseDescription() {
    return myExcerciseDescription;
}

void ExcerciseData::setExcerciseName(QString excerciseName) {

    if(myExcerciseName != excerciseName) {
        myExcerciseName = excerciseName;
    }
}

void ExcerciseData::setExcerciseDescription(QString excerciseDescription) {

    if(myExcerciseDescription != excerciseDescription) {
        myExcerciseDescription = excerciseDescription;
    }
}

