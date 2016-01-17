#ifndef APIREADER_H
#define APIREADER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTemporaryFile>
#include <QList>
#include <QStringRef>
#include <QByteArray>
#include <QBuffer>
#include <QJsonObject>
#include <QJsonDocument>

class APIReader : public QObject
{
    Q_OBJECT
public:

    explicit APIReader(QObject *parent = 0);
    ~APIReader();

    void startRequest(QUrl url);

    void getExcercises(QString muscle);

signals:
public slots:
    void replyFinished(QNetworkReply* reply);

private:

    QNetworkAccessManager* myNetWorkAccessManager;

};

#endif // APIREADER_H
