#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QSqlQuery>
#include <QStandardPaths>

class UserDatabase : public QObject
{
    Q_OBJECT
public:
    explicit UserDatabase(QObject *parent = 0);
    ~UserDatabase();

    bool openDB();
    bool deleteDB();
    QSqlError lastError();
    void close();

    bool createUserTable();
    bool insertUser(QString name, int age, QString gender, double height, double weight);

private:

    QSqlDatabase db;


};

#endif // USERDATABASE_H
