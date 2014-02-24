#ifndef GYMMODEL_H
#define GYMMODEL_H

#include <QObject>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QVector>
#include <QQmlContext>
#include <QDate>

class GymModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Name READ getName
               WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString Description READ getDescription
               WRITE setDescription NOTIFY DescriptionChanged)
    Q_PROPERTY(QString SelectedMuscle READ getSelectedMuscle WRITE setSelectedMuscle
               NOTIFY SelectedMuscleChanged)
    Q_PROPERTY(QString SelectedExcercise READ getSelectedExcercise WRITE setSelectedExcercise
               NOTIFY SelectedExcerciseChanged)
    //Q_PROPERTY(int SelectedExcercisesCount READ getSelectedExcercisesCount NOTIFY selectedExcercisesCountChanged)
    Q_PROPERTY(QString ExcerciseName READ getExcerciseName WRITE setExcerciseName NOTIFY excerciseNameChanged)
    Q_PROPERTY(QString ExcerciseDescription READ getExcerciseDescription WRITE setExcerciseDescription NOTIFY excerciseDescriptionChanged)
    Q_PROPERTY(QString Mode READ getMode WRITE setMode NOTIFY modeChanged)
    //Q_PROPERTY(int series READ getSeries WRITE setSeries NOTIFY seriesChanged)
    //Q_PROPERTY(int repeats READ getRepeats WRITE setRepeats NOTIFY repeatsChanged)
    //Q_PROPERTY(double weights READ getWeights WRITE setWeights NOTIFY weightsChanged)
    Q_PROPERTY(int currentSeriesIndex READ getCurrentSeriesIndex NOTIFY currentSeriesIndexChanged)

public:
    explicit GymModel(QObject *parent = 0);
    ~GymModel();

    Q_INVOKABLE void clean();

    QString getName();
    QString getSelectedMuscle();
    QString getSelectedExcercise();
    QString getDescription();
    QString getExcerciseName();
    QString getExcerciseDescription();
    QString getMode();

    void setName(QString excerciseName);
    void setSelectedMuscle(QString selectedMuscle);
    void setSelectedExcercise(QString selectedExcercise);
    void setDescription(QString description);
    void setExcerciseName(QString excerciseName);
    void setExcerciseDescription(QString excerciseDescription);
    void setContext(QQmlContext* context);
    void setMode(QString mode);

    // These are for the database
    bool openDB();
    void closeDB();
    bool insertExcerciseName(QString excerciseName);
    bool insertExcerciseDescription(QString description);
    Q_INVOKABLE bool getExcercises();
    Q_INVOKABLE bool getExcercise(QString excercise);
    Q_INVOKABLE bool insertExcercise();
    Q_INVOKABLE bool insertWorkoutExcercises();
    Q_INVOKABLE bool createWorkout();
    Q_INVOKABLE bool createPreviousWorkout();
    Q_INVOKABLE bool deleteExcerciseFromDB();
    Q_INVOKABLE bool deleteWorkoutFromDB(QString workoutName);
    Q_INVOKABLE bool getWorkouts();
    bool getWorkoutTables();
    Q_INVOKABLE bool getWorkout(QString workout);
    Q_INVOKABLE bool updateExcercise();
    Q_INVOKABLE bool getPreviousWorkouts();

    Q_INVOKABLE QStringList excerciseNames();
    Q_INVOKABLE void addExcercise(QString excercise);
    Q_INVOKABLE void removeExcercise(QString excercise);
    //Q_INVOKABLE void removeExcercises();
    Q_INVOKABLE void removeWorkout(QString workout);
    Q_INVOKABLE bool isExcerciseSelected(QString excercise);
    Q_INVOKABLE void setWorkoutName(QString workoutName);
    Q_INVOKABLE QString getWorkoutName();
    //Q_INVOKABLE QString getExcerciseDescription();
    //Q_INVOKABLE QString getEcerciseName();
    Q_INVOKABLE int getExcerciseCount();
    Q_INVOKABLE int getSelectedExcercisesCount();
    Q_INVOKABLE void clearSelectedExcercises();
    Q_INVOKABLE void removeWorkoutExcercise(QString excercise);
    Q_INVOKABLE QString nextCoverExcercise();
    Q_INVOKABLE QString previousCoverExcercise();

    bool findExcerciseIndex();
    bool findWorkoutExcerciseIndex(QString excerciseName);
    bool findWorkoutIndex(QString workoutName);


    Q_INVOKABLE void setSeries(QString excercisename, int series);
    Q_INVOKABLE void setRepeats(QString excercisename,int repeats, int currentSerie);
    Q_INVOKABLE void setWeights(QString excercisename,double weights, int currentSerie);
    Q_INVOKABLE void setComments(QString excercisename,QString comments);

    Q_INVOKABLE int getSeries(QString excerciseName);
    Q_INVOKABLE int getRepeats(QString excerciseName, int currentSerie);
    Q_INVOKABLE double getWeights(QString excerciseName, int currentSerie);
    Q_INVOKABLE QString getComments(QString excerciseName);

    Q_INVOKABLE void increaseCurrentSeriesIndex();
    Q_INVOKABLE void decreaseCurrentSeriesIndex();
    int getCurrentSeriesIndex();

    void clearWorkout();

signals:

    void nameChanged();
    void SelectedMuscleChanged();
    void SelectedExcerciseChanged();
    void DescriptionChanged();
    void selectedExcercisesCountChanged();
    void excerciseNameChanged();
    void excerciseDescriptionChanged();
    void modeChanged();
    void seriesChanged();
    void repeatsChanged();
    void weightsChanged();
    void currentSeriesIndexChanged();

private:

    //User* user_;  // Mahdollinen ominaisuus lisätä useita käyttäjiä
    QString name_;   // addNewExcercise
    QString description_; // addNewErcercise
    QString selectedMuscle_; // createWorkout
    QString selectedExcercise_; // showDescription
    QSqlDatabase db_;
    QStringList excerciseNames_; // All excercises of musclegroup
    QString excerciseName_; // getting excercise with index
    QString excerciseDescription_; // getting excercise with index
    QStringList selectedExcercises_; // Workout's excercises
    QString workoutName_; // Workout's name from createWorkoutPage and WorkoutPage
    QStringList workoutNames_; // All names of own workouts, with these we search from db.
    QStringList workoutTableNames_;
    //QStringList workouts_; // nothing yet.
    int excerciseCount_;
    QStringList series_;
    QStringList repeats_;
    QStringList weights_;
    QStringList comments_;
    QStringList excercises_;
    QQmlContext* context_;
    int excerciseIndex_;
    int workoutExcerciseIndex_;
    int workoutIndex_;
    QStringList workout_;
    QStringList previousWorkouts_; // Earlier workouts in the FirstPage
    QStringList previousWorkoutTableNames_;
    QString mode_;
    int coverExcerciseIndex_;
    int currentSeriesIndex_;
};

#endif // GYMMODEL_H
