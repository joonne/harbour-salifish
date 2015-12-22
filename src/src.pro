TEMPLATE=app
# The name of your app binary (and it's better if you think it is the whole app name as it's referred to many times)
# Must start with "harbour-"
TARGET = harbour-salifish

# In the bright future this config line will do a lot of stuff to you
CONFIG += sailfishapp

QT += sql

SOURCES += main.cpp \
    user.cpp \
    gymmodel.cpp \
    databasemanager.cpp \
    workoutmodel/excercisemodel.cpp \
    workoutmodel/excercisedata.cpp

OTHER_FILES = \
# You DO NOT want .yaml be listed here as Qt Creator's editor is completely not ready for multi package .yaml's
#
# Also Qt Creator as of Nov 2013 will anyway try to rewrite your .yaml whenever you change your .pro
# Well, you will just have to restore .yaml from version control again and again unless you figure out
# how to kill this particular Creator's plugin
#    ../rpm/harbour-salifish.yaml \
    ../rpm/harbour-salifish.spec \
    qml/main.qml \
    qml/pages/WorkoutPage.qml \
    qml/pages/ShowWorkoutPage.qml \
    qml/pages/ShowDescriptionPage.qml \
    qml/pages/SettingsPage.qml \
    qml/pages/SavedWorkoutsPage.qml \
    qml/pages/ProfilePage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/ExcercisePage.qml \
    qml/pages/EditWorkoutPage.qml \
    qml/pages/CreateWorkoutPage.qml \
    qml/pages/AddNewExcercise.qml \
    qml/pages/AboutPage.qml \
    qml/cover/CoverPage.qml

INCLUDEPATH += $$PWD

HEADERS += \
    user.h \
    gymmodel.h \
    databasemanager.h \
    workoutmodel/excercisemodel.h \
    workoutmodel/excercisedata.h
