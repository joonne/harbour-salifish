#include "userdatabasemanager.h"

UserDatabase::UserDatabase(QObject *parent) :
    QObject(parent)
{
}

UserDatabase::~UserDatabase() {}

bool UserDatabase::openDB() {

    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    dbpath = dbpath + "/gymDatabase.db.sqlite";
    db.setDatabaseName(dbpath);

    // Open databasee
    return db.open();
}

QSqlError UserDatabase::lastError() {

    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool UserDatabase::deleteDB() {

    // Close database
    db.close();

    // Remove created database binary file
    return QFile::remove("userDatabase.db.sqlite");
}

void UserDatabase::close() {
    db.close();
}

bool UserDatabase::createUserTable() {

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

bool UserDatabase::insertUser(QString name, int age, QString gender, double height, double weight) {

    bool ret = false;

    if (db.isOpen()) {

        QSqlQuery query(db);
        ret = query.exec(QString("insert into user values(NULL,'%1',%2,'%3',%4,%5)")
                         .arg(name).arg(age).arg(gender).arg(height).arg(weight));

    }
    return ret;
}
