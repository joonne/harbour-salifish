#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{}

DatabaseManager::~DatabaseManager()
{
    db.close();
}

void DatabaseManager::setUpDB()
{
    if(openDB()) {

        // check whether db is empty, if it is, create db
        if(db.tables().size() == 0) {

            createDB();

            emit initDbWithData();

        } else {

            QSqlQuery query(db);
            query.exec("SELECT name, version FROM information;");
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

bool DatabaseManager::openDB()
{
    QString dbname = "salifish.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));

    if(!dir.exists()) {
        dir.mkpath(".");
    }

    // find SQLite driver
    db = QSqlDatabase::addDatabase("QSQLITE", "databasemanager");
    db.setDatabaseName(dbpath);

    // open databasee
    return db.open();
}

QSqlError DatabaseManager::lastError()
{
    return db.lastError();
}

bool DatabaseManager::deleteDB()
{
    db.close();

    QString dbname = "salifish.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    return QFile::remove(dbpath);
}

void DatabaseManager::close()
{
    db.close();
}

bool DatabaseManager::initializeInfoTable()
{
    bool ret = createInfoTable();

    if (ret) {

        QSqlQuery query(db);
        return query.exec(QString("INSERT INTO information VALUES(%1,'%2')")
                          .arg(1.0).arg("SaliFish"));
    }

    return false;
}

bool DatabaseManager::createInfoTable()
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE information"
                         "(id INTEGER PRIMARY KEY, "
                         "version REAL, "
                         "name varchar(50))");
    }

    return ret;
}

bool DatabaseManager::updateInfoTable(double version)
{
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE information SET version = %1;").arg(version));
    }

    return ret;
}

bool DatabaseManager::createCategoryTable()
{
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE category"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50))");
    }

    return ret;
}

bool DatabaseManager::insertCategories(QList<QVariantMap> categories)
{
    db.transaction();

    for (auto category: categories) {

        auto id = category.value("id").toInt();
        auto name = category.value("name").toString();

        insertCategory(id, name);
    }

    return db.commit();
}

bool DatabaseManager::insertCategory(int id, QString name)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT OR REPLACE INTO category VALUES(%0,'%1')").arg(id).arg(name));
        qDebug() << query.lastError();
    }

    return ret;
}

int DatabaseManager::findCategory(QString category)
{
    int categoryId = 0;

    if (db.isOpen()) {
        QSqlQuery query(db);
        query.exec(QString("SELECT id FROM category WHERE name = '%1'").arg(category));
        qDebug() << query.lastError();

        if (query.isSelect()) {
            while (query.next()) {
                categoryId = query.value(0).toInt();
            }
        }
    }

    return categoryId;
}

bool DatabaseManager::createExerciseTable()
{
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE exercise"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50), "
                         "description VARCHAR(160), "
                         "category INTEGER, "
                         "FOREIGN KEY(category) REFERENCES category(id))");
        qDebug() << query.lastError();

    }

    return ret;
}

bool DatabaseManager::insertExercises(QList<QVariantMap> exercises)
{
    db.transaction();

    for (auto exercise : exercises) {
        auto id = exercise.value("id").toInt();
        auto name = exercise.value("name").toString();
        name.replace("'", "''");
        auto description = exercise.value("description").toString();
        auto category = exercise.value("category").toInt();

        insertExercise(id, name, description, category);
    }

    return db.commit();
}

bool DatabaseManager::insertExercise(int id, QString name, QString description, int category)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT OR REPLACE INTO exercise values(%0, '%1', '%2', %3)")
                         .arg(id).arg(name).arg(description).arg(category));
        qDebug() << query.lastError();

    }

    return ret;
}

bool DatabaseManager::createExerciseMuscleTable()
{
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE exerciseMuscle"
                         "(id INTEGER PRIMARY KEY, "
                         "muscle INTEGER, "
                         "exercise INTEGER, "
                         "FOREIGN KEY(muscle) REFERENCES muscle(id), "
                         "FOREIGN KEY(exercise) REFERENCES exercise(id))");
        qDebug() << query.lastError();

    }

    return ret;
}

