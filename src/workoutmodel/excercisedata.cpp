#include "excercisedata.h"

ExcerciseData::ExcerciseData(QObject *parent) :
    QObject(parent)
{
}

ExcerciseData::~ExcerciseData() { }

QString ExcerciseData::getExcerciseName() {
    return myExcerciseName;
}

QString ExcerciseData::getExcerciseDescription() {
    return myExceriseDescription;
}

int ExcerciseData::getRepeats() {
    return myRepeats;
}

double ExcerciseData::getWeights() {
    return myWeights;
}

void ExcerciseData::setExcerciseName(QString excerciseName) {

    if(myExcerciseName != excerciseName) {
        myExcerciseName = excerciseName;
        emit excerciseNameChanged();
    }
}

void ExcerciseData::setExcerciseDescription(QString excerciseDescription) {

    if(myExceriseDescription != excerciseDescription) {
        myExceriseDescription = excerciseDescription;
        emit excerciseDescriptionChanged();
    }
}

void ExcerciseData::setRepeats(int repeats) {

    if(myRepeats != repeats) {
        myRepeats = repeats;
        emit repeatsChanged();
    }
}

void ExcerciseData::setWeights(double weights) {

    if(myWeights != weights) {
        myWeights = weights;
        emit weightsChanged();
    }
}
