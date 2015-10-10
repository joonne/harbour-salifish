#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    setUpDB();
    close();
}

DatabaseManager::~DatabaseManager() {

    qDebug() << "Destroying gymdbmanager..";
    deleteDB();
}

void DatabaseManager::setUpDB() {

    if(openDB()) {

        QSqlQuery query(db);
        query.exec("SELECT count(*) FROM sqlite_master WHERE type = 'table';");
        int tableCount = query.value(1).toInt();
        qDebug() << "Tables in DatabaseManager: " << tableCount;

        if(tableCount == 0) {

            createDB();

        } else {

            QSqlQuery query(db);
            query.exec("SELECT version FROM information;");
            double version = query.value(1).toDouble();

            qDebug() << "Database already created, current version is: " << version;

            updateDB();
        }
    }

    close();

}

bool DatabaseManager::openDB() {

    QString dbname = "salifish.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    if(!dir.exists()) {
        dir.mkpath(".");
    }

    // Find SQLite driver
    db = QSqlDatabase::addDatabase("QSQLITE","databasemanager");
    db.setDatabaseName(dbpath);

    // Open databasee
    return db.open();
}

QSqlError DatabaseManager::lastError() {

    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::deleteDB() {

    // Close database
    db.close();

    // Remove created database binary file
    QString dbname = "DatabaseManager.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    return QFile::remove(dbpath);
}

void DatabaseManager::close() {
    db.close();
}

bool DatabaseManager::initializeInfoTable() {

    bool ret = createInfoTable();

    if(ret) {

        QSqlQuery query(db);
        return query.exec(QString("INSERT INTO information VALUES(%1,'%2')")
                          .arg(1.0).arg("SaliFish"));
    }
    return false;
}

bool DatabaseManager::createInfoTable() {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE information"
                         "(version real primary key, "
                         "name varchar(50))");
    }
    return ret;
}

bool DatabaseManager::updateInfoTable(double version) {

    bool ret = false;
    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE information SET version = %1;").arg(version));
    }
    return ret;
}

bool DatabaseManager::createChestTable() {

    // Create table "chest"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE chest"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertChestExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into chest values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createShouldersTable() {

    // Create table shoulders
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE shoulders"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertShouldersExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO shoulders VALUES(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createAbsTable() {

    // Create table abs
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE abs"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertAbsEcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into abs values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createBicepsTable() {

    // Create table biceps
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE biceps"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertBicepsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into biceps values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createForearmsTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE forearms"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertForearmsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into forearms values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createQuadsTable() {

    // Create table quads
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE quads"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertQuadsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into quads values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createCalvesTable() {

    // Create table calves
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE calves"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertCalvesExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into calves values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createTrapeziusTable() {

    // Create table trapezius
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE trapezius"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertTrapeziusExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into trapezius values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createLatsTable() {

    // Create table lats
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE lats"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertLatsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into lats values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createTricepsTable() {

    // Create table triceps
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE triceps"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertTricepsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into triceps values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createGlutesTable() {

    // Create table glutes
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE glutes"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertGlutesExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into glutes values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::createHamstringsTable() {

    // Create table hamstrings
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE hamstrings"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "description varchar(160))");

    }
    return ret;
}

bool DatabaseManager::insertHamstringsExcercise(QString name, QString description) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into hamstrings values(NULL,'%1','%2')")
                         .arg(name).arg(description));

    }
    return ret;
}

bool DatabaseManager::insertWorkout(QString workoutname) {

    bool ret = false;

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-workout";

    if (db.isOpen()) {

        QSqlQuery query(db);
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

bool DatabaseManager::createWorkoutTable(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-workout";

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
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
                                 "weights6 real)").arg(tablename));
    }
    return ret;
}


bool DatabaseManager::createWorkoutNamesTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("CREATE TABLE workoutnames"
                                 "(id integer primary key, "
                                 "workoutname varchar(50), "
                                 "tablename varchar(50))"));

    }
    return ret;
}

bool DatabaseManager::insertWorkoutName(QString name) {

    QStringRef sub(&name, 0, 3);
    QString tablename = sub.toString() + "-workout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into workoutnames values(NULL,'%1','%2')")
                         .arg(name).arg(tablename));

    }
    return ret;
}

bool DatabaseManager::createPreviousWorkoutNamesTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("CREATE TABLE previousworkoutnames"
                                 "(id integer primary key, "
                                 "workoutname varchar(50), "
                                 "tablename varchar(50), "
                                 "date varchar(50))"));

    }
    return ret;
}

