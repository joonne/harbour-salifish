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

    m_excercises = false;
    m_muscles = false;
    m_categories = false;

//    getAllExcercises();
    getMuscles();
//    getCategories();
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

    m_excercises = true;

    QUrl url(QString(QString(APIURL) + "/exercise/?language=2&status=2&limit=200"));
    startRequest(url);
}

void APIReader::getMuscles() {

    m_muscles = true;

    QUrl url(QString(QString(APIURL) + "/muscle/"));
    startRequest(url);
}

void APIReader::getCategories() {

    m_categories = true;

    QUrl url(QString(QString(APIURL) + "/exercisecategory/"));
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

    QJsonArray resultsArray = obj.value("results").toArray();

    if (m_excercises) {
        processExcercises(resultsArray);
    } else if (m_muscles) {
        processMuscles(resultsArray);
    } else if (m_categories) {
        processCategories(resultsArray);
    }

    m_excercises, m_muscles, m_categories = false;

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

        mydbmanager->insertExcercise(id, name, description, category);
    }
}

void APIReader::processMuscles(QJsonArray muscles) {

    int id = 0;
    QString name = "";
    int is_front = 0;

    int size = muscles.size();
    for(int i = 0; i < size; ++i) {

        id = muscles.at(i).toObject().value("id").toInt();
        name = muscles.at(i).toObject().value("name").toString();
        is_front = muscles.at(i).toObject().value("is_front").toBool() == true ? 1 : 0;

        mydbmanager->insertMuscle(id, name, is_front);
    }
}

void APIReader::processCategories(QJsonArray categories) {

    int id = 0;
    QString name = "";

    int size = categories.size();
    for(int i = 0; i < size; ++i) {

        id = categories.at(i).toObject().value("id").toInt();
        name = categories.at(i).toObject().value("name").toString();

        mydbmanager->insertCategory(id, name);
    }
}
