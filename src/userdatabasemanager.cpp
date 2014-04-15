#include "userdatabasemanager.h"

UserDatabase::UserDatabase(QObject *parent) :
    QObject(parent)
{
    setUpDB();
    close();
}

UserDatabase::~UserDatabase() {

    qDebug() << "Destroying userdbmanager..";
    deleteDB();

}

bool UserDatabase::openDB() {

    QString dbname = "userDatabase.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    //QString dbpath = "/usr/share/harbour-gymtracker/databases/" + dbname;
    QDir path(QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname);

    if(!path.exists()) {

        path.mkpath(dbpath);

    } else {

        // Find SQLite driver
        db = QSqlDatabase::addDatabase("QSQLITE","userdbmanager");
        db.setDatabaseName(dbpath);

    }

    // Open database
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
    QString dbname = "userDatabase.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    return QFile::remove(dbpath);}

void UserDatabase::close() {
    db.close();
}

void UserDatabase::setUpDB() {

    if(openDB()) {

        QSqlQuery query(db);
        query.exec("SELECT count(*) FROM sqlite_master WHERE type = 'table';");
        int tableCount = query.value(0).toInt();
        qDebug() << "Tables in userdatabase: " << tableCount;

        if(tableCount == 0) {

            createDB();

        }
    }

    close();

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

bool UserDatabase::createDB() {

    if(createUserTable()) {
        insertUser("Jonne Pihlanen",23,"male",177,77);
    }
}
