#include "workoutmodel.h"
#include <QDebug>

WorkoutModel::WorkoutModel(QObject *parent, DatabaseManager *dbmanager) : QAbstractListModel(parent)
{
    mydbmanager = dbmanager;

}

int WorkoutModel::rowCount(const QModelIndex &index) const {
    Q_UNUSED(index)
    return myExercises.size();
}

QHash<int, QByteArray> WorkoutModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[CategoryRole] = "category";
    roles[WeightsRole] = "weights";
    roles[RepsRole] = "reps";
    return roles;
}

QVariant WorkoutModel::data(const QModelIndex &index, int role) const {

    if(!index.isValid()) {
        return QVariant();
    }

    if(role == IdRole) {
        return myExercises[index.row()]->getExerciseId();
    } else if(role == NameRole) {
        return myExercises[index.row()]->getExerciseName();
    } else if(role == DescriptionRole) {
        return myExercises[index.row()]->getExerciseDescription();
    } else if(role == CategoryRole) {
        return myExercises[index.row()]->getExerciseCategory();
    } else if(role == WeightsRole) {
        return myExercises[index.row()]->getWeights();
    } else if(role == RepsRole) {
        return myExercises[index.row()]->getReps();
    }
    return QVariant();
}

bool WorkoutModel::setData(const QModelIndex &index, const QVariant &value, int role) {

    if(!index.isValid()) {
        return false;
    }

    if(role == IdRole) {
        myExercises[index.row()]->setExerciseId(value.toInt());
        emit dataChanged(index, index);
    } else if(role == NameRole) {
        myExercises[index.row()]->setExerciseName(value.toString());
        emit dataChanged(index, index);
    } else if(role == DescriptionRole) {
        myExercises[index.row()]->setExerciseDescription(value.toString());
        emit dataChanged(index, index);
    } else if(role == CategoryRole) {
        myExercises[index.row()]->setExerciseCategory(value.toString());
        emit dataChanged(index, index);
    } else if(role == WeightsRole) {
        myExercises[index.row()]->setWeights(value.toDouble());
        emit dataChanged(index, index);
    } else if(role == RepsRole) {
        myExercises[index.row()]->setReps(value.toInt());
        emit dataChanged(index, index);
    }
}

void WorkoutModel::populate(QString workoutId) {

    Q_UNUSED(workoutId);

    beginResetModel();
    myExercises.clear();
    endResetModel();

//    QList<QMap<QString,QString> > exercises = mydbmanager->getWorkout(workoutId);
//    int size = exercises.size();
//    for(int i = 0; i < size; ++i) {
//        QMap<QString,QString> temp = exercises.at(i);
//        beginInsertRows(QModelIndex(), 0, 0);
//        ExerciseData* data = new ExerciseData(temp["id"].toInt(), temp["name"], temp["description"], temp["category"]);
//        myExercises.append(data);
//        endInsertRows();
//    }
}

void WorkoutModel::addExercise(int index, QString id, QString name, QString description, QString category, double weights, int reps) {

    beginInsertRows(QModelIndex(), index, index);
    WorkoutData* data = new WorkoutData(id.toInt(), name, description, category, weights, reps);
    myExercises.insert(index, data);
    endInsertRows();
}

void WorkoutModel::removeExerciseByIndex(const int i) {

    if(i < 0 || i >= myExercises.size()) {
        return;
    }

    beginRemoveRows(QModelIndex(), i, i);
    myExercises.erase(myExercises.begin() + i);
    endRemoveRows();

}

bool WorkoutModel::isSelected(QString name) {

    bool ret = false;
    foreach (auto data, myExercises) {
        if(name == data->getExerciseName()) {
            ret = true;
        }
    }
    return ret;
}

void WorkoutModel::removeExerciseByName(QString name) {

    for (auto i = 0; i < myExercises.size(); ++i) {
        qDebug() << myExercises.at(i)->getExerciseName();
        if(name == myExercises.at(i)->getExerciseName()) {
            qDebug() << "found " << name << " at " << i;
            beginRemoveRows(QModelIndex(), i, i);
            myExercises.erase(myExercises.begin() + i);
            endRemoveRows();
            i = 0;
        }
    }
}

void WorkoutModel::clearExercises() {
    beginResetModel();
    myExercises.clear();
    endResetModel();
}

double WorkoutModel::calculateTotalWeights() {

    double weights = 0;
    foreach (auto data, myExercises) {
       weights += data->getReps() * data->getWeights();
    }

    return weights;
}

int WorkoutModel::calculateDuration(int pause) {

    return pause * pause * (myExercises.size() - 1);
}

void WorkoutModel::saveWorkout() {
    qDebug() << "save workout";
}

void WorkoutModel::saveWorkoutTemplate() {
    qDebug() << "save workout template";
}
