#include "exercisedata.h"
#include <QDebug>

ExerciseData::ExerciseData(int exerciseId, QString exerciseName, QString exerciseDescription, QString exerciseCategory)
{
    myExerciseId = exerciseId;
    myExerciseName = exerciseName;
    myExerciseDescription = exerciseDescription;
    myExerciseCategory = exerciseCategory;
}

ExerciseData::~ExerciseData() { }

int ExerciseData::getExerciseId() {
    return myExerciseId;
}

QString ExerciseData::getExerciseName() {
    return myExerciseName;
}

QString ExerciseData::getExerciseDescription() {
    return myExerciseDescription;
}

QString ExerciseData::getExerciseCategory() {
    return myExerciseCategory;
}

void ExerciseData::setExerciseId(int exerciseId) {

    if(myExerciseId != exerciseId) {
        myExerciseId = exerciseId;
    }
}

void ExerciseData::setExerciseName(QString exerciseName) {

    if(myExerciseName != exerciseName) {
        myExerciseName = exerciseName;
    }
}

void ExerciseData::setExerciseDescription(QString exerciseDescription) {

    if(myExerciseDescription != exerciseDescription) {
        myExerciseDescription = exerciseDescription;
    }
}

void ExerciseData::setExerciseCategory(QString exerciseCategory) {

    if(myExerciseCategory != exerciseCategory) {
        myExerciseCategory = exerciseCategory;
    }
}
