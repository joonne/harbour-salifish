#include "exercisedata.h"
#include <QDebug>

ExerciseData::ExerciseData(int exerciseId, QString exerciseName, QString exerciseDescription, QString exerciseCategory, QString exerciseImage)
{
    m_exerciseId = exerciseId;
    m_exerciseName = exerciseName;
    m_exerciseDescription = exerciseDescription;
    m_exerciseCategory = exerciseCategory;
    m_exerciseImage = exerciseImage;
}

ExerciseData::~ExerciseData() { }

int ExerciseData::getExerciseId() { return m_exerciseId; }

QString ExerciseData::getExerciseName() { return m_exerciseName; }

QString ExerciseData::getExerciseDescription() { return m_exerciseDescription; }

QString ExerciseData::getExerciseCategory() { return m_exerciseCategory; }

QString ExerciseData::getExerciseImage() { return m_exerciseImage; }

void ExerciseData::setExerciseId(int exerciseId)
{
    if (m_exerciseId != exerciseId) {
        m_exerciseId = exerciseId;
    }
}

void ExerciseData::setExerciseName(QString exerciseName)
{
    if (m_exerciseName != exerciseName) {
        m_exerciseName = exerciseName;
    }
}

void ExerciseData::setExerciseDescription(QString exerciseDescription)
{
    if (m_exerciseDescription != exerciseDescription) {
        m_exerciseDescription = exerciseDescription;
    }
}

void ExerciseData::setExerciseCategory(QString exerciseCategory)
{
    if (m_exerciseCategory != exerciseCategory) {
        m_exerciseCategory = exerciseCategory;
    }
}

void ExerciseData::setExerciseImage(QString exerciseImage)
{
    if (m_exerciseImage != exerciseImage) {
        m_exerciseImage = exerciseImage;
    }
}
