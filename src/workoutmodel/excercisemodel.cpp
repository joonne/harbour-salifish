#include "excercisemodel.h"

ExcerciseModel::ExcerciseModel(QObject *parent) :
    QAbstractListModel(parent) {

}

QHash<int, QByteArray> ExcerciseModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[DescriptionRole] = "description";
    roles[CategoryRole] = "category";
    return roles;
}

QVariant ExcerciseModel::data(const QModelIndex &index, int role) const {

    if(!index.isValid()) {
        return QVariant();
    }

    if(role == IdRole) {
        return QVariant(excercises[index.row()]);
    } else if(role == NameRole) {
        return QVariant(excercises[index.row()]);
    } else if(role == DescriptionRole) {
        return QVariant(excercises[index.row()]);
    } else if(role == CategoryRole) {
        return QVariant(excercises[index.row()]);
    }
    return QVariant();
}

void ExcerciseModel::populate() {

    beginInsertRows(QModelIndex(), 0, 0);
    ExcerciseData* data = new ExcerciseData(this, 1, "Bench Press", "push the bar", "chest");
    excercises.insert(0, "Bench Press");
    endInsertRows();
}
