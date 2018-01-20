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
#include <QStandardPaths>
#include <QDir>

class GymModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Name READ getName
               WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString Description READ getDescription
               WRITE setDescription NOTIFY DescriptionChanged)
    Q_PROPERTY(QString SelectedMuscle READ getSelectedMuscle WRITE setSelectedMuscle
               NOTIFY SelectedMuscleChanged)
    Q_PROPERTY(QString SelectedExercise READ getSelectedExercise WRITE setSelectedExercise
               NOTIFY SelectedExerciseChanged)
    Q_PROPERTY(QString ExerciseName READ getExerciseName WRITE setExerciseName NOTIFY exerciseNameChanged)
    Q_PROPERTY(QString ExerciseDescription READ getExerciseDescription WRITE setExerciseDescription NOTIFY exerciseDescriptionChanged)
    Q_PROPERTY(QString Mode READ getMode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(int currentSeriesIndex READ getCurrentSeriesIndex NOTIFY currentSeriesIndexChanged)

public:
    explicit GymModel(QObject *parent = 0);
    ~GymModel();

    Q_INVOKABLE void clean();

    QString getName();
    QString getSelectedMuscle();
    QString getSelectedExercise();
    QString getDescription();
    QString getExerciseName();
    QString getExerciseDescription();
    QString getMode();

    void setName(QString exerciseName);
    void setSelectedMuscle(QString selectedMuscle);
    void setSelectedExercise(QString selectedExercise);
    void setDescription(QString description);
    void setExerciseName(QString exerciseName);
    void setExerciseDescription(QString exerciseDescription);
    void setContext(QQmlContext* context);
    void setMode(QString mode);

    // These are for the database
    bool openDB();
    void closeDB();
    bool insertExerciseName(QString exerciseName);
    bool insertExerciseDescription(QString description);
    Q_INVOKABLE bool getExercises();
    Q_INVOKABLE bool getExercise(QString exercise);
    Q_INVOKABLE bool insertExercise();
    Q_INVOKABLE bool insertWorkoutExercises();
    Q_INVOKABLE bool createWorkout();
    Q_INVOKABLE bool createPreviousWorkout();
    Q_INVOKABLE bool deleteExerciseFromDB();
    Q_INVOKABLE bool deleteWorkoutFromDB(QString workoutName);
    Q_INVOKABLE bool getWorkouts();
    Q_INVOKABLE bool getWorkout(QString workout);
    Q_INVOKABLE bool updateExercise();
    Q_INVOKABLE bool getPreviousWorkouts();

    Q_INVOKABLE QStringList exerciseNames();
    Q_INVOKABLE void addExercise(QString exercise);
    Q_INVOKABLE void removeExercise(QString exercise);
    //Q_INVOKABLE void removeExercises();
    Q_INVOKABLE void removeWorkout(QString workout);
    Q_INVOKABLE bool isExerciseSelected(QString exercise);
    Q_INVOKABLE void setWorkoutName(QString workoutName);
    Q_INVOKABLE QString getWorkoutName();
    //Q_INVOKABLE QString getExerciseDescription();
    //Q_INVOKABLE QString getEcerciseName();
    Q_INVOKABLE int getExerciseCount();
    Q_INVOKABLE int getSelectedExercisesCount();
    Q_INVOKABLE void clearSelectedExercises();
    Q_INVOKABLE void removeWorkoutExercise(QString exercise);
    Q_INVOKABLE QString nextCoverExercise();
    Q_INVOKABLE QString previousCoverExercise();

    bool findExerciseIndex();
    bool findWorkoutExerciseIndex(QString exerciseName);
    bool findWorkoutIndex(QString workoutName);


    Q_INVOKABLE void setSeries(QString exercisename, int series);
    Q_INVOKABLE void setRepeats(QString exercisename,int repeats, int currentSerie);
    Q_INVOKABLE void setWeights(QString exercisename,double weights, int currentSerie);
    Q_INVOKABLE void setComments(QString exercisename,QString comments);

    Q_INVOKABLE int getSeries(QString exerciseName);
    Q_INVOKABLE int getRepeats(QString exerciseName, int currentSerie);
    Q_INVOKABLE double getWeights(QString exerciseName, int currentSerie);
    Q_INVOKABLE QString getComments(QString exerciseName);

    Q_INVOKABLE void increaseCurrentSeriesIndex();
    Q_INVOKABLE void decreaseCurrentSeriesIndex();
    int getCurrentSeriesIndex();

    void clearWorkout();

signals:

    void nameChanged();
    void SelectedMuscleChanged();
    void SelectedExerciseChanged();
    void DescriptionChanged();
    void selectedExercisesCountChanged();
    void exerciseNameChanged();
    void exerciseDescriptionChanged();
    void modeChanged();
    void seriesChanged();
    void repeatsChanged();
    void weightsChanged();
    void currentSeriesIndexChanged();

private:

    //User* user_;  // Mahdollinen ominaisuus lisätä useita käyttäjiä
    QString name_;   // addNewExercise
    QString description_; // addNewErcercise
    QString selectedMuscle_; // createWorkout
    QString selectedExercise_; // showDescription
    QSqlDatabase db_;
    QStringList exerciseNames_; // All exercises of musclegroup
    QString exerciseName_; // getting exercise with index
    QString exerciseDescription_; // getting exercise with index
    QStringList selectedExercises_; // Workout's exercises
    QString workoutName_; // Workout's name from createWorkoutPage and WorkoutPage
    QStringList workoutNames_; // All names of own workouts, with these we search from db.
    QStringList workoutTableNames_;
    //QStringList workouts_; // nothing yet.
    int exerciseCount_;
    QStringList series_;
    QStringList repeats_;
    QStringList weights_;
    QStringList comments_;
    QStringList exercises_;
    QQmlContext* context_;
    int exerciseIndex_;
    int workoutExerciseIndex_;
    int workoutIndex_;
    QStringList workout_;
    QStringList previousWorkouts_; // Earlier workouts in the FirstPage
    QStringList previousWorkoutTableNames_;
    QString mode_;
    int coverExerciseIndex_;
    int currentSeriesIndex_;
};

#endif // GYMMODEL_H
