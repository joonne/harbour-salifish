#include "gymmodel.h"
#include <QDebug>

GymModel::GymModel(QObject* parent) : QObject(parent) {

    currentSeriesIndex_ = 1;

}

GymModel::~GymModel() {
    qDebug() << "Destroying GymModel..";
    clean();
}

QString GymModel::getName() {

    return name_;
}

QString GymModel::getExcerciseName() {

    return excerciseName_;
}

QString GymModel::getDescription() {

    return description_;
}

QString GymModel::getExcerciseDescription() {

    return excerciseDescription_;
}

QString GymModel::getSelectedMuscle() {

    return selectedMuscle_;
}

QString GymModel::getSelectedExcercise() {

    return selectedExcercise_;
}

QString GymModel::getMode() {
    return mode_;
}

void GymModel::setName(QString excerciseName) {

    if(excerciseName != name_ and excerciseName != "") {
        name_ = excerciseName;
        emit nameChanged();
    }
}

void GymModel::setExcerciseName(QString excerciseName) {

    excerciseName_ = excerciseName;
    emit excerciseNameChanged();
}

void GymModel::setDescription(QString description) {

    if(description != description_ and description != "") {
        description_ = description;
        emit DescriptionChanged();
    }
}

void GymModel::setExcerciseDescription(QString excerciseDescription) {

    excerciseDescription_ = excerciseDescription;
    emit excerciseDescriptionChanged();
}

void GymModel::setSelectedMuscle(QString selectedMuscle) {

    selectedMuscle_ = selectedMuscle;
    emit SelectedMuscleChanged();
}

void GymModel::setSelectedExcercise(QString selectedExcercise) {

    selectedExcercise_ = selectedExcercise;
    emit SelectedExcerciseChanged();
}

void GymModel::setMode(QString mode) {

    mode_ = mode;
    emit modeChanged();
}

bool GymModel::getExcercises() {

    excerciseNames_.clear();
    excerciseCount_ = 0;

    bool ret = false;

    if(db_.isOpen()) {

        qDebug() << "Tietokannan avaaminen onnistui.";

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM '%1';").arg(selectedMuscle_.toLower()));
        qDebug() << query.lastError();

        while(query.next()) {

            excerciseNames_ << query.value(1).toString();
            ++excerciseCount_;

        }

        qDebug() << excerciseNames_;
    }

    context_->setContextProperty("excerciseNamesModel",QVariant::fromValue(excerciseNames_));
    return ret;
}

bool GymModel::getWorkouts() {

    workoutNames_.clear();
    workoutTableNames_.clear();
    getWorkoutTables();

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM workoutnames;"));
        qDebug() << query.lastError();

        while(query.next()) {

            workoutNames_ << query.value(1).toString();
            workoutTableNames_ << query.value(2).toString();
        }

        qDebug() << workoutNames_;
        qDebug() << workoutTableNames_;
    }

    context_->setContextProperty("workoutsModel",QVariant::fromValue(workoutNames_));
    return ret;
}

bool GymModel::getPreviousWorkouts() {

    previousWorkouts_.clear();

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM previousworkoutnames;"));
        qDebug() << query.lastError();

        while(query.next()) {

            previousWorkouts_ << query.value(1).toString() + " " + query.value(3).toString();
        }

        qDebug() << previousWorkouts_;
    }

    context_->setContextProperty("previousWorkoutsModel",QVariant::fromValue(previousWorkouts_));
    return ret;
}


bool GymModel::getWorkout(QString workout) {

    workoutName_ = workout;
    bool ret = false;
    excercises_.clear();
    excerciseNames_.clear();
    series_.clear();
    repeats_.clear();
    weights_.clear();
    comments_.clear();
    coverExcerciseIndex_ = 0;

    // figures out the index of the workout and then the table that contains the information,
    // TODO: make a good error check later for all of these!
    int workoutIndex = findWorkoutIndex(workout);
    workoutIndex = workoutIndex - 1;
    QString tablename = workoutTableNames_.at(workoutIndex);
    qDebug() << "get from: " << tablename;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM '%1';").arg(tablename));
        qDebug() << query.lastError();

        while(query.next()) {

            excercises_ << query.value(1).toString() + "         " + query.value(2).toString() + " x " +
                           query.value(3).toString() + " x " + query.value(4).toString() + " kg";

            excerciseNames_ << query.value(1).toString();
            series_ << query.value(2).toString();
            repeats_ << query.value(3).toString();
            weights_ << query.value(4).toString();
            comments_ << query.value(5).toString();

        }
    }

    workout_ = excerciseNames_;
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));
    context_->setContextProperty("excerciseNamesModel",QVariant::fromValue(excerciseNames_));
    context_->setContextProperty("seriesModel",QVariant::fromValue(series_));
    context_->setContextProperty("repeatsModel",QVariant::fromValue(repeats_));
    context_->setContextProperty("weightsModel",QVariant::fromValue(weights_));
    context_->setContextProperty("excercisesModel",QVariant::fromValue(excercises_));
    context_->setContextProperty("selectedExcercisesModel",QVariant::fromValue(excerciseNames_));


    return ret;

}

