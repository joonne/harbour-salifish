#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QScopedPointer>
#include <QQuickView>
#include <QQmlEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <gymmodel.h>
#include <user.h>
#include <userdatabasemanager.h>
#include <gymdatabasemanager.h>
#include <QStandardPaths>
#include <QDebug>

int main(int argc, char *argv[])
{
    // For this example, wizard-generates single line code would be good enough,
    // but very soon it won't be enough for you anyway, so use this more detailed example from start
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    GymDatabase* gymDB = new GymDatabase();
    //gymDB->setUpDB();

    UserDatabase* userDB = new UserDatabase();
    //userDB->setUpDB();

    User* user = new User();
    if(user->openDB()) user->getUser();

    GymModel* model = new GymModel();
    model->openDB();

    QQmlContext *context = view->engine()->rootContext();
    context->setContextProperty("User", user);
    context->setContextProperty("GymModel", model);
    model->setContext(context);
    model->getPreviousWorkouts();

    //    Here's how you will add QML components whenever you start using them
    //    Check https://github.com/amarchen/Wikipedia for a more full example
    //    view->engine()->addImportPath(SailfishApp::pathTo("qml/components").toString());
    view->setSource(SailfishApp::pathTo("qml/main.qml"));

    view->showFullScreen();

    app->exec();

    delete userDB;
    delete gymDB;
    delete user;
    delete model;
}
