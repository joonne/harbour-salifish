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

QString GymModel::getExerciseName() {

    return exerciseName_;
}

QString GymModel::getDescription() {

    return description_;
}

QString GymModel::getExerciseDescription() {

    return exerciseDescription_;
}

QString GymModel::getSelectedMuscle() {

    return selectedMuscle_;
}

QString GymModel::getSelectedExercise() {

    return selectedExercise_;
}

QString GymModel::getMode() {
    return mode_;
}

void GymModel::setName(QString exerciseName) {

    if(exerciseName != name_ and exerciseName != "") {
        name_ = exerciseName;
        emit nameChanged();
    }
}

void GymModel::setExerciseName(QString exerciseName) {

    exerciseName_ = exerciseName;
    emit exerciseNameChanged();
}

void GymModel::setDescription(QString description) {

    if(description != description_ and description != "") {
        description_ = description;
        emit DescriptionChanged();
    }
}

void GymModel::setExerciseDescription(QString exerciseDescription) {

    exerciseDescription_ = exerciseDescription;
    emit exerciseDescriptionChanged();
}

void GymModel::setSelectedMuscle(QString selectedMuscle) {

    selectedMuscle_ = selectedMuscle;
    emit SelectedMuscleChanged();
}

void GymModel::setSelectedExercise(QString selectedExercise) {

    selectedExercise_ = selectedExercise;
    emit SelectedExerciseChanged();
}

void GymModel::setMode(QString mode) {

    mode_ = mode;
    emit modeChanged();
}

bool GymModel::getExercises() {

    exerciseNames_.clear();
    exerciseCount_ = 0;

    bool ret = false;

    if(db_.isOpen()) {

        qDebug() << "Tietokannan avaaminen onnistui.";

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM '%1';").arg(selectedMuscle_.toLower()));
        qDebug() << query.lastError();

        while(query.next()) {

            exerciseNames_ << query.value(1).toString();
            ++exerciseCount_;

        }

        qDebug() << exerciseNames_;
    }

    context_->setContextProperty("exerciseNamesModel",QVariant::fromValue(exerciseNames_));
    return ret;
}

bool GymModel::getWorkouts() {

    workoutNames_.clear();
    workoutTableNames_.clear();

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
    exercises_.clear();
    exerciseNames_.clear();
    series_.clear();
    repeats_.clear();
    weights_.clear();
    comments_.clear();
    coverExerciseIndex_ = 0;

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

            exercises_ << query.value(1).toString() + "         " + query.value(2).toString() + " x " +
                           query.value(3).toString() + " x " + query.value(4).toString() + " kg";

            exerciseNames_ << query.value(1).toString();
            series_ << query.value(2).toString();
            repeats_ << query.value(3).toString();
            weights_ << query.value(4).toString();
            comments_ << query.value(5).toString();

        }
    }

    workout_ = exerciseNames_;
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));
    context_->setContextProperty("exerciseNamesModel",QVariant::fromValue(exerciseNames_));
    context_->setContextProperty("seriesModel",QVariant::fromValue(series_));
    context_->setContextProperty("repeatsModel",QVariant::fromValue(repeats_));
    context_->setContextProperty("weightsModel",QVariant::fromValue(weights_));
    context_->setContextProperty("exercisesModel",QVariant::fromValue(exercises_));
    context_->setContextProperty("selectedExercisesModel",QVariant::fromValue(exerciseNames_));


    return ret;

}

bool GymModel::getExercise(QString exercise) {

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("SELECT * FROM '%1' WHERE name = '%2'").arg(selectedMuscle_.toLower()).arg(exercise));
        qDebug() << query.lastError();

        if(query.next()) {

            setExerciseName(query.value(1).toString());
            setExerciseDescription(query.value(2).toString());
        }
    }

    return ret;
}

bool GymModel::insertExerciseName(QString exerciseName) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2');").arg(selectedMuscle_).arg(exerciseName));
        qDebug() << query.lastError();

    }
    return ret;
}

