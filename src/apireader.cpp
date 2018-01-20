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

    getAllExercises();
//    getMuscles();
//    getCategories();
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
//    request.setRawHeader(QByteArray("Authorization"), (QString("Bearer %1").arg(m_jwt)).toLocal8Bit());
    request.setRawHeader(QByteArray("Accept-Language"), QByteArray("en"));

    qDebug() << "REQUESTING" << request.url().toString();

    return myNetWorkAccessManager->get(request);
}

void APIReader::initRequested()
{
    m_tasks.append("exercises");
    m_tasks.append("muscles");
    m_tasks.append("categories");

    getPart();
}

void APIReader::getPart()
{
    if(!m_tasks.isEmpty()) {
        QString task = m_tasks.takeFirst();

        if (task == "exercises") {
            getAllExercises();
        } else if (task == "muscles") {
            getMuscles();
        } else if (task == "categories") {
            getCategories();
        }
    }
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
            processMuscles(document.array());
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
            processCategories(document.array());
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

void APIReader::processMuscles(QJsonArray muscles)
{
    for (auto muscle : muscles) {
        auto object = muscle.toObject();

        auto id = object.value("id").toInt();
        auto name = object.value("name").toString();
        auto is_front = object.value("is_front").toBool() ? 1 : 0;

        mydbmanager->insertMuscle(id, name, is_front);
    }
}

void APIReader::processCategories(QJsonArray categories)
{
    for(auto category : categories) {
        auto object = category.toObject();

        auto id = object.value("id").toInt();
        auto name = object.value("name").toString();

        mydbmanager->insertCategory(id, name);
    }
}
