#ifndef WORKOUTDATA_H
#define WORKOUTDATA_H

#include <QObject>

class WorkoutData : public QObject
{
    Q_OBJECT
public:
    explicit WorkoutData(int exerciseId = 0, QString exerciseName = "", QString exerciseDescription = "", QString exerciseCategory = "", double weigths = 0, int reps = 0);

    int getExerciseId();
    void setExerciseId(int exerciseId);

    QString getExerciseName();
    void setExerciseName(QString exerciseName);

    QString getExerciseDescription();
    void setExerciseDescription(QString exerciseDescription);

    QString getExerciseCategory();
    void setExerciseCategory(QString exerciseCategory);

    double getWeights();
    void setWeights(double exerciseWeights);

    int getReps();
    void setReps(int exerciseReps);


private:
    int myExerciseId;
    QString myExerciseName;
    QString myExerciseDescription;
    QString myExerciseCategory;
    double myExerciseWeights;
    int myExerciseReps;
};

#endif // WORKOUTDATA_H
