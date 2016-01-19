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

    void startRequest(QUrl url);

    void getExcercises(QString muscle);
    void getAllExcercises();
    void getMuscles();

signals:
    void readyToStoreExcercises();
    void readyToStoreMuscles();

public slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* myNetWorkAccessManager;
    DatabaseManager* mydbmanager;


};

#endif // APIREADER_H
