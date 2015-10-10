#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QSqlQuery>
#include <QTextStream>
#include <QStandardPaths>
#include <QVariant>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

    void setUpDB();

    bool openDB();
    bool deleteDB();
    QSqlError lastError();
    void close();
    bool createDB();
    bool updateDB();

    bool initializeInfoTable();
    bool createInfoTable();
    bool updateInfoTable(double version);

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

    bool createUserTable();
    bool insertUser(QString name, int age, QString gender, double height, double weight);

    QMap<QString, QString> getUser();
    bool updateName(QString name);
    bool updateAge(int age);
    bool updateGender(QString gender);
    bool updateHeight(double height);
    bool updateWeight(double weight);

private:

    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
