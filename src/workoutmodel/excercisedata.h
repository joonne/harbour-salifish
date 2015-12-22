#ifndef EXCERCISEDATA_H
#define EXCERCISEDATA_H

#include <QObject>

class ExcerciseData : public QObject
{
    Q_OBJECT
public:
    explicit ExcerciseData(QObject *parent = 0, int excerciseId = 0, QString excerciseName = "", QString excerciseDescription = "", QString excerciseCategory = "");
    ~ExcerciseData();

    int getExcerciseId();
    void setExcerciseId(int excerciseId);

    QString getExcerciseName();
    void setExcerciseName(QString excerciseName);

    QString getExcerciseDescription();
    void setExcerciseDescription(QString excerciseDescription);

    QString getCategory();
    void setCategory(QString category);

private:
    int myExcerciseId;
    QString myExcerciseName;
    QString myExcerciseDescription;
    QString myExcerciseCategory;

};

#endif // EXCERCISEDATA_H
