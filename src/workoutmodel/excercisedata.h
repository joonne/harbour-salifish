#ifndef EXCERCISEDATA_H
#define EXCERCISEDATA_H

#include <QObject>

class ExcerciseData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ExcerciseName READ getExcerciseName WRITE setExcerciseName NOTIFY excerciseNameChanged)
    Q_PROPERTY(QString ExcerciseDescription READ getExcerciseDescription WRITE setExcerciseDescription NOTIFY excerciseDescriptionChanged)
    Q_PROPERTY(int repeats READ getRepeats WRITE setRepeats NOTIFY repeatsChanged)
    Q_PROPERTY(double weights READ getWeights WRITE setWeights NOTIFY weightsChanged)
public:
    explicit ExcerciseData(QObject *parent = 0);
    ~ExcerciseData();

    QString getExcerciseName();
    void setExcerciseName(QString excerciseName);

    QString getExcerciseDescription();
    void setExcerciseDescription(QString excerciseDescription);

    int getRepeats();
    void setRepeats(int repeats);

    double getWeights();
    void setWeights(double weights);

signals:
    void excerciseNameChanged();
    void excerciseDescriptionChanged();
    void repeatsChanged();
    void weightsChanged();

public slots:

private:
    QString myExcerciseName;
    QString myExceriseDescription;
    int myRepeats;
    double myWeights;

};

#endif // EXCERCISE_H
