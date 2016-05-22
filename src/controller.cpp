#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    mydbmanager = new DatabaseManager(this);
    mydbmanager->setUpDB();

    myExcerciseModel = new ExcerciseModel(this, mydbmanager);
    myWorkoutModel = new WorkoutModel(this, mydbmanager);
    myapireader = new APIReader(this, mydbmanager);
    myUser = new User(this, mydbmanager);
}

ExcerciseModel* Controller::getExcerciseModel() {
    return myExcerciseModel;
}

WorkoutModel* Controller::getWorkoutModel() {
    return myWorkoutModel;
}

User* Controller::getUser() {
    return myUser;
}

QVariantList Controller::getMuscleModel() {
    QVariantList temp;
    auto muscles = mydbmanager->getMuscles();

    foreach (auto muscle, muscles) {
        QVariantMap muscleMap;
        QMap<QString, QString>::const_iterator itr = muscle.constBegin();
        while (itr != muscle.constEnd()) {
            muscleMap.insert(itr.key(), QVariant(itr.value()));
            ++itr;
        }
        temp.append(muscleMap);
    }

    return temp;
}

QVariantList Controller::getCategoryModel() {

    QVariantList temp;
    auto categories = mydbmanager->getCategories();

    foreach (auto category, categories) {
        QVariantMap categoryMap;
        QMap<QString, QString>::const_iterator itr = category.constBegin();
        while (itr != category.constEnd()) {
            categoryMap.insert(itr.key(), QVariant(itr.value()));
            ++itr;
        }
        temp.append(categoryMap);
    }
    return temp;
}