bool GymModel::insertExerciseDescription(QString description) {

    bool ret = false;

    if (db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2');").arg(selectedMuscle_).arg(description));
        qDebug() << query.lastError();

    }
    return ret;
}

bool GymModel::insertExercise() {

    bool ret = false;

    if(db_.isOpen()) {

        QSqlQuery query(db_);
        ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2','%3');")
                         .arg(selectedMuscle_.toLower()).arg(name_).arg(description_));
    }

    exerciseNames_ << name_;
    context_->setContextProperty("exerciseNamesModel",QVariant::fromValue(exerciseNames_));


    return ret;
}

bool GymModel::insertWorkoutExercises() {

    bool ret = false;

    for(int i = 0; i < selectedExercises_.size(); ++i) {

        qDebug() << "adding " << selectedExercises_.at(i) << " to " << workoutName_;
        QString exercise = selectedExercises_.at(i);

        if(db_.isOpen()) {

            QSqlQuery query(db_);
            ret = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2',%3,%4,%5,'%6');")
                             .arg(workoutName_).arg(exercise)
                             .arg(3).arg(12).arg(70));
            qDebug() << query.lastError();
        }
    }

    return ret;
}

// Finds and deletes an exercise from the database.
bool GymModel::deleteExerciseFromDB() {

    bool ret = false;

    getExercises();
    if(findExerciseIndex()) {

        if(db_.isOpen()) {

            QSqlQuery query(db_);
            ret = query.exec(QString("DELETE FROM '%1' WHERE ID = %2").arg(selectedMuscle_).arg(exerciseIndex_));
        }

        if(ret) {
            removeExercise(selectedExercise_);
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
                                  "exercisename varchar(50), "
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

            for( int i = 0; i < selectedExercises_.size(); ++i ) {

                ret3 = query.exec(QString("INSERT INTO '%1' VALUES(NULL,'%2',%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15)")
                                  .arg(workoutName_)
                                  .arg(selectedExercises_.at(i))
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
                                  "exercisename varchar(50), "
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

bool GymModel::updateExercise() {

    bool ret = false;
    bool ret1 = false;
    bool ret2 = false;

    if(findExerciseIndex()) {

        if (db_.isOpen()) {

            QSqlQuery query(db_);

            ret1 = query.exec(QString("UPDATE '%1' SET name = '%2' WHERE Id = %3;")
                              .arg(selectedMuscle_).arg(name_).arg(exerciseIndex_));
            qDebug() << query.lastError();

            ret2 = query.exec(QString("UPDATE '%1' SET description = '%2' WHERE Id = %3;")
                              .arg(selectedMuscle_).arg(description_).arg(exerciseIndex_));
            qDebug() << query.lastError();

            if(ret1 and ret2) ret = true;
        }
    }

    getExercises();

    return ret;
}

QStringList GymModel::exerciseNames() {

    qDebug() << "names: " << exerciseNames_;
    return exerciseNames_;
}

void GymModel::addExercise(QString exercise) {

    selectedExercises_ << exercise;
    emit selectedExercisesCountChanged();
    context_->setContextProperty("selectedExercisesModel",QVariant::fromValue(selectedExercises_));

    qDebug() << "exercise added.";
}

void GymModel::removeExercise(QString exercise) {

    int index = selectedExercises_.indexOf(exercise);
    if(index != -1 ) selectedExercises_.removeAt(index);
    context_->setContextProperty("selectedExercisesModel",QVariant::fromValue(selectedExercises_));

    qDebug() << "after delete" << selectedExercises_;
}

void GymModel::removeWorkout(QString exercise) {

    int index = workoutNames_.indexOf(exercise);
    if(index != -1 ) workoutNames_.removeAt(index);
    context_->setContextProperty("workoutsModel",QVariant::fromValue(workoutNames_));

    qDebug() << "after delete" << workoutNames_;
}

bool GymModel::isExerciseSelected(QString exercise) {

    int index = selectedExercises_.indexOf(exercise);
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

int GymModel::getSelectedExercisesCount() {

    qDebug() << selectedExercises_.size();
    return selectedExercises_.size();
}

//QString GymModel::getExerciseDescription() {

//    return exerciseDescription_;
//}

//QString GymModel::getEcerciseName() {

//    return exerciseName_;
//}

int GymModel::getExerciseCount() {

    return exerciseCount_;
}

void GymModel::clean() {

    name_.clear();
    description_.clear();
    selectedMuscle_.clear();
    selectedExercise_.clear();
    db_.close();
    exerciseNames_.clear();
    exerciseName_.clear();
    exerciseDescription_.clear();
    selectedExercises_.clear();
    workoutName_.clear();
    exerciseCount_ = 0;
    series_.clear();
    repeats_.clear();
    weights_.clear();
    comments_.clear();
    exercises_.clear();
    delete context_;
    exerciseIndex_ = 0;
    workout_.clear();
    previousWorkouts_.clear();
    mode_.clear();
    coverExerciseIndex_ = 0;
}

void GymModel::setContext(QQmlContext *context) {

    context_ = context;
}

void GymModel::clearSelectedExercises() {

    workoutName_.clear();
    selectedExercises_.clear();
    context_->setContextProperty("selectedExercisesModel",QVariant::fromValue(selectedExercises_));

}

bool GymModel::findExerciseIndex() {

    int index = exerciseNames_.indexOf(selectedExercise_);
    if(index != -1) {
        exerciseIndex_ = index+1; // Because database indexing starts from 1
        return true;
    }
    return false;
}

void GymModel::removeWorkoutExercise(QString exercise) {

    int index = workout_.indexOf(exercise);
    if(index != -1 ) workout_.removeAt(index);
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));

    qDebug() << "after delete" << workout_;

}

void GymModel::clearWorkout() {

    workout_.clear();
    context_->setContextProperty("workoutModel",QVariant::fromValue(workout_));
}

bool GymModel::findWorkoutExerciseIndex(QString exerciseName) {

    int index = exerciseNames_.indexOf(exerciseName);

    qDebug() << "index of exercise: " << index;

    if(index != -1) {
        workoutExerciseIndex_ = index+1; // Because database indexing starts from 1
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

int GymModel::getSeries(QString exerciseName) {

    int series = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get series of " << exerciseName << " from " << tablename;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT series FROM '%1' WHERE exercisename = '%2';").arg(tablename).arg(exerciseName));

            if(query.next()) series = query.value(1).toInt();
        }
    }

    return series;

}

void GymModel::setSeries(QString exercisename,int series) {

    qDebug() << "Setting series";

    //    if(findWorkoutIndex(workoutName_)) {

    //        int workoutIndex = workoutIndex_ - 1;
    //        QString tablename = workoutTableNames_.at(workoutIndex);

    //        findWorkoutExerciseIndex(exercisename);

    //        if(db_.isOpen()) {
    //            QSqlQuery query(db_);
    //            query.exec(QString("UPDATE '%1' SET series = '%2' WHERE ID = %3 ;")
    //                       .arg(tablename).arg(series).arg(workoutExerciseIndex_));

    //        }
    //    }
}

int GymModel::getRepeats(QString exerciseName, int currentSerie) {

    int repeats = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get repeats of " << exerciseName << " from " << tablename;

        QString serierepeats = "repeats";
        serierepeats = serierepeats + currentSerie;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT '%1' FROM '%2' WHERE exercisename = '%3';").arg(serierepeats).arg(tablename).arg(exerciseName));

            if(query.next()) repeats = query.value(1).toInt();
        }
    }

    return repeats;
}

