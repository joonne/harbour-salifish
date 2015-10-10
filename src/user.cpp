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

bool User::openDB() {

    // Find QSLite driver
    mydbmanager = QSqlDatabase::addDatabase("QSQLITE","userConnection");
    QString dbname = "userDatabase.db.sqlite";
    QString dbpath = QStandardPaths::writableLocation(QStandardPaths::DataLocation) + QDir::separator() + dbname;
    //QString dbpath = "/usr/share/harbour-salifish/databases/" + dbname;
    mydbmanager.setDatabaseName(dbpath);

    // Open databasee
    if(mydbmanager.open()) {
        QStringList tables = mydbmanager.tables();
        qDebug() << "Tables: " << tables;
        return true;
    } else {
        qDebug() << mydbmanager.lastError();
        return false;
    }
}

void User::closeDB() {
    mydbmanager.close();
}

QString User::getName() {
    return myName;
}

void User::setName(QString name) {

    if(myName != name) {
        myName = name;
        updateName(name);
    }
}

int User::getAge() {
    return myAge;
}

void User::setAge(int age) {

    if(myAge != age) {
        myAge = age;
        updateAge(age);
        calculateBMR();
    }
}

QString User::getGender() {
    return myGender;
}

void User::setGender(QString gender) {

    if(myGender != gender) {
        myGender = gender;
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

    QMap<QString, QString> user = mydbmanager.getUser();

    QMap<QString, QString>::iterator itr = user.first();
    while(itr != user.end()) {
        if(itr.key() == "name") {
            myName = itr.value();
        } else if(itr.key() == "age") {
            myAge = itr.value();
        } else if(itr.key() == "gender") {
            myGender = itr.value();
        } else if(itr.key() == "height") {
            myHeight = itr.value();
        } else if(itr.key() == "weight") {
            myWeight = itr.value();
        }

        ++itr;
    }

    calculateBMI();
    calculateBMR();
}

// Insert new user
bool User::insertUser(QString name, int age, QString gender, double height, double weight) {

    return mydbmanager.insertUser(name, age, gender, height, weight);
}



bool User::updateName(QString name) {

    bool ret = false;

    if (mydbmanager.isOpen()) {

        QSqlQuery query(mydbmanager);
        ret = query.exec(QString("UPDATE user SET name = '%1' WHERE Id = 1;").arg(name));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateAge(int age) {

    bool ret = false;

    if (mydbmanager.isOpen()) {

        QSqlQuery query(mydbmanager);
        ret = query.exec(QString("UPDATE user SET age = %1 WHERE Id = 1;").arg(age));
        qDebug() << query.lastError();
    }
    return ret;
}

bool User::updateGender(QString gender) {

    bool ret = false;

    if (mydbmanager.isOpen()) {

        QSqlQuery query(mydbmanager);
        ret = query.exec(QString("UPDATE user SET gender = '%1' WHERE Id = 1;").arg(gender));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateHeight(double height) {

    bool ret = false;

    if (mydbmanager.isOpen()) {

        QSqlQuery query(mydbmanager);
        ret = query.exec(QString("UPDATE user SET height = %1 WHERE Id = 1;").arg(height));
        qDebug() << query.lastError();
        ret = true;
    }
    return ret;
}

bool User::updateWeight(double weight) {

    bool ret = false;

    if (mydbmanager.isOpen()) {

        QSqlQuery query(mydbmanager);
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

    myName.clear();
    myAge = 0;
    myGender.clear();
    height_ = 0;
    weight_ = 0;
    BMI_ = 0;
    BMIdescription_.clear();
    BMR_ = 0;
    mydbmanager.close();

}

void User::calculateBMR() {

    if(myGender == "Male") {
        BMR_ = 66 + (13.8*weight_) + (5 * height_) - (6.8 * myAge);
    } else if(myGender == "Female") {
        BMR_ = 655 + (9.6 * weight_) + (1.8 * height_) - (4.7 * myAge);
    }
    emit BMRChanged();
}

double User::getBMR() {

    return BMR_;
}
