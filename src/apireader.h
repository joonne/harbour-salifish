#ifndef APIREADER_H
#define APIREADER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "databasemanager.h"

class APIReader : public QObject
{
    Q_OBJECT
public:

    explicit APIReader(QObject *parent = 0, DatabaseManager* dbmanager = 0);
    ~APIReader();

    QNetworkReply* get(QUrl url);

    void getAllExercises();
    void getMuscles();
    void getCategories();
    void getExerciseImages(QList<QVariantMap> exercises);

    QList<QVariantMap> processExercises(QJsonArray exercises);
    QList<QVariantMap> processExerciseImages (QJsonArray exerciseImages);
    QList<QVariantMap> processMuscles(QJsonArray muscles);
    QList<QVariantMap> processCategories(QJsonArray categories);

signals:

public slots:
    void initRequested();

private:
    QNetworkAccessManager* myNetWorkAccessManager;
    DatabaseManager* mydbmanager;
};

#endif // APIREADER_H
