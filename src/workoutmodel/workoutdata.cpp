#include "workoutdata.h"

WorkoutData::WorkoutData(int exerciseId, QString exerciseName, QString exerciseDescription, QString exerciseCategory, double weigths, int reps)
{
    myExerciseId = exerciseId;
    myExerciseName = exerciseName;
    myExerciseDescription = exerciseDescription;
    myExerciseCategory = exerciseCategory;
    myExerciseWeights = weigths;
    myExerciseReps = reps;

}

int WorkoutData::getExerciseId() {
    return myExerciseId;
}

QString WorkoutData::getExerciseName() {
    return myExerciseName;
}

QString WorkoutData::getExerciseDescription() {
    return myExerciseDescription;
}

QString WorkoutData::getExerciseCategory() {
    return myExerciseCategory;
}

void WorkoutData::setExerciseId(int exerciseId) {

    if(myExerciseId != exerciseId) {
        myExerciseId = exerciseId;
    }
}

void WorkoutData::setExerciseName(QString exerciseName) {

    if(myExerciseName != exerciseName) {
        myExerciseName = exerciseName;
    }
}

void WorkoutData::setExerciseDescription(QString exerciseDescription) {

    if(myExerciseDescription != exerciseDescription) {
        myExerciseDescription = exerciseDescription;
    }
}

void WorkoutData::setExerciseCategory(QString exerciseCategory) {

    if(myExerciseCategory != exerciseCategory) {
        myExerciseCategory = exerciseCategory;
    }
}

double WorkoutData::getWeights() {
    return myExerciseWeights;
}

void WorkoutData::setWeights(double exerciseWeights) {

    if(myExerciseWeights != exerciseWeights) {
        myExerciseWeights = exerciseWeights;
    }
}

int WorkoutData::getReps() {
    return myExerciseReps;
}

void WorkoutData::setReps(int exerciseReps) {

    if(myExerciseReps != exerciseReps) {
        myExerciseReps = exerciseReps;
    }
}
