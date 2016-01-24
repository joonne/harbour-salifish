#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Creating dbmanager...";
}

DatabaseManager::~DatabaseManager() {

    qDebug() << "Destroying dbmanager...";
    db.close();
}

void DatabaseManager::setUpDB() {

    if(openDB()) {

        // check whether db is empty, if it is, create db
        if(db.tables().size() == 0) {

            createDB();

        } else {

            QSqlQuery query(db);
            query.exec("SELECT name,version FROM information;");
            if(query.isSelect()) {
                while(query.next()) {
                    QString name = query.value(0).toString();
                    double version = query.value(1).toDouble();
                    qDebug() << "App name: " << name;
                    qDebug() << "Database version : " << version;

                }
            }
        }
    }
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
                         "(id INTEGER PRIMARY KEY, "
                         "version REAL, "
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

bool DatabaseManager::createCategoryTable() {

    // Create table "category"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE category"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50))");

    }
    return ret;
}

bool DatabaseManager::insertCategory(int id, QString name) {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO category VALUES(%0,'%1')").arg(id).arg(name));
    }
    return ret;
}

int DatabaseManager::findCategory(QString category) {

    int categoryId = 0;

    if(db.isOpen()) {
        QSqlQuery query(db);
        query.exec(QString("SELECT id FROM category WHERE name = '%1'").arg(category));
        qDebug() << query.lastError();

        if(query.isSelect()) {
            while(query.next()) {
                categoryId = query.value(0).toInt();
            }
        }
    }

    return categoryId;
}

bool DatabaseManager::createExcerciseTable() {

    // Create table "excercise"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE excercise"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50), "
                         "description VARCHAR(160), "
                         "category INTEGER, "
                         "FOREIGN KEY(category) REFERENCES category(id))");
        qDebug() << query.lastError();

    }
    return ret;
}

bool DatabaseManager::insertExcercise(int id, QString name, QString description, int category) {

    bool ret = false;

    db.transaction();

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT OR REPLACE INTO excercise values(%0,'%1','%2',%3)")
                         .arg(id).arg(name).arg(description).arg(category));

    }

    db.commit();

    return ret;
}

bool DatabaseManager::createExcerciseMuscleTable() {

    // Create table "excerciseMuscle"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE excerciseMuscle"
                         "(id INTEGER PRIMARY KEY, "
                         "muscle INTEGER, "
                         "excercise INTEGER, "
                         "FOREIGN KEY(muscle) REFERENCES muscle(id), "
                         "FOREIGN KEY(excercise) REFERENCES excercise(id))");
        qDebug() << query.lastError();

    }
    return ret;
}

bool DatabaseManager::insertExcerciseMuscle(int muscle, int excercise) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO excerciseMuscle values(NULL, %1, %2)")
                         .arg(muscle).arg(excercise));

    }
    return ret;
}

bool DatabaseManager::createMuscleTable() {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE muscle"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50))");
    }

    return ret;
}

bool DatabaseManager::insertMuscle(QString name) {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO muscle VALUES(NULL, '%1')").arg(name));
    }
    return ret;
}

bool DatabaseManager::createWorkoutTable() {

    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE workout"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(160), "
                         "calories REAL)");
    }
    return ret;
}

bool DatabaseManager::insertWorkout(QString name, double calories) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO workout VALUES(NULL,'%1'").arg(name).arg(calories));

    }
    return ret;
}

bool DatabaseManager::createWorkoutEntryTable() {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE workoutEntry"
                         "(id INTEGER PRIMARY KEY, "
                         "excercise INTEGER, "
                         "user INTEGER, "
                         "workout INTEGER, "
                         "date VARCHAR(15), "
                         "repeats INTEGER, "
                         "weights REAL, "
                         "equipment INTEGER, "
                         "FOREIGN KEY(excercise) REFERENCES excercise(id), "
                         "FOREIGN KEY(user) REFERENCES user(id), "
                         "FOREIGN KEY(workout) REFERENCES workout(id), "
                         "FOREIGN KEY(equipment) REFERENCES equipment(id))");
    }
    return ret;
}

bool DatabaseManager::insertWorkoutEntry(int excercise,
                                         int user,
                                         int workout,
                                         QString date,
                                         int repeats,
                                         double weights,
                                         int equipment) {

    bool ret = false;

    if(db.isOpen()) {
        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO workoutEntry VALUES(NULL, %1, %2, %3, '%4', %5, %6, %7)")
                         .arg(excercise)
                         .arg(user)
                         .arg(workout)
                         .arg(date)
                         .arg(repeats)
                         .arg(weights)
                         .arg(equipment));
    }
    return ret;
}

bool DatabaseManager::createEquipmentTable() {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        query.exec("CREATE TABLE equipment"
                   "(id INTEGER PRIMARY KEY, "
                   "name VARCHAR(50))");
    }
    return ret;
}

bool DatabaseManager::insertEquipment(QString name) {

    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        query.exec(QString("INSERT INTO equipment VALUES(NULL, '%1')").arg(name));
    }
    return ret;
}



