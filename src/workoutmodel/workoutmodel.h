#ifndef WORKOUTMODEL_H
#define WORKOUTMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "workoutdata.h"
#include "databasemanager.h"

class WorkoutModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ExcerciseRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        CategoryRole,
        WeightsRole,
        RepsRole
    };

    explicit WorkoutModel(QObject *parent = 0, DatabaseManager* dbmanager = 0);

    virtual int rowCount(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void populate(QString workoutId);
    Q_INVOKABLE void addExcercise(QString id, QString name, QString description, QString category, double weights, int reps);

private:
    QList<WorkoutData*> myExcercises;
    DatabaseManager* mydbmanager;
};

#endif // WORKOUTMODEL_H
