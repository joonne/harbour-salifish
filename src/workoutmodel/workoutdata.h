#ifndef WORKOUTDATA_H
#define WORKOUTDATA_H

#include <QObject>

class WorkoutData : public QObject
{
    Q_OBJECT
public:
    explicit WorkoutData(int excerciseId = 0, QString excerciseName = "", QString excerciseDescription = "", QString excerciseCategory = "", double weigths = 0, int reps = 0);

    int getExcerciseId();
    void setExcerciseId(int excerciseId);

    QString getExcerciseName();
    void setExcerciseName(QString excerciseName);

    QString getExcerciseDescription();
    void setExcerciseDescription(QString excerciseDescription);

    QString getExcerciseCategory();
    void setExcerciseCategory(QString excerciseCategory);

    double getWeights();
    void setWeights(double excerciseWeights);

    int getReps();
    void setReps(int excerciseReps);


private:
    int myExcerciseId;
    QString myExcerciseName;
    QString myExcerciseDescription;
    QString myExcerciseCategory;
    double myExcerciseWeights;
    int myExcerciseReps;
};

#endif // WORKOUTDATA_H
