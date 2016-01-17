#include "apireader.h"

#define APIURL "https://wger.de/api/v2/"

APIReader::APIReader(QObject *parent) :
    QObject(parent),
    myNetWorkAccessManager(0)
{
    myNetWorkAccessManager = new QNetworkAccessManager(this);

    connect(myNetWorkAccessManager,
            SIGNAL(finished(QNetworkReply*)),
            this,
            SLOT(replyFinished(QNetworkReply*)));

    getExcercises("1");
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

    QUrl finalUrl(QString(QString(APIURL) + "/exercise/?muscles=" + muscle + "&language=2&status=2"));
    startRequest(finalUrl);
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


    qDebug() << obj.toVariantMap()["results"].value<QVariantMap>();

//    QVariantMap results = obj.toVariantMap()["results"].at(0);

//    QVariantMap::iterator itr = results.begin();
//    while(itr != results.end()) {
//        qDebug() << itr.key();
//        qDebug() << itr.value();
//    }

}