bool DatabaseManager::insertExerciseMuscle(int muscle, int exercise)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO exerciseMuscle values(NULL, %1, %2)")
                         .arg(muscle).arg(exercise));

    }

    return ret;
}

bool DatabaseManager::createMuscleTable()
{
    bool ret = false;

    if(db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE muscle"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(50), "
                         "is_front INTEGER DEFAULT 0)");

        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::insertMuscles(QList<QVariantMap> muscles)
{
    db.transaction();

    for (auto muscle : muscles) {
        auto id = muscle.value("id").toInt();
        auto name = muscle.value("name").toString();
        auto isFront = muscle.value("is_front").toInt();

        insertMuscle(id, name, isFront);
    }

    return db.commit();
}

bool DatabaseManager::insertMuscle(int id, QString name, int is_front)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT OR REPLACE INTO muscle VALUES(%0, '%1', %2)").arg(id).arg(name).arg(is_front));
        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::createWorkoutTable()
{
    bool ret = false;
    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE workout"
                         "(id INTEGER PRIMARY KEY, "
                         "name VARCHAR(160), "
                         "calories REAL, "
                         "isTemplate INTEGER DEFAULT 0)");

        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::insertWorkout(QString name, double calories, int isTemplate)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO workout VALUES(NULL,'%1', %2").arg(name).arg(calories).arg(isTemplate));

    }

    return ret;
}

bool DatabaseManager::createWorkoutEntryTable()
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec("CREATE TABLE workoutEntry"
                         "(id INTEGER PRIMARY KEY, "
                         "exercise INTEGER, "
                         "user INTEGER, "
                         "workout INTEGER, "
                         "date VARCHAR(15), "
                         "repeats INTEGER, "
                         "weights REAL, "
                         "equipment INTEGER, "
                         "FOREIGN KEY(exercise) REFERENCES exercise(id), "
                         "FOREIGN KEY(user) REFERENCES user(id), "
                         "FOREIGN KEY(workout) REFERENCES workout(id), "
                         "FOREIGN KEY(equipment) REFERENCES equipment(id))");

        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::insertWorkoutEntry(int exercise, int user, int workout, QString date, int repeats, double weights, int equipment)
{
    bool ret = false;

    if (db.isOpen()) {
        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO workoutEntry VALUES(NULL, %1, %2, %3, '%4', %5, %6, %7)")
                         .arg(exercise)
                         .arg(user)
                         .arg(workout)
                         .arg(date)
                         .arg(repeats)
                         .arg(weights)
                         .arg(equipment));
    }

    return ret;
}

bool DatabaseManager::createEquipmentTable()
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        query.exec("CREATE TABLE equipment"
                   "(id INTEGER PRIMARY KEY, "
                   "name VARCHAR(50))");

        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::insertEquipment(QString name)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT INTO equipment VALUES(NULL, '%1')").arg(name));
    }

    return ret;
}



bool DatabaseManager::createDB()
{
    if (db.isOpen()) {

        //-----------------------------------------------------------------

        if(initializeInfoTable()) {
            qDebug() << "information table created";
        }

        //-----------------------------------------------------------------

        if(createCategoryTable() &&
                createExerciseTable() &&
                createMuscleTable() &&
                createExerciseMuscleTable() &&
                createWorkoutTable() &&
                createWorkoutEntryTable() &&
                createEquipmentTable()) {
            qDebug() << "Tables created";
        }

        //-----------------------------------------------------------------

        if(createUserTable() && insertUser("Sali Fish", 25, "Male", 180, 85)) {
            qDebug() << "User table created";
        }

        //-----------------------------------------------------------------

//        if(insertCategory(10, "Abs") && insertCategory(8, "Arms") &&
//                insertCategory(12, "Back") && insertCategory(14, "Calves") &&
//                insertCategory(11, "Chest") && insertCategory(9, "Legs") &&
//                insertCategory(13, "Shoulders")) {

//            qDebug() << "Categories added";
//        }
    }

    return true;
}

