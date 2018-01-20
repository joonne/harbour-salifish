#ifndef EXERCISEMODEL_H
#define EXERCISEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUuid>

#include "exercisedata.h"
#include "databasemanager.h"

class ExerciseModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ExerciseRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        CategoryRole
    };

    explicit ExerciseModel(QObject *parent = 0, DatabaseManager* dbmanager = 0);

    virtual int rowCount(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void populate(QString selectedMuscle);

    Q_INVOKABLE void createNewExercise(QString name, QString description, int category);

private:
    QVector<ExerciseData*> myExercises;
    DatabaseManager* mydbmanager;

};

#endif // EXERCISEMODEL_H
