#include "controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    m_db = new DatabaseManager(this);
    m_ExerciseModel = new ExerciseModel(this, m_db);
    m_WorkoutModel = new WorkoutModel(this, m_db);
    m_api = new APIReader(this, m_db);
    m_User = new User(this, m_db);

    m_db->setUpDB();

    m_ExerciseProxyModel = new QSortFilterProxyModel(this);
    m_ExerciseProxyModel->setSourceModel(m_ExerciseModel);
    m_ExerciseProxyModel->setFilterRole(0);
    m_ExerciseProxyModel->setDynamicSortFilter(true);
}

ExerciseModel* Controller::getExerciseModel()
{
    return m_ExerciseModel;
}

void Controller::sortExercises(QString name)
{
    m_ExerciseProxyModel->setFilterFixedString(name);
}

QSortFilterProxyModel* Controller::getExerciseProxyModel()
{
    return m_ExerciseProxyModel;
}

WorkoutModel* Controller::getWorkoutModel()
{
    return m_WorkoutModel;
}

User* Controller::getUser()
{
    return m_User;
}

QVariantList Controller::getMuscleModel()
{
    QVariantList result;
    auto muscles = m_db->getMuscles();

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
    auto categories = m_db->getCategories();

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
