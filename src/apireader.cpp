#include "apireader.h"

#define APIURL "https://wger.de/api/v2/"

APIReader::APIReader(QObject *parent, DatabaseManager *dbmanager) :
    QObject(parent),
    myNetWorkAccessManager(0),
    mydbmanager(0)
{
    myNetWorkAccessManager = new QNetworkAccessManager(this);
    mydbmanager = dbmanager;

    connect(myNetWorkAccessManager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));

//    getExcercises("1");
//    getExcercises("2");
//    getExcercises("3");
//    getExcercises("4");
//    getExcercises("5");

    getAllExcercises();
}

APIReader::~APIReader() {

    delete myNetWorkAccessManager;
    myNetWorkAccessManager = 0;
    qDebug() << "destructing apireader";

}

void APIReader::startRequest(QUrl url) {

    QNetworkRequest request(url);
    myNetWorkAccessManager->get(request);

}

void APIReader::getExcercises(QString muscle) {

    QUrl url(QString(QString(APIURL) + "/exercise/?muscles=" + muscle + "&language=2&status=2"));
    startRequest(url);
}

void APIReader::getAllExcercises() {

    QUrl url(QString(QString(APIURL) + "/exercise/&language=2&status=2&limit=200"));
    startRequest(url);
}

void APIReader::getMuscles() {

    QUrl url(QString(QString(APIURL) + "/muscle"));
    startRequest(url);
}

// ---------------------------------------------------
// slots
// ---------------------------------------------------

void APIReader::replyFinished(QNetworkReply *reply) {

    QString response = (QString) reply->readAll();
    qDebug() << response;

    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());

    // check validity of the document
    if(!doc.isNull()) {
        if(doc.isObject()) {
            obj = doc.object();
        } else {
            qDebug() << "Document is not an object" << endl;
        }
    } else {
        qDebug() << "Invalid JSON...\n" << response << endl;
    }
    reply->deleteLater();


    qDebug() << obj.value("results");

    QString name = "";
    QString description = "";

    QJsonValue excercisesObj = obj.value("results");
    QJsonArray excercises = excercisesObj.toArray();

    int size = excercises.size();
    for(int i = 0; i < size; ++i) {
        name = excercises.at(i).toObject().value("name").toString();
        description = excercises.at(i).toObject().value("description").toString();
        qDebug() << name;
        qDebug() << description;
//        mydbmanager->insertExcercise(name,description,"biceps");
    }
}