bool GymModel::getExcercise(QString excercise) {

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM '%1' WHERE name = '%2'").arg(selectedMuscle_.toLower()).arg(excercise));
        qDebug() << query.lastError();

        if(query.next()) {

            setExcerciseName(query.value(1).toString());
            setExcerciseDescription(query.value(2).toString());
        }
    }

    return ret;
}

bool GymModel::openDB() {

    // Find QSLite driver
    db_ = QSqlDatabase::addDatabase("QSQLITE","dataConnection");
    db_.setDatabaseName("/home/nemo/qml/Sqlite/gymDatabase.db.sqlite");

    // TODO
    //QString dbpath = QStandardPaths::DataLocation;


    // Open databasee
    if(db_.open()) {
        QStringList tables = db_.tables();
        qDebug() << "Tables: " << tables;
        return true;
    } else {
        qDebug() << db_.lastError();
        return false;
    }
}

void GymModel::closeDB() {
    db_.close();
}

bool GymModel::insertExcerciseName(QString excerciseName) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2');").arg(selectedMuscle_).arg(excerciseName));
        qDebug() << query.lastError();

    }
    return ret;
}

bool GymModel::insertExcerciseDescription(QString description) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2');").arg(selectedMuscle_).arg(description));
        qDebug() << query.lastError();

    }
    return ret;
}

bool GymModel::insertExcercise() {

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2','%3');")
                         .arg(selectedMuscle_.toLower()).arg(name_).arg(description_));
    }

    excerciseNames_ << name_;
    context_->setContextProperty("excerciseNamesModel",QVariant::fromValue(excerciseNames_));


    return ret;
}

bool GymModel::insertWorkoutExcercises() {

    bool ret = false;

    for(int i = 0; i < selectedExcercises_.size(); ++i) {

        qDebug() << "adding " << selectedExcercises_.at(i) << " to " << workoutName_;
        QString excercise = selectedExcercises_.at(i);

        if(db_.isOpen()) {

            QSqlQuery query(db_);
            ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2',%3,%4,%5,'%6');")
                             .arg(workoutName_).arg(excercise)
                             .arg(3).arg(12).arg(70));
            qDebug() << query.lastError();
        }
    }

    return ret;
}

// Finds and deletes an excercise from the database.
bool GymModel::deleteExcerciseFromDB() {

    bool ret = false;

    getExcercises();
    if(findExcerciseIndex()) {

        if(db_.isOpen()) {

            QSqlQuery query(db_);
            ret = query.exec(QString("DELETE FROM '%1' WHERE ID = %2").arg(selectedMuscle_).arg(excerciseIndex_));
        }

        if(ret) {
            removeExcercise(selectedExcercise_);
        }
    }

    return ret;
}

bool GymModel::deleteWorkoutFromDB(QString workoutName) {

    qDebug() << "removing workout from db";

    bool ret = false;
    bool ret1 = false;
    bool ret2 = false;

    if(findWorkoutIndex(workoutName)) {

        qDebug() << "index found: " << workoutIndex_;

        if(db_.isOpen()) {

            QSqlQuery query(db_);
            ret1 = query.exec(QString("DELETE FROM workoutnames WHERE ID = %1").arg(workoutIndex_));

            if(ret1) ret2 = query.exec(QString("DELETE FROM '%1'").arg(workoutName));
        }

        if(ret1 and ret2) {
            removeWorkout(workoutName);
            ret = true;

            qDebug() << workoutName << " removed.";
        }
    }

    return ret;
}

