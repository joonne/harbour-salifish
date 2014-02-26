#include "gymdatabasemanager.h"
#include <QDebug>

GymDatabase::GymDatabase(QObject *parent) :
    QObject(parent)
{
}

GymDatabase::~GymDatabase() {}

bool GymDatabase::openDB() {

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gymDatabase.db.sqlite");

    // Open databasee
    return db.open();
}

QSqlError GymDatabase::lastError() {

    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool GymDatabase::deleteDB() {

    // Close database
    db.close();

    // Remove created database binary file
    return QFile::remove("gymDatabase.db.sqlite");
}

void GymDatabase::close() {
    db.close();
}

bool GymDatabase::createChestTable() {

    // Create table "chest"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table chest"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertChestExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into chest values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createShouldersTable() {

    // Create table shoulders
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("CREATE TABLE shoulders"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertShouldersExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("INSERT INTO shoulders VALUES(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createAbsTable() {

    // Create table abs
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table abs"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertAbsEcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into abs values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createBicepsTable() {

    // Create table biceps
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table biceps"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertBicepsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into biceps values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createForearmsTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table forearms"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertForearmsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into forearms values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createQuadsTable() {

    // Create table quads
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table quads"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertQuadsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into quads values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createCalvesTable() {

    // Create table calves
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table calves"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertCalvesExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into calves values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createTrapeziusTable() {

    // Create table trapezius
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table trapezius"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertTrapeziusExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into trapezius values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createLatsTable() {

    // Create table lats
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table lats"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertLatsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into lats values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createTricepsTable() {

    // Create table triceps
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table triceps"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertTricepsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into triceps values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createGlutesTable() {

    // Create table glutes
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table glutes"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertGlutesExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into glutes values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::createHamstringsTable() {

    // Create table hamstrings
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec("create table hamstrings"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool GymDatabase::insertHamstringsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into hamstrings values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool GymDatabase::insertWorkout(QString workoutname) {

    bool ret = false;

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-workout";

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into '%1' values(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                         .arg(tablename)
                         .arg("Bench Press")
                         .arg(3)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg(0).arg(0));
        qDebug() << query.lastError();

        ret = query.exec(QString("insert into '%1' values(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                         .arg(tablename)
                         .arg("Butterfly Machine")
                         .arg(3)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg(0).arg(0));
        qDebug() << query.lastError();

        ret = query.exec(QString("insert into '%1' values(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                         .arg(tablename)
                         .arg("Shoulder Press")
                         .arg(3)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg(0).arg(0));
        qDebug() << query.lastError();

        ret = query.exec(QString("insert into '%1' values(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                         .arg(tablename)
                         .arg("Dumbbel Front Raise")
                         .arg(3)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(12).arg(80)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg(0).arg(0));
        qDebug() << query.lastError();

    }
    return ret;
}

bool GymDatabase::createWorkoutTable(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-workout";

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("create table '%1'"
                                 "(id integer primary key, "
                                 "excercisename varchar(50), "
                                 "series integer, "
                                 "repeats1 integer, "
                                 "weights1 real, "
                                 "repeats2 integer, "
                                 "weights2 real, "
                                 "repeats3 integer, "
                                 "weights3 real, "
                                 "repeats4 integer, "
                                 "weights4 real, "
                                 "repeats5 integer, "
                                 "weights5 real, "
                                 "repeats6 integer, "
                                 "weights6 real)").arg(tablename));
    }
    return ret;
}


bool GymDatabase::createWorkoutNamesTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("create table workoutnames"
                                 "(id integer primary key, "
                                 "workoutname varchar(50), "
                                 "tablename varchar(50))"));

    }
    return ret;
}

bool GymDatabase::insertWorkoutName(QString name) {

    QStringRef sub(&name, 0, 3);
    QString tablename = sub.toString() + "-workout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into workoutnames values(NULL,'%1','%2')")
                         .arg(name).arg(tablename));

    }
    return ret;
}

bool GymDatabase::createPreviousWorkoutNamesTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("create table previousworkoutnames"
                                 "(id integer primary key, "
                                 "workoutname varchar(50), "
                                 "tablename varchar(50), "
                                 "date varchar(50))"));

    }
    return ret;
}

bool GymDatabase::insertPreviousWorkoutName(QString name, QString date) {

    QStringRef sub(&name, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into previousworkoutnames values(NULL,'%1','%2','%3')")
                         .arg(name).arg(tablename).arg(date));

    }
    return ret;
}


bool GymDatabase::createPreviousWorkoutsTable(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("CREATE TABLE '%1'"
                                  "(id integer primary key, "
                                  "excercisename varchar(50), "
                                  "series integer, "
                                  "repeats1 integer, "
                                  "weights1 real, "
                                  "repeats2 integer, "
                                  "weights2 real, "
                                  "repeats3 integer, "
                                  "weights3 real, "
                                  "repeats4 integer, "
                                  "weights4 real, "
                                  "repeats5 integer, "
                                  "weights5 real, "
                                  "repeats6 integer, "
                                  "weights6 real, "
                                  "comments varchar(160))").arg(tablename));

    }
    return ret;
}

bool GymDatabase::insertPreviousWorkoutExcercise(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query;
        ret = query.exec(QString("insert into '%1' values(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15,'%16')")
                         .arg(tablename)
                         .arg("Bench Press")
                         .arg(3)
                         .arg(12).arg(70)
                         .arg(12).arg(70)
                         .arg(12).arg(70)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg(0).arg(0)
                         .arg("Went well."));
        qDebug() << query.lastError();

    }
    return ret;
}