bool DatabaseManager::createDB() {

    if(db.isOpen()) {

        //-----------------------------------------------------------------

        if(initializeInfoTable()) qDebug() << "information table created";

        //-----------------------------------------------------------------

        if(createCategoryTable() && createExcerciseTable() && createMuscleTable() && createExcerciseMuscleTable() && createWorkoutTable() && createWorkoutEntryTable() && createEquipmentTable()) {
            qDebug() << "Tables created";
        }

        //-----------------------------------------------------------------


//        if(insertCategory("chest") && insertCategory("shoulders") &&
//                insertCategory("abs") && insertCategory("biceps") &&
//                insertCategory("forearms") && insertCategory("quads") &&
//                insertCategory("calves") && insertCategory("trapezius") &&
//                insertCategory("lats") && insertCategory("triceps") &&
//                insertCategory("glutes") && insertCategory("hamstrings")) {
//            qDebug() << "Categories added";
//        }

        if(insertCategory(10, "Abs") && insertCategory(8, "Arms") &&
                insertCategory(12, "Back") && insertCategory(14, "Calves") &&
                insertCategory(11, "Chest") && insertCategory(9, "Legs") &&
                insertCategory(13, "Shoulders")) {

            qDebug() << "Categories added";
        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Bench Press", "Raise the bar.", "chest")) {
//            qDebug() << "Chest Excercise added.";
//        } else {
//            qDebug() << "Chest Excercise addition failed";
//        }

//        if(insertExcercise("Butterfly Machine", "Push the handles together slowly as you squeeze your chest in the middle.", "chest")) {
//            qDebug() << "Chest Excercise added.";
//        } else {
//            qDebug() << "Chest Excercise addition failed";
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Deadlift", "The deadlift is a weight training exercise where a loaded barbell is lifted off the ground from a stabilized, bent over position.", "trapezius")) {
//            qDebug() << "Trapezius Excercise added.";
//        } else {
//            qDebug() << "Trapezius Excercise addition failed";
//        }

//        if(insertExcercise("Back Extension Machine","Extend your back slowly up and return to starting position.", "trapezius")) {
//            qDebug() << "Trapezius Excercise added.";
//        } else {
//            qDebug() << "Trapezius Excercise addition failed";
//        }

//        //-----------------------------------------------------------------
//        if(insertExcercise("Seated Arm Curl on Scott Bench","Lower weights slowly and lift them up.", "biceps") &&
//                insertExcercise("Seated Dumbbel Curl","Sit on a flat bench with a dumbbel on each hand. Lift dumbbels up to your shoulder level and hold a second. Then Bring dumbbels back to starting position.", "biceps")) {
//            qDebug() << "Bicep Excercises added." ;
//        } else {
//            qDebug() << "Bicep Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Ab Roll", "Roll slowly down with your back a little curved. Then roll back up and squeeze your abdominals at the same time.", "abs")) {
//            qDebug() << "Ab Excercise added." ;
//        } else {
//            qDebug() << "Ab Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Shoulder Press","Press bar/dumbbels upward until arms are extended overhead. Return to upper chest and repeat.", "shoulders")) {
//            qDebug() << "Shoulder Excercise added." ;
//        } else {
//            qDebug() << "Shoulder Excercise addition failed" ;
//        }

//        if(insertExcercise("Dumbbel Front Raise","Raise dumbbells forward and upward with until upper arms are above horizontal. Lower and repeat.", "shoulders")) {
//            qDebug() << "Shoulder Excercise added." ;
//        } else {
//            qDebug() << "Shoulder Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Barbell Incline Row","Pull shoulders back and push chest forward while arching back. Return until arms are extended, shoulders are stretched forward, and lower back is flexed forward. Repeat.", "lats")) {
//            qDebug() << "Lats Excercise added." ;
//        } else {
//            qDebug() << "Lats Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Calf Raises","Raise heels by extending ankles as high as possible. Lower heels by bending ankles until calves are stretched. Repeat.", "calves")) {
//            qDebug() << "Calves Excercise added." ;
//        } else {
//            qDebug() << "Calves Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Squat","Bend knees forward while allowing hips to bend back behind, keeping back straight and knees pointed same direction as feet. Descend until knees and hips are fully bent. Extend knees and hips until legs are straight. Return and repeat.", "quads")) {
//            qDebug() << "Quads Excercise added." ;
//        } else {
//            qDebug() << "Quads Excercise addition failed" ;
//        }

//        if(insertExcercise("Leg Extension","Move lever forward and upward by extending knees until leg are straight. Return lever to original position by bending knees. Repeat.", "quads")) {
//            qDebug() << "Quads Excercise added." ;
//        } else {
//            qDebug() << "Quads Excercise addition failed" ;
//        }

//        if(insertExcercise("Leg Press Machine","Push platform(s) away by extending knees and hips until knees are fully extended. Return until hips are completely flexed. Repeat.", "quads")) {
//            qDebug() << "Quads Excercise added." ;
//        } else {
//            qDebug() << "Quads Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Barbell Roll","Roll barbell slowly down towards your fingertips and roll it back up.", "forearms")) {
//            qDebug() << "Forearms Excercise added." ;
//        } else {
//            qDebug() << "Forearms Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Straight Leg Deadlift","With knees straight, lower bar toward top of feet by bending hips. After hips can no longer flex, bend waist as bar approaches top of feet. Lift bar by extending waist and hip until standing upright. Pull shoulders back slightly if rounded. Repeat.", "hamstrings")) {
//            qDebug() << "Hamstrings Excercise added." ;
//        } else {
//            qDebug() << "Hamstrings Excercise addition failed" ;
//        }

//        if(insertExcercise("Seated Leg Curl","Pull lever to back of thighs by flexing knees. Return lever until knees are straight. Repeat.", "hamstrings")) {
//            qDebug() << "Hamstrings Excercise added." ;
//        } else {
//            qDebug() << "Hamstrings Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Dip","Lower body until slight stretch is felt in shoulders. Push body up until arms are straight. Repeat.", "triceps")) {
//            qDebug() << "Triceps Excercise added." ;
//        } else {
//            qDebug() << "Triceps Excercise addition failed" ;
//        }

//        if(insertExcercise("Pushdown","Extend arms down. Return until forearm is close to upper arm. Repeat.", "triceps")) {
//            qDebug() << "Triceps Excercise added." ;
//        } else {
//            qDebug() << "Triceps Excercise addition failed" ;
//        }

//        if(insertExcercise("Kneeling Triceps Extension","Extend forearms overhead until elbow are fully extended. Return and repeat.", "triceps")) {
//            qDebug() << "Triceps Excercise added." ;
//        } else {
//            qDebug() << "Triceps Excercise addition failed" ;
//        }

//        //-----------------------------------------------------------------

//        if(insertExcercise("Lunge","Lunge forward with first leg. Land on heel then forefoot. Lower body by flexing knee and hip of front leg until knee of rear leg is almost in contact with floor. Return to original standing position by forcibly extending hip and knee of forward leg. Repeat by alternating lunge with opposite leg.", "glutes")) {
//            qDebug() << "Glutes Excercise added." ;
//        } else {
//            qDebug() << "Glutes Excercise addition failed" ;
//        }
    }

    return true;
}

bool DatabaseManager::createUserTable() {

    // Create table "user"
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE user"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50), "
                         "age INTEGER, "
                         "gender VARCHAR(1), "
                         "height REAL, "
                         "weight REAL)");


    }
    return ret;
}

