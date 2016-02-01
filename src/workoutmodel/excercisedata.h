#ifndef EXCERCISEDATA_H
#define EXCERCISEDATA_H

#include <QString>

class ExcerciseData
{

public:
    explicit ExcerciseData(int excerciseId = 0, QString excerciseName = "", QString excerciseDescription = "", QString excerciseCategory = "");
    ~ExcerciseData();

    int getExcerciseId();
    void setExcerciseId(int excerciseId);

    QString getExcerciseName();
    void setExcerciseName(QString excerciseName);

    QString getExcerciseDescription();
    void setExcerciseDescription(QString excerciseDescription);

    QString getExcerciseCategory();
    void setExcerciseCategory(QString excerciseCategory);

private:
    int myExcerciseId;
    QString myExcerciseName;
    QString myExcerciseDescription;
    QString myExcerciseCategory;


};

#endif // EXCERCISEDATA_H