bool DatabaseManager::insertPreviousWorkoutName(QString name, QString date) {

    QStringRef sub(&name, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into previousworkoutnames values(NULL,'%1','%2','%3')")
                         .arg(name).arg(tablename).arg(date));

    }
    return ret;
}


bool DatabaseManager::createPreviousWorkoutsTable(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
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

bool DatabaseManager::insertPreviousWorkoutExcercise(QString workoutname) {

    QStringRef sub(&workoutname, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
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

bool DatabaseManager::createDB() {

    if(db.isOpen()) {

        //-----------------------------------------------------------------

        if(initializeInfoTable()) qDebug() << "information table created";

        //-----------------------------------------------------------------

        if(createShouldersTable() and
                createAbsTable() and
                createBicepsTable() and
                createForearmsTable() and
                createTricepsTable() and
                createTrapeziusTable() and
                createCalvesTable() and
                createGlutesTable() and
                createHamstringsTable() and
                createLatsTable() and
                createQuadsTable() and
                createChestTable() and
                createWorkoutTable("example") and
                createWorkoutNamesTable() and
                createPreviousWorkoutNamesTable() and
                createPreviousWorkoutsTable("chestday") and
                initializeInfoTable()) {

            qDebug() << "Tables created";
        }

        //-----------------------------------------------------------------

        if(insertChestExcercise("Bench Press","Raise the bar.")) {
            qDebug() << "Chest Excercise added.";
        } else {
            qDebug() << "Chest Excercise addition failed";
        }

        if(insertChestExcercise("Butterfly Machine","Push the handles together slowly as you squeeze your chest in the middle.")) {
            qDebug() << "Chest Excercise added.";
        } else {
            qDebug() << "Chest Excercise addition failed";
        }

        //-----------------------------------------------------------------

        if(insertTrapeziusExcercise("Deadlift","The deadlift is a weight training exercise where a loaded barbell is lifted off the ground from a stabilized, bent over position.")) {
            qDebug() << "Trapezius Excercise added.";
        } else {
            qDebug() << "Trapezius Excercise addition failed";
        }

        if(insertTrapeziusExcercise("Back Extension Machine","Extend your back slowly up and return to starting position.")) {
            qDebug() << "Trapezius Excercise added.";
        } else {
            qDebug() << "Trapezius Excercise addition failed";
        }

        //-----------------------------------------------------------------
        if(insertBicepsExcercise("Seated Arm Curl on Scott Bench","Lower weights slowly and lift them up.") and
                insertBicepsExcercise("Seated Dumbbel Curl","Sit on a flat bench with a dumbbel on each hand. Lift dumbbels up to your shoulder level and hold a second. Then Bring dumbbels back to starting position.")) {
            qDebug() << "Bicep Excercises added." ;
        } else {
            qDebug() << "Bicep Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertAbsEcercise("Ab Roll", "Roll slowly down with your back a little curved. Then roll back up and squeeze your abdominals at the same time.")) {
            qDebug() << "Ab Excercise added." ;
        } else {
            qDebug() << "Ab Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertShouldersExcercise("Shoulder Press","Press bar/dumbbels upward until arms are extended overhead. Return to upper chest and repeat.")) {
            qDebug() << "Shoulder Excercise added." ;
        } else {
            qDebug() << "Shoulder Excercise addition failed" ;
        }

        if(insertShouldersExcercise("Dumbbel Front Raise","Raise dumbbells forward and upward with until upper arms are above horizontal. Lower and repeat.")) {
            qDebug() << "Shoulder Excercise added." ;
        } else {
            qDebug() << "Shoulder Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertLatsExcercise("Barbell Incline Row","Pull shoulders back and push chest forward while arching back. Return until arms are extended, shoulders are stretched forward, and lower back is flexed forward. Repeat.")) {
            qDebug() << "Lats Excercise added." ;
        } else {
            qDebug() << "Lats Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertCalvesExcercise("Calf Raises","Raise heels by extending ankles as high as possible. Lower heels by bending ankles until calves are stretched. Repeat.")) {
            qDebug() << "Calves Excercise added." ;
        } else {
            qDebug() << "Calves Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertQuadsExcercise("Squat","Bend knees forward while allowing hips to bend back behind, keeping back straight and knees pointed same direction as feet. Descend until knees and hips are fully bent. Extend knees and hips until legs are straight. Return and repeat.")) {
            qDebug() << "Quads Excercise added." ;
        } else {
            qDebug() << "Quads Excercise addition failed" ;
        }

        if(insertQuadsExcercise("Leg Extension","Move lever forward and upward by extending knees until leg are straight. Return lever to original position by bending knees. Repeat.")) {
            qDebug() << "Quads Excercise added." ;
        } else {
            qDebug() << "Quads Excercise addition failed" ;
        }

        if(insertQuadsExcercise("Leg Press Machine","Push platform(s) away by extending knees and hips until knees are fully extended. Return until hips are completely flexed. Repeat.")) {
            qDebug() << "Quads Excercise added." ;
        } else {
            qDebug() << "Quads Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertForearmsExcercise("Barbell Roll","Roll barbell slowly down towards your fingertips and roll it back up.")) {
            qDebug() << "Forearms Excercise added." ;
        } else {
            qDebug() << "Forearms Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertHamstringsExcercise("Straight Leg Deadlift","With knees straight, lower bar toward top of feet by bending hips. After hips can no longer flex, bend waist as bar approaches top of feet. Lift bar by extending waist and hip until standing upright. Pull shoulders back slightly if rounded. Repeat.")) {
            qDebug() << "Hamstrings Excercise added." ;
        } else {
            qDebug() << "Hamstrings Excercise addition failed" ;
        }

        if(insertHamstringsExcercise("Seated Leg Curl","Pull lever to back of thighs by flexing knees. Return lever until knees are straight. Repeat.")) {
            qDebug() << "Hamstrings Excercise added." ;
        } else {
            qDebug() << "Hamstrings Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertTricepsExcercise("Dip","Lower body until slight stretch is felt in shoulders. Push body up until arms are straight. Repeat.")) {
            qDebug() << "Triceps Excercise added." ;
        } else {
            qDebug() << "Triceps Excercise addition failed" ;
        }

        if(insertTricepsExcercise("Pushdown","Extend arms down. Return until forearm is close to upper arm. Repeat.")) {
            qDebug() << "Triceps Excercise added." ;
        } else {
            qDebug() << "Triceps Excercise addition failed" ;
        }

        if(insertTricepsExcercise("Kneeling Triceps Extension","Extend forearms overhead until elbow are fully extended. Return and repeat.")) {
            qDebug() << "Triceps Excercise added." ;
        } else {
            qDebug() << "Triceps Excercise addition failed" ;
        }

        //-----------------------------------------------------------------

        if(insertGlutesExcercise("Lunge","Lunge forward with first leg. Land on heel then forefoot. Lower body by flexing knee and hip of front leg until knee of rear leg is almost in contact with floor. Return to original standing position by forcibly extending hip and knee of forward leg. Repeat by alternating lunge with opposite leg.")) {
            qDebug() << "Glutes Excercise added." ;
        } else {
            qDebug() << "Glutes Excercise addition failed" ;
        }

        //-----------------------------------------------------------------


        if(insertWorkout("example") and insertWorkoutName("example")) {
            qDebug() << "Workout and workoutname added" ;
        }

        if(insertPreviousWorkoutName("chestday","15.01.2014")) {
            qDebug() << "Previous workoutname added" ;
        }

        if(insertPreviousWorkoutExcercise("chestday") and
                insertPreviousWorkoutExcercise("chestday")) {
            qDebug() << "Previous workout added";
        }
    }

    return true;
}

bool DatabaseManager::createUserTable() {

    // Create table "user"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("create table user"
                         "(id integer primary key, "
                         "name varchar(50), "
                         "age integer, "
                         "gender varchar(10), "
                         "height real, "
                         "weight real)");


    }
    return ret;
}

bool DatabaseManager::insertUser(QString name, int age, QString gender, double height, double weight) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into user values(NULL,'%1',%2,'%3',%4,%5)")
                         .arg(name).arg(age).arg(gender).arg(height).arg(weight));

    }
    return ret;
}

// This function is used to update the database, upcoming changes are coming trough this.
bool DatabaseManager::updateDB() {

    //updateInfoTable(2.0);

    qDebug() << "Updating database...";

}

// returns all users from db
QMap<QString,QString> DatabaseManager::getUser() {

    bool ret = false;
    QString name;
    int age;
    QString gender;
    double height;
    double weight;

    QMap<QString,QString> temp;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("SELECT * FROM user;");

        if (query.isSelect()) {

            name = query.value(1).toString();
            temp.insert("name", name);

            age = query.value(2).toInt();
            temp.insert("age", age);

            gender = query.value(3).toString();
            temp.insert("gender", gender);

            height = query.value(4).toDouble();
            temp.insert("height", height);

            weight = query.value(5).toDouble();
            temp.insert("weight", weight);

//            calculateBMI();
//            calculateBMR();
        }
    }

    return temp;
}

bool DatabaseManager::updateName(QString name) {

}
