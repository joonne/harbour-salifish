#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlDriver>
#include <QDir>
#include <QStandardPaths>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int age READ getAge WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString gender READ getGender WRITE setGender NOTIFY genderChanged)
    Q_PROPERTY(double height READ getHeight WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(double weight READ getWeight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(double BMI READ getBMI NOTIFY BMIChanged)
    Q_PROPERTY(QString BMIdescription READ getBMIdescription NOTIFY BMIdescriptionChanged)
    Q_PROPERTY(double BMR READ getBMR NOTIFY BMRChanged)

public:
    User(QObject *parent = 0);
    ~User();
    Q_INVOKABLE void clean();

    QString getName();
    int getAge();
    QString getGender();
    double getHeight();
    double getWeight();
    double getBMI();
    double getBMR();

    QString getBMIdescription();
    void calculateBMI();
    void calculateBMR();

    void setName(QString name);
    void setAge(int age);
    void setGender(QString gender);
    void setHeight(double height);
    void setWeight(double weight);

    bool getUser();
    bool insertUser(QString name, int age, QString gender,
                 double height, double weight);
    bool updateName(QString name);
    bool updateAge(int age);
    bool updateGender(QString gender);
    bool updateHeight(double height);
    bool updateWeight(double weight);
    bool openDB();
    void closeDB();

signals:
    void nameChanged();
    void ageChanged();
    void genderChanged();
    void heightChanged();
    void weightChanged();
    void BMIChanged();
    void BMIdescriptionChanged();
    void BMRChanged();


private:
    QString name_;
    int age_;
    QString gender_;
    double height_;
    double weight_;
    double BMI_;
    QString BMIdescription_;
    double BMR_;
    QSqlDatabase db_;

};

#endif // USER_H