void GymModel::setRepeats(QString exercisename, int repeats, int currentSerie) {

    qDebug() << "setting repeats";

    //    QString serierepeats = "repeats";
    //    serierepeats = serierepeats + currentSerie;

    //    if(findWorkoutIndex(workoutName_)) {

    //        int workoutIndex = workoutIndex_ - 1;
    //        QString tablename = workoutTableNames_.at(workoutIndex);

    //        findWorkoutExerciseIndex(exercisename);

    //        if(db_.isOpen()) {
    //            QSqlQuery query(db_);
    //            query.exec(QString("UPDATE '%1' SET '%2' = '%3' WHERE ID = %4 ;")
    //                       .arg(tablename).arg(repeats).arg(serierepeats).arg(workoutExerciseIndex_));

    //        }
    //    }
}

double GymModel::getWeights(QString exerciseName, int currentSerie) {

    double weights = 1;

    if(findWorkoutIndex(workoutName_)) {

        int workoutIndex = workoutIndex_ - 1;
        QString tablename = workoutTableNames_.at(workoutIndex);

        qDebug() << "get weights of " << exerciseName << " from " << tablename;

        QString serieweights = "weights";
        serieweights = serieweights + currentSerie;

        if(db_.isOpen()) {
            QSqlQuery query(db_);
            query.exec(QString("SELECT '%1' FROM '%2' WHERE exercisename = '%3';").arg(serieweights).arg(tablename).arg(exerciseName));

            if(query.next()) weights = query.value(1).toDouble();
        }
    }

    return weights;
}

