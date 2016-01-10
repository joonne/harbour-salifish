#include "excercisedata.h"

ExcerciseData::ExcerciseData(int excerciseId, QString excerciseName, QString excerciseDescription, QString excerciseCategory)
{
    myExcerciseId = excerciseId;
    myExcerciseName = excerciseName;
    myExcerciseDescription = excerciseDescription;
    myExcerciseCategory = excerciseCategory;
}

ExcerciseData::~ExcerciseData() { }

int ExcerciseData::getExcerciseId() {
    return myExcerciseId;
}

QString ExcerciseData::getExcerciseName() {
    return myExcerciseName;
}

QString ExcerciseData::getExcerciseDescription() {
    return myExcerciseDescription;
}

QString ExcerciseData::getExcerciseCategory() {
    return myExcerciseCategory;
}

void ExcerciseData::setExcerciseId(int excerciseId) {

    if(myExcerciseId != excerciseId) {
        myExcerciseId = excerciseId;
    }
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

void ExcerciseData::setExcerciseCategory(QString excerciseCategory) {

    if(myExcerciseCategory != excerciseCategory) {
        myExcerciseCategory = excerciseCategory;
    }
}
