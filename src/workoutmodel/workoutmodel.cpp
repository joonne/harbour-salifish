#include "workoutmodel.h"
#include <QDebug>

WorkoutModel::WorkoutModel(QObject *parent, DatabaseManager *dbmanager) : QAbstractListModel(parent)
{
    m_db = dbmanager;
}

int WorkoutModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return m_exercises.size();
}

QHash<int, QByteArray> WorkoutModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[CategoryRole] = "category";
    roles[WeightsRole] = "weights";
    roles[RepsRole] = "reps";
    return roles;
}

QVariant WorkoutModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == IdRole) {
        return m_exercises[index.row()]->getExerciseId();
    } else if (role == NameRole) {
        return m_exercises[index.row()]->getExerciseName();
    } else if (role == DescriptionRole) {
        return m_exercises[index.row()]->getExerciseDescription();
    } else if (role == CategoryRole) {
        return m_exercises[index.row()]->getExerciseCategory();
    } else if (role == WeightsRole) {
        return m_exercises[index.row()]->getWeights();
    } else if (role == RepsRole) {
        return m_exercises[index.row()]->getReps();
    }

    return QVariant();
}

bool WorkoutModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    if (role == IdRole) {
        m_exercises[index.row()]->setExerciseId(value.toInt());
        emit dataChanged(index, index);
    } else if (role == NameRole) {
        m_exercises[index.row()]->setExerciseName(value.toString());
        emit dataChanged(index, index);
    } else if (role == DescriptionRole) {
        m_exercises[index.row()]->setExerciseDescription(value.toString());
        emit dataChanged(index, index);
    } else if (role == CategoryRole) {
        m_exercises[index.row()]->setExerciseCategory(value.toString());
        emit dataChanged(index, index);
    } else if (role == WeightsRole) {
        m_exercises[index.row()]->setWeights(value.toDouble());
        emit dataChanged(index, index);
    } else if (role == RepsRole) {
        m_exercises[index.row()]->setReps(value.toInt());
        emit dataChanged(index, index);
    }

    return true; // ??
}

void WorkoutModel::populate(QString workoutId)
{
    Q_UNUSED(workoutId);

    beginResetModel();
    m_exercises.clear();
    endResetModel();
    //    auto exercises = mydbmanager->getWorkout(workoutId);
    //    for (auto exercise : exercises) {
    //        beginInsertRows(QModelIndex(), 0, 0);
    //        ExerciseData* data = new ExerciseData(exercise["id"].toInt(), exercise["name"], exercise["description"], exercise["category"]);
    //        myExercises.append(data);
    //        endInsertRows();
    //    }

}

void WorkoutModel::addExercise(QString id, QString name, QString description, QString category, double weights, int reps)
{
    beginInsertRows(QModelIndex(), 0, 0);
    WorkoutData* data = new WorkoutData(id.toInt(), name, description, category, weights, reps);
    m_exercises.insert(0, data);
    endInsertRows();
}

void WorkoutModel::removeExerciseByIndex(const int i)
{
    if (i < 0 || i >= m_exercises.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), i, i);
    m_exercises.erase(m_exercises.begin() + i);
    endRemoveRows();
}

bool WorkoutModel::isSelected(QString name)
{
    bool ret = false;
    for (auto data : m_exercises) {
        if (name == data->getExerciseName()) {
            ret = true;
        }
    }

    return ret;
}

void WorkoutModel::removeExerciseByName(QString name)
{
    auto size = m_exercises.size();
    for (auto i = 0; i < size; ++i) {
        if (name == m_exercises.at(i)->getExerciseName()) {
            beginRemoveRows(QModelIndex(), i, i);
            m_exercises.erase(m_exercises.begin() + i);
            endRemoveRows();
            i = 0;
        }
    }
}

void WorkoutModel::clearExercises()
{
    beginResetModel();
    m_exercises.clear();
    endResetModel();
}

double WorkoutModel::calculateTotalWeights()
{
    double weights = 0;
    for (auto data : m_exercises) {
       weights += data->getReps() * data->getWeights();
    }

    return weights;
}

int WorkoutModel::calculateDuration(int pause)
{
    return pause * pause * (m_exercises.size() - 1);
}

void WorkoutModel::saveWorkout(QString name)
{
    QList<QVariantMap> exercises;
    for (auto exercise : m_exercises) {
        QVariantMap temp;
        temp["id"] = exercise->getExerciseId();
        temp["repeats"] = exercise->getReps();
        temp["weights"] = exercise->getWeights();
        exercises.append(temp);
    }

    m_db->storeWorkout(name, false, exercises);
}

void WorkoutModel::saveWorkoutTemplate(QString name)
{
    QList<QVariantMap> exercises;
    for (auto exercise : m_exercises) {
        QVariantMap temp;
        temp["id"] = exercise->getExerciseId();
        temp["repeats"] = exercise->getReps();
        temp["weights"] = exercise->getWeights();
        exercises.append(temp);
    }

    m_db->storeWorkout(name, true, exercises);
}
