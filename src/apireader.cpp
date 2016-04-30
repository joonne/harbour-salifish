#include "apireader.h"

#define APIURL "https://wger.de/api/v2"

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

void APIReader::getExcercises(QString muscleId) {

    QUrl url(QString(QString(APIURL) + "/exercise/?muscles=" + muscleId + "&language=2&status=2"));
    startRequest(url);
}

void APIReader::getAllExcercises() {

    QUrl url(QString(QString(APIURL) + "/exercise/?language=2&status=2&limit=200"));
    startRequest(url);
}

void APIReader::getMuscles() {

    QUrl url(QString(QString(APIURL) + "/muscle"));
    startRequest(url);
}

void APIReader::getCategories() {

    QUrl url(QString(QString(APIURL) + "/exercisecategory"));
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

    qDebug() << obj.value("results");

    QJsonValue resultsObj = obj.value("results");
    QJsonArray resultsArray = resultsObj.toArray();

    processExcercises(resultsArray);

    reply->deleteLater();
}

void APIReader::processExcercises(QJsonArray excercises) {

    int id = 0;
    QString name = "";
    QString description = "";
    int category = 0;

    int size = excercises.size();
    for(int i = 0; i < size; ++i) {

        id = excercises.at(i).toObject().value("id").toInt();
        name = excercises.at(i).toObject().value("name").toString();
        description = excercises.at(i).toObject().value("description").toString().remove(QRegExp("<[^>]*>"));
        category = excercises.at(i).toObject().value("category").toInt();

        qDebug() << id;
        qDebug() << name;
        qDebug() << description;
        qDebug() << category;

        mydbmanager->insertExcercise(id, name, description, category);
    }
}

void APIReader::populateDatabase() {

}
