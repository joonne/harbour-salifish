#ifndef EXERCISEDATA_H
#define EXERCISEDATA_H

#include <QString>

class ExerciseData {

public:
    explicit ExerciseData(int exerciseId = 0, QString exerciseName = "", QString exerciseDescription = "", QString exerciseCategory = "");
    ~ExerciseData();

    int getExerciseId();
    void setExerciseId(int exerciseId);

    QString getExerciseName();
    void setExerciseName(QString exerciseName);

    QString getExerciseDescription();
    void setExerciseDescription(QString exerciseDescription);

    QString getExerciseCategory();
    void setExerciseCategory(QString exerciseCategory);

    QString getExerciseImage();
    void setExerciseImage();

private:
    int myExerciseId;
    QString myExerciseName;
    QString myExerciseDescription;
    QString myExerciseCategory;

};

#endif // EXERCISEDATA_H
