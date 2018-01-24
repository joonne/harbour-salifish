#include "exercisemodel.h"
#include <QDebug>

ExerciseModel::ExerciseModel(QObject *parent, DatabaseManager *dbmanager) :
    QAbstractListModel(parent)
{
    mydbmanager = dbmanager;
}

int ExerciseModel::rowCount(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return myExercises.size();
}

QHash<int, QByteArray> ExerciseModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[CategoryRole] = "category";
    roles[ImageRole] = "image";

    return roles;
}

QVariant ExerciseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == IdRole) {
        return myExercises[index.row()]->getExerciseId();
    } else if (role == NameRole) {
        return myExercises[index.row()]->getExerciseName();
    } else if (role == DescriptionRole) {
        return myExercises[index.row()]->getExerciseDescription();
    } else if (role == CategoryRole) {
        return myExercises[index.row()]->getExerciseCategory();
    } else if (role == ImageRole) {
        return myExercises[index.row()]->getExerciseImage();
    }

    return QVariant();
}

void ExerciseModel::populate(QString category)
{
    beginResetModel();
    myExercises.clear();
    endResetModel();

    auto exercises = mydbmanager->getExercises(category);

    for (auto exercise: exercises) {
        beginInsertRows(QModelIndex(), 0, 0);
        ExerciseData* data = new ExerciseData(exercise["id"].toInt(), exercise["name"], exercise["description"], exercise["category"], exercise["image"]);
        myExercises.insert(0, data);
        endInsertRows();
    }
}

void ExerciseModel::createNewExercise(QString name, QString description, int category)
{
    auto uuid = QUuid::createUuid().toString();
//    mydbmanager->insertExercise(uuid, name, description, category);
}
