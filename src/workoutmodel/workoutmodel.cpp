#include "workoutmodel.h"
#include <QDebug>

WorkoutModel::WorkoutModel(QObject *parent, DatabaseManager *dbmanager) : QAbstractListModel(parent)
{
    mydbmanager = dbmanager;

}

int WorkoutModel::rowCount(const QModelIndex &index) const {
    Q_UNUSED(index)
    return myExcercises.size();
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
        return myExcercises[index.row()]->getExcerciseId();
    } else if(role == NameRole) {
        return myExcercises[index.row()]->getExcerciseName();
    } else if(role == DescriptionRole) {
        return myExcercises[index.row()]->getExcerciseDescription();
    } else if(role == CategoryRole) {
        return myExcercises[index.row()]->getExcerciseCategory();
    } else if(role == WeightsRole) {
        return myExcercises[index.row()]->getWeights();
    } else if(role == RepsRole) {
        return myExcercises[index.row()]->getReps();
    }
    return QVariant();
}

void WorkoutModel::populate(QString workoutId) {

    Q_UNUSED(workoutId);

    beginResetModel();
    myExcercises.clear();
    endResetModel();

//    QList<QMap<QString,QString> > excercises = mydbmanager->getWorkout(workoutId);
//    int size = excercises.size();
//    for(int i = 0; i < size; ++i) {
//        QMap<QString,QString> temp = excercises.at(i);
//        beginInsertRows(QModelIndex(), 0, 0);
//        ExcerciseData* data = new ExcerciseData(temp["id"].toInt(), temp["name"], temp["description"], temp["category"]);
//        myExcercises.append(data);
//        endInsertRows();
//    }
}

void WorkoutModel::addExcercise(QString id, QString name, QString description, QString category, double weights, int reps) {

    beginInsertRows(QModelIndex(), 0, 0);
    WorkoutData* data = new WorkoutData(id.toInt(), name, description, category, weights, reps);
    myExcercises.insert(0, data);
    endInsertRows();
}
