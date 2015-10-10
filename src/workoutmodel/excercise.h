#ifndef EXCERCISE_H
#define EXCERCISE_H

#include <QObject>

class Excercise : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ExcerciseName READ getExcerciseName WRITE setExcerciseName NOTIFY excerciseNameChanged)
    Q_PROPERTY(QString ExcerciseDescription READ getExcerciseDescription WRITE setExcerciseDescription NOTIFY excerciseDescriptionChanged)
//    Q_PROPERTY(int series READ getSeries WRITE setSeries NOTIFY seriesChanged)
    Q_PROPERTY(int repeats READ getRepeats WRITE setRepeats NOTIFY repeatsChanged)
    Q_PROPERTY(double weights READ getWeights WRITE setWeights NOTIFY weightsChanged)
public:
    explicit Excercise(QObject *parent = 0);

    QString getExcerciseName();
    void setExcerciseName(QString excerciseName);

    QString getExcerciseDescription();
    void setExcerciseDescription(QString excerciseDescription);

//    int getSeries();
//    void setSeries(int series);

    int getRepeats();
    double getWeights();

signals:
    void excerciseNameChanged();
    void excerciseDescriptionChanged();
//    void seriesChanged();
    void repeatsChanged();
    void weightsChanged();

public slots:

private:
    QString myExcerciseName;
    QString myExceriseDescription;
//    int mySeries;
    int myRepeats;
    double myWeights;

};

#endif // EXCERCISE_H
