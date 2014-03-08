#ifndef GYMDATABASE_H
#define GYMDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QSqlQuery>
#include <QTextStream>
#include <QStandardPaths>

class GymDatabase : public QObject
{
    Q_OBJECT
public:
    explicit GymDatabase(QObject *parent = 0);
    ~GymDatabase();

    bool openDB();
    bool deleteDB();
    QSqlError lastError();
    void close();
    bool createDB();
    bool upgradeDB();

    bool createChestTable();
    bool insertChestExcercise(QString name, QString description);

    bool createShouldersTable();
    bool insertShouldersExcercise(QString name, QString description);

    bool createAbsTable();
    bool insertAbsEcercise(QString name, QString description);

    bool createBicepsTable();
    bool insertBicepsExcercise(QString name, QString description);

    bool createForearmsTable();
    bool insertForearmsExcercise(QString name, QString description);

    bool createQuadsTable();
    bool insertQuadsExcercise(QString name, QString description);

    bool createCalvesTable();
    bool insertCalvesExcercise(QString name, QString description);

    bool createTrapeziusTable();
    bool insertTrapeziusExcercise(QString name, QString description);

    bool createLatsTable();
    bool insertLatsExcercise(QString name, QString description);

    bool createTricepsTable();
    bool insertTricepsExcercise(QString name, QString description);

    bool createGlutesTable();
    bool insertGlutesExcercise(QString name, QString description);

    bool createHamstringsTable();
    bool insertHamstringsExcercise(QString name, QString description);

    bool createWorkoutTable(QString workoutname);
    bool insertWorkout(QString workoutname);

    bool createWorkoutNamesTable();
    bool insertWorkoutName(QString name);

    bool createPreviousWorkoutNamesTable();
    bool insertPreviousWorkoutName(QString name, QString date);

    bool createPreviousWorkoutsTable(QString workoutname);
    bool insertPreviousWorkoutExcercise(QString workoutname);

private:

    QSqlDatabase db;
};

#endif // GYMDATABASE_H
