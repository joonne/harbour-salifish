#ifndef EXCERCISEMODEL_H
#define EXCERCISEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QUuid>

#include "excercisedata.h"
#include "databasemanager.h"

class ExcerciseModel : public QAbstractListModel
{
    Q_OBJECT
public:

    enum ExcerciseRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        CategoryRole
    };

    explicit ExcerciseModel(QObject *parent = 0, DatabaseManager* dbmanager = 0);

    virtual int rowCount(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void populate(QString selectedMuscle);

    Q_INVOKABLE void createNewExcercise(QString name, QString description, int category);

private:
    QVector<ExcerciseData*> myExcercises;
    DatabaseManager* mydbmanager;

};

#endif // EXCERCISEMODEL_H
