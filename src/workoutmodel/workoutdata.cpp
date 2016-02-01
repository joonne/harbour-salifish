#include "workoutdata.h"

WorkoutData::WorkoutData(int excerciseId, QString excerciseName, QString excerciseDescription, QString excerciseCategory, double weigths, int reps)
{
    myExcerciseId = excerciseId;
    myExcerciseName = excerciseName;
    myExcerciseDescription = excerciseDescription;
    myExcerciseCategory = excerciseCategory;
    myExcerciseWeights = weigths;
    myExcerciseReps = reps;

}

int WorkoutData::getExcerciseId() {
    return myExcerciseId;
}

QString WorkoutData::getExcerciseName() {
    return myExcerciseName;
}

QString WorkoutData::getExcerciseDescription() {
    return myExcerciseDescription;
}

QString WorkoutData::getExcerciseCategory() {
    return myExcerciseCategory;
}

void WorkoutData::setExcerciseId(int excerciseId) {

    if(myExcerciseId != excerciseId) {
        myExcerciseId = excerciseId;
    }
}

void WorkoutData::setExcerciseName(QString excerciseName) {

    if(myExcerciseName != excerciseName) {
        myExcerciseName = excerciseName;
    }
}

void WorkoutData::setExcerciseDescription(QString excerciseDescription) {

    if(myExcerciseDescription != excerciseDescription) {
        myExcerciseDescription = excerciseDescription;
    }
}

void WorkoutData::setExcerciseCategory(QString excerciseCategory) {

    if(myExcerciseCategory != excerciseCategory) {
        myExcerciseCategory = excerciseCategory;
    }
}

double WorkoutData::getWeights() {
    return myExcerciseWeights;
}

void WorkoutData::setWeights(double excerciseWeights) {

    if(myExcerciseWeights != excerciseWeights) {
        myExcerciseWeights = excerciseWeights;
    }
}

int WorkoutData::getReps() {
    return myExcerciseReps;
}

void WorkoutData::setReps(int excerciseReps) {

    if(myExcerciseReps != excerciseReps) {
        myExcerciseReps = excerciseReps;
    }
}