bool DatabaseManager::createUserTable()
{
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

        qDebug() << query.lastError();
    }

    qDebug() << db.lastError();
    return ret;
}

bool DatabaseManager::insertUser(QString name, int age, QString gender, double height, double weight)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("INSERT OR REPLACE INTO user VALUES(1,'%1',%2,'%3', %4, %5);").arg(name).arg(age).arg(gender).arg(height).arg(weight));
    }

    return ret;
}

bool DatabaseManager::updateDB() { return false; }

QMap<QString,QString> DatabaseManager::getUser()
{
    QString name;
    QString age;
    QString gender;
    QString height;
    QString weight;

    QMap<QString,QString> temp;

    if (db.isOpen()) {

        QSqlQuery query(db);
        query.exec("SELECT * FROM user WHERE id = 1;");

        if (query.isSelect()) {
            while(query.next()) {

                qDebug() << query.value(0);

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

        qDebug() << query.lastError();
        qDebug() << db.lastError();
    }

    return temp;
}

bool DatabaseManager::updateName(QString name)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET name = '%1' WHERE id = 1;").arg(name));
        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::updateAge(int age)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET age = %1 WHERE id = 1;").arg(age));
        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::updateGender(QString gender)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET gender = '%1' WHERE id = 1;").arg(gender));
        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::updateHeight(double height)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET height = %1 WHERE id = 1;").arg(height));
        qDebug() << query.lastError();
    }

    return ret;
}

bool DatabaseManager::updateWeight(double weight)
{
    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("UPDATE user SET weight = %1 WHERE id = 1;").arg(weight));
        qDebug() << query.lastError();
    }

    return ret;
}

QList<QMap<QString, QString> > DatabaseManager::getExercises(QString category)
{
    QList<QMap<QString, QString> > exercises;

    if (db.isOpen()) {

        QSqlQuery query(db);
        query.exec(QString("SELECT exercise.id, exercise.name, exercise.description, category.name "
                           "FROM exercise "
                           "INNER JOIN category "
                           "ON exercise.category = category.id AND category.name = '%1' "
                           "ORDER BY exercise.name;").arg(category));

        qDebug() << query.lastError();
        qDebug() << query.lastQuery();

        if (query.isSelect()) {
            while (query.next()) {
                QMap<QString,QString> temp;
                temp.insert("id", query.value(0).toString());
                temp.insert("name", query.value(1).toString());
                temp.insert("description", query.value(2).toString());
                temp.insert("category", query.value(3).toString());
                exercises.append(temp);
            }
        }
    }

    qDebug() << exercises;
    return exercises;
}

QList<QMap<QString, QString> > DatabaseManager::getCategories()
{
    QList<QMap<QString, QString> > categories;

    if (db.isOpen()) {

        QSqlQuery query(db);
        query.exec(QString("SELECT * FROM category ORDER BY name;"));

        if(query.isSelect()) {
            while(query.next()) {
                QMap<QString,QString> temp;
                temp.insert("id", query.value(0).toString());
                temp.insert("name", query.value(1).toString());
                categories.append(temp);
            }
        }
    }

    return categories;
}

QList<QMap<QString, QString> > DatabaseManager::getMuscles()
{
    QList<QMap<QString, QString> > muscles;

    if (db.isOpen()) {

        QSqlQuery query(db);
        query.exec(QString("SELECT * FROM muscle ORDER BY name;"));

        if (query.isSelect()) {
            while (query.next()) {
                QMap<QString,QString> temp;
                temp.insert("id", query.value(0).toString());
                temp.insert("name", query.value(1).toString());
                temp.insert("is_front", query.value(2).toString());
                muscles.append(temp);
            }
        }
    }

    return muscles;
}