bool GymModel::createWorkout() {

    qDebug() << "creating new workout...";

    QStringRef sub(&workoutName_, 0, 3);
    QString tablename = sub.toString() + "-workout";

    bool ret = false;
    bool ret1 = false;
    bool ret2 = false;
    bool ret3 = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret1 = query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'"
                                  "(id integer primary key, "
                                  "excercisename varchar(50), "
                                  "series integer, "
                                  "repeats1 integer, "
                                  "weights1 real, "
                                  "repeats2 integer, "
                                  "weights2 real, "
                                  "repeats3 integer, "
                                  "weights3 real, "
                                  "repeats4 integer, "
                                  "weights4 real, "
                                  "repeats5 integer, "
                                  "weights5 real, "
                                  "repeats6 integer, "
                                  "weights6 real)").arg(tablename));

        qDebug() << query.lastError();


        if(ret1) {

            qDebug() << "table " << tablename << " created.";

            ret2 = query.exec(QString("INSERT INTO workoutnames VALUES(NULL,'%1','%2')")
                              .arg(workoutName_).arg(tablename));

            qDebug() << query.lastError();

        }

        if(ret1 and ret2) {

            for( int i = 0; i < selectedExcercises_.size(); ++i ) {

                ret3 = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                                  .arg(workoutName_)
                                  .arg(selectedExcercises_.at(i))
                                  .arg(3)
                                  .arg(12).arg(40)
                                  .arg(12).arg(40)
                                  .arg(12).arg(40)
                                  .arg(0).arg(0)
                                  .arg(0).arg(0)
                                  .arg(0).arg(0));

                qDebug() << query.lastError();

            }

        }


        if(ret1 and ret2 and ret3) {

            workoutNames_ << workoutName_;
            workoutTableNames_ << tablename;
            context_->setContextProperty("workoutsModel",QVariant::fromValue(workoutNames_));
            ret = true;

            qDebug() << workoutName_ << " added to database.";
        }
    }
    return ret;
}

bool GymModel::createPreviousWorkout() {

    qDebug() << "creating table for done workout...";

    QStringRef sub(&workoutName_, 0, 3);
    QString tablename = sub.toString() + "-doneworkout";

    QString date = QDate::currentDate().toString();

    bool ret = false;
    bool ret1 = false;
    bool ret2 = false;
    bool ret3 = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret1 = query.exec(QString("CREATE TABLE IF NOT EXISTS '%1'"
                                  "(id integer primary key, "
                                  "excercisename varchar(50), "
                                  "series integer, "
                                  "repeats1 integer, "
                                  "weights1 real, "
                                  "repeats2 integer, "
                                  "weights2 real, "
                                  "repeats3 integer, "
                                  "weights3 real, "
                                  "repeats4 integer, "
                                  "weights4 real, "
                                  "repeats5 integer, "
                                  "weights5 real, "
                                  "repeats6 integer, "
                                  "weights6 real, "
                                  "comments varchar(160))").arg(tablename));

        qDebug() << query.lastError();


        if(ret1) {

            qDebug() << "table " << tablename << " created.";

            ret2 = query.exec(QString("INSERT INTO previousworkoutnames VALUES(NULL,'%1','%2',%3)")
                              .arg(workoutName_).arg(tablename).arg(date));

            qDebug() << query.lastError();

        }

        if(ret1 and ret2 and ret3) {

            previousWorkouts_ << workoutName_;
            previousWorkoutTableNames_ << tablename;
            context_->setContextProperty("previousWorkoutsModel",QVariant::fromValue(previousWorkouts_));
            ret = true;

            qDebug() << workoutName_ << " added to database.";
        }
    }
    return ret;
}

bool GymModel::updateExcercise() {

    bool ret = false;
    bool ret1 = false;
    bool ret2 = false;

    if(findExcerciseIndex()) {

        if (db_.isOpen()) {

            QSqlQuery query(db_);

            ret1 = query.exec(QString("UPDATE '%1' SET name = '%2' WHERE Id = %3;")
                              .arg(selectedMuscle_).arg(name_).arg(excerciseIndex_));
            qDebug() << query.lastError();

            ret2 = query.exec(QString("UPDATE '%1' SET description = '%2' WHERE Id = %3;")
                              .arg(selectedMuscle_).arg(description_).arg(excerciseIndex_));
            qDebug() << query.lastError();

            if(ret1 and ret2) ret = true;
        }
    }

    getExcercises();

    return ret;
}

QStringList GymModel::excerciseNames() {

    qDebug() << "names: " << excerciseNames_;
    return excerciseNames_;
}

void GymModel::addExcercise(QString excercise) {

    selectedExcercises_ << excercise;
    emit selectedExcercisesCountChanged();
    context_->setContextProperty("selectedExcercisesModel",QVariant::fromValue(selectedExcercises_));

    qDebug() << "excercise added.";
}

void GymModel::removeExcercise(QString excercise) {

    int index = selectedExcercises_.indexOf(excercise);
    if(index != -1 ) selectedExcercises_.removeAt(index);
    context_->setContextProperty("selectedExcercisesModel",QVariant::fromValue(selectedExcercises_));

    qDebug() << "after delete" << selectedExcercises_;
}

