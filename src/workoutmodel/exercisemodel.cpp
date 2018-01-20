#include "exercisemodel.h"
#include <QDebug>

ExerciseModel::ExerciseModel(QObject *parent, DatabaseManager *dbmanager) :
    QAbstractListModel(parent) {

    mydbmanager = dbmanager;
}

int ExerciseModel::rowCount(const QModelIndex &index) const {
    Q_UNUSED(index)
    return myExercises.size();
}

QHash<int, QByteArray> ExerciseModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[CategoryRole] = "category";
    return roles;
}

QVariant ExerciseModel::data(const QModelIndex &index, int role) const {

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
    }
    return QVariant();
}

void ExerciseModel::populate(QString selectedMuscle) {

    beginResetModel();
    myExercises.clear();
    endResetModel();

    QList<QMap<QString,QString> > exercises = mydbmanager->getExercises(selectedMuscle);
    int size = exercises.size();
    QMap<QString,QString> temp;
    for(int i = 0; i < size; ++i) {
        temp = exercises.at(i);
        beginInsertRows(QModelIndex(), 0, 0);
        qDebug() << temp["description"];
        ExerciseData* data = new ExerciseData(temp["id"].toInt(), temp["name"], temp["description"], temp["category"]);
        myExercises.insert(0, data);
        endInsertRows();
    }
}

void ExerciseModel::createNewExercise(QString name, QString description, int category) {

    auto uuid = QUuid::createUuid().toString();
//    mydbmanager->insertExercise(uuid, name, description, category);
}
