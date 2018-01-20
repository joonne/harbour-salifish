#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    mydbmanager = new DatabaseManager(this);
    mydbmanager->setUpDB();

    myExerciseModel = new ExerciseModel(this, mydbmanager);
    myWorkoutModel = new WorkoutModel(this, mydbmanager);
    myapireader = new APIReader(this, mydbmanager);
    myUser = new User(this, mydbmanager);
}

ExerciseModel* Controller::getExerciseModel()
{
    return myExerciseModel;
}

WorkoutModel* Controller::getWorkoutModel()
{
    return myWorkoutModel;
}

User* Controller::getUser()
{
    return myUser;
}

QVariantList Controller::getMuscleModel()
{
    QVariantList result;
    auto muscles = mydbmanager->getMuscles();

    for (auto muscle : muscles) {
        QVariantMap temp;
        QMap<QString, QString>::const_iterator itr = muscle.constBegin();
        while (itr != muscle.constEnd()) {
            temp.insert(itr.key(), QVariant(itr.value()));
            ++itr;
        }

        result.append(temp);
    }

    return result;
}

QVariantList Controller::getCategoryModel()
{
    QVariantList result;
    auto categories = mydbmanager->getCategories();

    for (auto category : categories) {
        QVariantMap temp;
        QMap<QString, QString>::const_iterator itr = category.constBegin();
        while (itr != category.constEnd()) {
            temp.insert(itr.key(), QVariant(itr.value()));
            ++itr;
        }

        result.append(temp);
    }

    return result;
}
