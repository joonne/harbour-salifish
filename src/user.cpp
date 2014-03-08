#include "user.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>

User::User(QObject *parent) : QObject(parent) {}

User::~User() {
    qDebug() << "Destroying User..";
    clean();
}

QString User::getName() {
    return name_;
}

void User::setName(QString name) {

    if(name_ != name) {
        name_ = name;
        updateName(name);
    }
}

int User::getAge() {
    return age_;
}

void User::setAge(int age) {

    if(age_ != age) {
        age_ = age;
        updateAge(age);
        calculateBMR();
    }
}

QString User::getGender() {
    return gender_;
}

void User::setGender(QString gender) {

    if(gender_ != gender) {
        gender_ = gender;
        updateGender(gender);
        calculateBMR();
    }
}

double User::getHeight() {
    return height_;
}

void User::setHeight(double height) {

    if(height_ != height) {
        height_ = height;
        updateHeight(height);
        calculateBMI();
        calculateBMR();
    }
}

double User::getWeight() {
    return weight_;
}

void User::setWeight(double weight) {

    if(weight_ != weight) {
        weight_ = weight;
        updateWeight(weight);
        calculateBMI();
        calculateBMR();
    }
}

bool User::getUser() {

    bool ret = false;

    if(db_.isOpen()) {

        qDebug() << "Tietokannan avaaminen onnistui.";

        QSqlQuery query(db_);
        if(!query.exec("SELECT * FROM user;")) {
            qDebug() << query.lastError();
        }

        if (query.first()) {

            qDebug() << "Kohdistettu lailliseen kenttaan";

            name_ = query.value(1).toString();
            age_ = query.value(2).toInt();
            gender_ = query.value(3).toString();
            height_ = query.value(4).toDouble();
            weight_ = query.value(5).toDouble();
            ret = true;

            calculateBMI();
            calculateBMR();
        }
    }

    return ret;
}

// Insert new user
bool User::insertUser(QString name, int age, QString gender, double height, double weight) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("insert into user values(NULL,'%1',%2,'%3',%4,%5)")
                         .arg(name).arg(age).arg(gender).arg(height).arg(weight));
    }
    return ret;
}

bool User::openDB() {

    // Find QSLite driver
    db_ = QSqlDatabase::addDatabase("QSQLITE","userConnection");
    //    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    //    db_.setDatabaseName(dbpath);
    db_.setDatabaseName("/home/nemo/qml/Sqlite/userDatabase.db.sqlite");

    // Open databasee
    if(db_.open()) {
        QStringList tables = db_.tables();
        qDebug() << "Tables: " << tables;
        return true;
    } else {
        qDebug() << db_.lastError();
        return false;
    }
}

void User::closeDB() {
    db_.close();
}

bool User::updateName(QString name) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("UPDATE user SET name = '%1' WHERE Id = 1;").arg(name));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateAge(int age) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("UPDATE user SET age = %1 WHERE Id = 1;").arg(age));
        qDebug() << query.lastError();
    }
    return ret;
}

bool User::updateGender(QString gender) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("UPDATE user SET gender = '%1' WHERE Id = 1;").arg(gender));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateHeight(double height) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("UPDATE user SET height = %1 WHERE Id = 1;").arg(height));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateWeight(double weight) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("UPDATE user SET weight = %1 WHERE Id = 1;").arg(weight));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

void User::calculateBMI() {

    BMI_ = weight_ / ((height_/100) * (height_ / 100));
    BMI_ = static_cast<double>(static_cast<int>(BMI_*100+0.5))/100.0;
    emit BMIChanged();

    if(BMI_ < 15) {
        BMIdescription_ = "Very severely underweight";
    } else if(BMI_ >= 15.0 and BMI_ < 16.0 ) {
        BMIdescription_ = "Severely underweight";
    } else if(BMI_ >= 16.0 and BMI_ < 18.5) {
        BMIdescription_ = "Underweight";
    } else if(BMI_ >= 18.5 and BMI_ < 25.0) {
        BMIdescription_ = "Normal (healthy weight)";
    } else if(BMI_ >= 25.0 and BMI_ < 30.0) {
        BMIdescription_ = "Overweight";
    } else if( BMI_ >= 30 and BMI_ < 35) {
        BMIdescription_ = "Moderately obese";
    } else if(BMI_ >= 35 and BMI_ < 40) {
        BMIdescription_ = "Severely obese";
    } else if(BMI_ >= 40){
        BMIdescription_ = "Very severely obese";
    }

    emit BMIdescriptionChanged();

}

double User::getBMI() {

    return BMI_;
}

QString User::getBMIdescription() {

    return BMIdescription_;
}

void User::clean() {

    name_.clear();
    age_ = 0;
    gender_.clear();
    height_ = 0;
    weight_ = 0;
    BMI_ = 0;
    BMIdescription_.clear();
    BMR_ = 0;
    db_.close();

}

void User::calculateBMR() {

    if(gender_ == "Male") {
        BMR_ = 66 + (13.8*weight_) + (5 * height_) - (6.8 * age_);
    } else if(gender_ == "Female") {
        BMR_ = 655 + (9.6 * weight_) + (1.8 * height_) - (4.7 * age_);
    }
    emit BMRChanged();
}

double User::getBMR() {

    return BMR_;
}
