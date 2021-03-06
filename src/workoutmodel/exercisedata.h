#ifndef EXERCISEDATA_H
#define EXERCISEDATA_H

#include <QString>

class ExerciseData {

public:
    explicit ExerciseData(int exerciseId = 0, QString exerciseName = "", QString exerciseDescription = "", QString exerciseCategory = "", QString exerciseImage = "");
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
    void setExerciseImage(QString exerciseImage);

private:
    int m_exerciseId;
    QString m_exerciseName;
    QString m_exerciseDescription;
    QString m_exerciseCategory;
    QString m_exerciseImage;

};

#endif // EXERCISEDATA_H
