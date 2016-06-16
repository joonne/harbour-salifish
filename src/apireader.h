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

    void getPart();

    void getAllExcercises();
    void getMuscles();
    void getCategories();

    void processExcercises(QJsonArray excercises);
    void processMuscles(QJsonArray muscles);
    void processCategories(QJsonArray categories);

signals:
    void readyToStoreExcercises();
    void readyToStoreMuscles();

public slots:
    void replyFinished(QNetworkReply* reply);
    void initRequested();

private:
    QNetworkAccessManager* myNetWorkAccessManager;
    DatabaseManager* mydbmanager;

    QList<QString> m_tasks;

    // flags
    bool m_excercises;
    bool m_muscles;
    bool m_categories;

};

#endif // APIREADER_H
