#include "user.h"
#include <QDebug>

User::User(QObject *parent, DatabaseManager* dbmanager) : QObject(parent) {
    mydbmanager = dbmanager;

    getUser();
}

User::~User() {
    qDebug() << "Destroying User..";
    clean();
}

QString User::getName() {
    qDebug() << myName;
    return myName;
}

void User::setName(QString name) {

    if(myName != name) {
        myName = name;
        updateName(name);
        emit nameChanged();
    }
}

int User::getAge() {
    qDebug() << myAge;
    return myAge;
}

void User::setAge(int age) {

    if(myAge != age) {
        myAge = age;
        updateAge(age);
        calculateBMR();
        emit ageChanged();
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
        emit genderChanged();
    }
}

double User::getHeight() {
    return myHeight;
}

void User::setHeight(double height) {

    if(myHeight != height) {
        myHeight = height;
        updateHeight(height);
        calculateBMI();
        calculateBMR();
        emit heightChanged();
    }
}

double User::getWeight() {
    return myWeight;
}

void User::setWeight(double weight) {

    if(myWeight != weight) {
        myWeight = weight;
        updateWeight(weight);
        calculateBMI();
        calculateBMR();
        emit weightChanged();
    }
}

bool User::getUser() {

    auto user = mydbmanager->getUser();

    qDebug() << user;

    myName = user["name"];
    myAge = user["age"].toInt();
    myGender = user["gender"];
    myHeight = user["height"].toDouble();
    myWeight = user["weight"].toDouble();

    calculateBMI();
    calculateBMR();

    return true;
}

bool User::insertUser(QString name, int age, QString gender, double height, double weight) {

    return mydbmanager->insertUser(name, age, gender, height, weight);
}



bool User::updateName(QString name) {

    return mydbmanager->updateName(name);
}

bool User::updateAge(int age) {

    return mydbmanager->updateAge(age);

}

bool User::updateGender(QString gender) {

    return mydbmanager->updateGender(gender);
}

bool User::updateHeight(double height) {

    return mydbmanager->updateHeight(height);
}

bool User::updateWeight(double weight) {

    return mydbmanager->updateWeight(weight);
}

void User::calculateBMI() {

    myBMI = myWeight / ((myHeight/100) * (myHeight / 100));
    myBMI = static_cast<double>(static_cast<int>(myBMI*100+0.5))/100.0;
    emit BMIChanged();

    if(myBMI < 15) {
        myBMIdescription = "Very severely underweight";
    } else if(myBMI >= 15.0 and myBMI < 16.0 ) {
        myBMIdescription = "Severely underweight";
    } else if(myBMI >= 16.0 and myBMI < 18.5) {
        myBMIdescription = "Underweight";
    } else if(myBMI >= 18.5 and myBMI < 25.0) {
        myBMIdescription = "Normal (healthy weight)";
    } else if(myBMI >= 25.0 and myBMI < 30.0) {
        myBMIdescription = "Overweight";
    } else if( myBMI >= 30 and myBMI < 35) {
        myBMIdescription = "Moderately obese";
    } else if(myBMI >= 35 and myBMI < 40) {
        myBMIdescription = "Severely obese";
    } else if(myBMI >= 40){
        myBMIdescription = "Very severely obese";
    }

    emit BMIdescriptionChanged();

}

double User::getBMI() {

    return myBMI;
}

QString User::getBMIdescription() {

    return myBMIdescription;
}

void User::clean() {

    myName.clear();
    myAge = 0;
    myGender.clear();
    myHeight = 0;
    myWeight = 0;
    myBMI = 0;
    myBMIdescription.clear();
    myBMR = 0;
}

void User::calculateBMR() {

    if(myGender == "Male") {
        myBMR = 66 + (13.8 * myWeight) + (5 * myHeight) - (6.8 * myAge);
    } else if(myGender == "Female") {
        myBMR = 655 + (9.6 * myWeight) + (1.8 * myHeight) - (4.7 * myAge);
    }
    emit BMRChanged();
}

double User::getBMR() {

    return myBMR;
}