void GymModel::removeWorkout(QString excercise) {

    int index = workoutNames_.indexOf(excercise);
    if(index != -1 ) workoutNames_.removeAt(index);
    context_->setContextProperty("workoutsModel",QVariant::fromValue(workoutNames_));

    qDebug() << "after delete" << workoutNames_;
}

bool GymModel::isExcerciseSelected(QString excercise) {

    int index = selectedExcercises_.indexOf(excercise);
    if(index != -1) {
        return true;
    }

    return false;
}

void GymModel::setWorkoutName(QString workoutName) {

    workoutName_ = workoutName;
}

QString GymModel::getWorkoutName() {

    return workoutName_;
}

int GymModel::getSelectedExcercisesCount() {

    qDebug() << selectedExcercises_.size();
    return selectedExcercises_.size();
}

//QString GymModel::getExcerciseDescription() {

//    return excerciseDescription_;
//}

//QString GymModel::getEcerciseName() {

//    return excerciseName_;
//}

int GymModel::getExcerciseCount() {

    return excerciseCount_;
}

void GymModel::clean() {

    name_.clear();
    description_.clear();
    selectedMuscle_.clear();
    selectedExcercise_.clear();
    db_.close();
    excerciseNames_.clear();
    excerciseName_.clear();
    excerciseDescription_.clear();
    selectedExcercises_.clear();
    workoutName_.clear();
    excerciseCount_ = 0;
    series_.clear();
    repeats_.clear();
    weights_.clear();
    comments_.clear();
    excercises_.clear();
    delete context_;
    excerciseIndex_ = 0;
    workout_.clear();
    previousWorkouts_.clear();
    mode_.clear();
    coverExcerciseIndex_ = 0;
}

void GymModel::setContext(QQmlContext *context) {

    context_ = context;
}

void GymModel::clearSelectedExcercises() {

    workoutName_.clear();
    selectedExcercises_.clear();
    context_->setContextProperty("selectedExcercisesModel",QVariant::fromValue(selectedExcercises_));

}

bool GymModel::findExcerciseIndex() {

    int index = excerciseNames_.indexOf(selectedExcercise_);
    if(index != -1) {
        excerciseIndex_ = index+1; // Because database indexing starts from 1
        return true;
    }
    return false;
}

void GymModel::removeWorkoutExcercise(QString excercise) {

    int index = workout_.indexOf(excercise);
    if(index != -1 ) workout_.removeAt(index);
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));

    qDebug() << "after delete" << workout_;

}

void GymModel::clearWorkout() {

    workout_.clear();
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));
}

bool GymModel::findWorkoutExcerciseIndex(QString excerciseName) {

    int index = excerciseNames_.indexOf(excerciseName);

    qDebug() << "index of excercise: " << index;

    if(index != -1) {
        workoutExcerciseIndex_ = index+1; // Because database indexing starts from 1
        return true;
    }
    return false;
}

bool GymModel::findWorkoutIndex(QString workoutName) {

    qDebug() << workoutNames_;

    int index = workoutNames_.indexOf(workoutName);

    qDebug() << "index of " << workoutName << " is " << index;

    if(index != -1) {
        workoutIndex_ = index+1; // Because database indexing starts from 1
        return true;
    }
    return false;
}

int GymModel::getSeries(QString excerciseName) {

    int series = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get series of " << excerciseName << " from " << tablename;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT series FROM '%1' WHERE excercisename = '%2';").arg(tablename).arg(excerciseName));

            if(query.next()) series = query.value(1).toInt();
        }
    }

    return series;

}

void GymModel::setSeries(QString excercisename,int series) {

    qDebug() << "Setting series";

//    if(findWorkoutIndex(workoutName_)) {

//        int workoutIndex = workoutIndex_ - 1;
//        QString tablename = workoutTableNames_.at(workoutIndex);

//        findWorkoutExcerciseIndex(excercisename);

//        if(db_.isOpen()) {
//            QSqlQuery query(db_);
//            query.exec(QString("UPDATE '%1' SET series = '%2' WHERE ID = %3 ;")
//                       .arg(tablename).arg(series).arg(workoutExcerciseIndex_));

//        }
//    }
}

