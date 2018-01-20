#include "apireader.h"

#define APIURL "https://wger.de/api/v2"

APIReader::APIReader(QObject *parent, DatabaseManager *dbmanager) :
    QObject(parent),
    myNetWorkAccessManager(0),
    mydbmanager(0)
{
    myNetWorkAccessManager = new QNetworkAccessManager(this);
    mydbmanager = dbmanager;

    connect(mydbmanager,
            SIGNAL(initDbWithData()),
            this,
            SLOT(initRequested()));
}

APIReader::~APIReader()
{
    delete myNetWorkAccessManager;
    myNetWorkAccessManager = 0;
}

QNetworkReply* APIReader::get(QUrl url)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Content-Type"), QByteArray("application/json"));

    qDebug() << "REQUESTING" << request.url().toString();

    return myNetWorkAccessManager->get(request);
}

void APIReader::initRequested()
{
    getCategories();
    getMuscles();
    getAllExercises();
}

void APIReader::getAllExercises()
{
    QUrl url(QString(QString(APIURL) + "/exercise/?language=2&status=2&limit=200"));
    auto reply = get(url);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        auto document = QJsonDocument::fromJson(reply->readAll());

        if (!document.isNull()) {
            auto exercises = processExercises(document.object().value("results").toArray());
            mydbmanager->insertExercises(exercises);
        }

        reply->deleteLater();
    });
}

void APIReader::getMuscles()
{
    QUrl url(QString(QString(APIURL) + "/muscle/"));
    auto reply = get(url);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        auto document = QJsonDocument::fromJson(reply->readAll());

        if (!document.isNull()) {
            auto muscles = processMuscles(document.object().value("results").toArray());
            mydbmanager->insertMuscles(muscles);
        }

        reply->deleteLater();
    });
}

void APIReader::getCategories()
{
    QUrl url(QString(QString(APIURL) + "/exercisecategory/"));
    auto reply = get(url);

    connect(reply, &QNetworkReply::finished, [this, reply]()
    {
        auto document = QJsonDocument::fromJson(reply->readAll());

        if (!document.isNull()) {
            auto categories = processCategories(document.object().value("results").toArray());
            mydbmanager->insertCategories(categories);
        }

        reply->deleteLater();
    });
}

QList<QVariantMap> APIReader::processExercises(QJsonArray exercises)
{
    QList<QVariantMap> result;

    for (auto exercise: exercises) {
        QVariantMap temp;

        auto object = exercise.toObject();
        temp.insert("id", object.value("id").toInt());
        temp.insert("name", object.value("name").toString());
        temp.insert("description", object.value("description").toString().remove(QRegExp("<[^>]*>")));
        temp.insert("category", object.value("category").toInt());

        result.append(temp);
    }

    return result;
}

QList<QVariantMap> APIReader::processMuscles(QJsonArray muscles)
{
    QList<QVariantMap> result;

    for (auto muscle : muscles) {
        QVariantMap temp;

        auto object = muscle.toObject();
        temp.insert("id", object.value("id").toInt());
        temp.insert("name", object.value("name").toString());
        temp.insert("is_front", object.value("is_front").toBool() ? 1 : 0);

        result.append(temp);
    }

    return result;
}

QList<QVariantMap> APIReader::processCategories(QJsonArray categories)
{
    QList<QVariantMap> result;

    for(auto category : categories) {
        QVariantMap temp;

        auto object = category.toObject();
        temp.insert("id", object.value("id").toInt());
        temp.insert("name", object.value("name").toString());

        result.append(temp);
    }

    return result;
}