void GymModel::setWeights(QString exercisename, double weights, int currentSerie) {

    qDebug() << "setting weights";

    //    QString serieweights = "weights";
    //    serieweights = serieweights + currentSerie;

    //    if(findWorkoutIndex(workoutName_)) {

    //        int workoutIndex = workoutIndex_ - 1;
    //        QString tablename = workoutTableNames_.at(workoutIndex);

    //        findWorkoutExerciseIndex(exercisename);

    //        if(db_.isOpen()) {
    //            QSqlQuery query(db_);
    //            query.exec(QString("UPDATE '%1' SET '%2' = '%3' WHERE ID = %4 ;")
    //                       .arg(tablename).arg(weights).arg(serieweights).arg(workoutExerciseIndex_));

    //        }
    //    }
}

QString GymModel::getComments(QString exerciseName) {

    QString comments = "";

    //    if(findWorkoutIndex(workoutName_)) {

    //        int workoutIndex = workoutIndex_ - 1;
    //        QString tablename = workoutTableNames_.at(workoutIndex);

    //        qDebug() << "get comments of " << exerciseName << " from " << tablename;

    //        if(db_.isOpen()) {
    //            QSqlQuery query(db_);
    //            query.exec(QString("SELECT comments FROM '%1 WHERE exercisename = '%2';").arg(tablename).arg(exerciseName));
    //            if(query.next()) comments = query.value(1).toString();
    //        }
    //    }

    return comments;
}

void GymModel::setComments(QString exercisename, QString comments) {

    qDebug() << "setting comments";

    //    if(findWorkoutIndex(workoutName_)) {

    //        int workoutIndex = workoutIndex_ - 1;
    //        QString tablename = workoutTableNames_.at(workoutIndex);

    //        findWorkoutExerciseIndex(exercisename);

    //        if(db_.isOpen()) {
    //            QSqlQuery query(db_);
    //            query.exec(QString("UPDATE '%1' SET comments = '%2' WHERE ID = %3 ;")
    //                       .arg(tablename).arg(comments).arg(workoutExerciseIndex_));

    //        }
    //    }
}

QString GymModel::nextCoverExercise() {

    QString text = "Done";

    if(coverExerciseIndex_ < workout_.size()) {

        if(coverExerciseIndex_ == 0) {
            text = workout_.at(0);

        } else {
            text = workout_.at(coverExerciseIndex_ - 1);
            ++coverExerciseIndex_;
        }
    }
    return text;
}

QString GymModel::previousCoverExercise() {

    if(workout_.size() == 0) return "Done";

    if(coverExerciseIndex_ > 0) {
        --coverExerciseIndex_;
        return workout_.at(coverExerciseIndex_);
    } else {
        coverExerciseIndex_ = 0;
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