bool DatabaseManager::insertUser(QString name, int age, QString gender, double height, double weight) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO user VALUES(NULL,'%1',%2,'%3',%4,%5)")
                         .arg(name).arg(age).arg(gender).arg(height).arg(weight));

    }
    return ret;
}

// This function is used to update the database, upcoming changes are coming trough this.
bool DatabaseManager::updateDB() {

    //updateInfoTable(2.0);

    qDebug() << "Updating database...";
    return true;

}

// returns all users from db
QMap<QString,QString> DatabaseManager::getUser() {

    QString name;
    QString age;
    QString gender;
    QString height;
    QString weight;

    QMap<QString,QString> temp;

    if(db.isOpen()) {

        QSqlQuery query(db);
        query.exec("SELECT * FROM user;");

        if (query.isSelect()) {

            name = query.value(1).toString();
            temp.insert("name", name);

            age = query.value(2).toString();
            temp.insert("age", age);

            gender = query.value(3).toString();
            temp.insert("gender", gender);

            height = query.value(4).toString();
            temp.insert("height", height);

            weight = query.value(5).toString();
            temp.insert("weight", weight);
        }
    }

    return temp;
}

bool DatabaseManager::updateName(QString name) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET name = '%1' WHERE Id = 1;").arg(name));
        qDebug() << query.lastError();
    }
    return ret;
}

bool DatabaseManager::updateAge(int age) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET age = %1 WHERE Id = 1;").arg(age));
        qDebug() << query.lastError();
    }
    return ret;
}

bool DatabaseManager::updateGender(QString gender) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET gender = '%1' WHERE Id = 1;").arg(gender));
        qDebug() << query.lastError();
    }
    return ret;
}

bool DatabaseManager::updateHeight(double height) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET height = %1 WHERE Id = 1;").arg(height));
        qDebug() << query.lastError();
    }
    return ret;
}

bool DatabaseManager::updateWeight(double weight) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET weight = %1 WHERE Id = 1;").arg(weight));
        qDebug() << query.lastError();
    }
    return ret;
}

QList<QMap<QString, QString> > DatabaseManager::getExcercises(QString category) {

    int categoryId = findCategory(category);
    QList<QMap<QString, QString> > excercises;

    if(db.isOpen()) {

        QSqlQuery query(db);
        query.exec(QString("SELECT * FROM excercise WHERE category = %0;").arg(categoryId));
        qDebug() << query.lastError();
        qDebug() << query.lastQuery();

        if(query.isSelect()) {
            while(query.next()) {
                QMap<QString,QString> temp;
                temp.insert("id", query.value(0).toString());
                temp.insert("name", query.value(1).toString());
                temp.insert("description", query.value(2).toString());
                temp.insert("category", query.value(3).toString());
                excercises.append(temp);
            }
        }
    }
    qDebug() << excercises;
    return excercises;
}
