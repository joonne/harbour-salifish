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
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void populate(QString workoutId);

    Q_INVOKABLE void addExcercise(int index, QString id, QString name, QString description, QString category, double weights, int reps);
    Q_INVOKABLE void removeExcerciseByIndex(const int i);
    Q_INVOKABLE void removeExcerciseByName(QString name);
    Q_INVOKABLE void clearExcercises();
    Q_INVOKABLE bool isSelected(QString name);

    Q_INVOKABLE double calculateTotalWeights();
    Q_INVOKABLE int calculateDuration(int pause);

    Q_INVOKABLE void saveWorkout();
    Q_INVOKABLE void saveWorkoutTemplate();

private:
    QVector<WorkoutData*> myExcercises;
    DatabaseManager* mydbmanager;
};

#endif // WORKOUTMODEL_H
