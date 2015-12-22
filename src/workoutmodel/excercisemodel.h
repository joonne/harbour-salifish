#ifndef EXCERCISEMODEL_H
#define EXCERCISEMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "excercisedata.h"

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

    explicit ExcerciseModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &) const { return excercises.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void populate();

private:
    QVector<QString> excercises;

};

#endif // EXCERCISEMODEL_H