int GymModel::getRepeats(QString excerciseName, int currentSerie) {

    int repeats = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get repeats of " << excerciseName << " from " << tablename;

        QString serierepeats = "repeats";
        serierepeats = serierepeats + currentSerie;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT '%1' FROM '%2' WHERE excercisename = '%3';").arg(serierepeats).arg(tablename).arg(excerciseName));

            if(query.next()) repeats = query.value(1).toInt();
        }
    }

    return repeats;
}

void GymModel::setRepeats(QString excercisename, int repeats, int currentSerie) {

    qDebug() << "setting repeats";

//    QString serierepeats = "repeats";
//    serierepeats = serierepeats + currentSerie;

//    if(findWorkoutIndex(workoutName_)) {

//        int workoutIndex = workoutIndex_ - 1;
//        QString tablename = workoutTableNames_.at(workoutIndex);

//        findWorkoutExcerciseIndex(excercisename);

//        if(db_.isOpen()) {
//            QSqlQuery query(db_);
//            query.exec(QString("UPDATE '%1' SET '%2' = '%3' WHERE ID = %4 ;")
//                       .arg(tablename).arg(repeats).arg(serierepeats).arg(workoutExcerciseIndex_));

//        }
//    }
}

double GymModel::getWeights(QString excerciseName, int currentSerie) {

    double weights = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get weights of " << excerciseName << " from " << tablename;

        QString serieweights = "weights";
        serieweights = serieweights + currentSerie;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT '%1' FROM '%2' WHERE excercisename = '%3';").arg(serieweights).arg(tablename).arg(excerciseName));

            if(query.next()) weights = query.value(1).toDouble();
        }
    }

    return weights;
}

void GymModel::setWeights(QString excercisename, double weights, int currentSerie) {

    qDebug() << "setting weights";

//    QString serieweights = "weights";
//    serieweights = serieweights + currentSerie;

//    if(findWorkoutIndex(workoutName_)) {

//        int workoutIndex = workoutIndex_ - 1;
//        QString tablename = workoutTableNames_.at(workoutIndex);

//        findWorkoutExcerciseIndex(excercisename);

//        if(db_.isOpen()) {
//            QSqlQuery query(db_);
//            query.exec(QString("UPDATE '%1' SET '%2' = '%3' WHERE ID = %4 ;")
//                       .arg(tablename).arg(weights).arg(serieweights).arg(workoutExcerciseIndex_));

//        }
//    }
}

QString GymModel::getComments(QString excerciseName) {

    QString comments = "";

//    if(findWorkoutIndex(workoutName_)) {

//        int workoutIndex = workoutIndex_ - 1;
//        QString tablename = workoutTableNames_.at(workoutIndex);

//        qDebug() << "get comments of " << excerciseName << " from " << tablename;

//        if(db_.isOpen()) {
//            QSqlQuery query(db_);
//            query.exec(QString("SELECT comments FROM '%1 WHERE excercisename = '%2';").arg(tablename).arg(excerciseName));
//            if(query.next()) comments = query.value(1).toString();
//        }
//    }

    return comments;
}

void GymModel::setComments(QString excercisename, QString comments) {

    qDebug() << "setting comments";

//    if(findWorkoutIndex(workoutName_)) {

//        int workoutIndex = workoutIndex_ - 1;
//        QString tablename = workoutTableNames_.at(workoutIndex);

//        findWorkoutExcerciseIndex(excercisename);

//        if(db_.isOpen()) {
//            QSqlQuery query(db_);
//            query.exec(QString("UPDATE '%1' SET comments = '%2' WHERE ID = %3 ;")
//                       .arg(tablename).arg(comments).arg(workoutExcerciseIndex_));

//        }
//    }
}

QString GymModel::nextCoverExcercise() {

    QString text = "Done";

    if(coverExcerciseIndex_ < workout_.size()) {

        if(coverExcerciseIndex_ == 0) {
            text = workout_.at(0);

        } else {
            text = workout_.at(coverExcerciseIndex_ - 1);
            ++coverExcerciseIndex_;
        }
    }
    return text;
}

QString GymModel::previousCoverExcercise() {

    if(workout_.size() == 0) return "Done";

    if(coverExcerciseIndex_ > 0) {
        --coverExcerciseIndex_;
        return workout_.at(coverExcerciseIndex_);
    } else {
        coverExcerciseIndex_ = 0;
    }
    return "Wrong way";
}

void GymModel::increaseCurrentSeriesIndex() {

    ++currentSeriesIndex_;
    emit currentSeriesIndexChanged();
}

void GymModel::decreaseCurrentSeriesIndex() {

    --currentSeriesIndex_;
    emit currentSeriesIndexChanged();
}

int GymModel::getCurrentSeriesIndex() {

    return currentSeriesIndex_;
}
