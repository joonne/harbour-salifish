import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {

            MenuItem {
                text: "About SaliFish"
                onClicked: {
                    //GymModel.Mode = "normal"
                    pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                }
            }
            MenuItem {
                text: "Select a Workout"
                onClicked: {
                    //GymModel.Mode = "normal"
                    //GymModel.getWorkouts()
                    pageStack.push(Qt.resolvedUrl("SavedWorkoutsPage.qml"))
                }
            }
            MenuItem {
                text: "Create a new Workout"
                onClicked: {
                    //GymModel.Mode = "normal"
                    //GymModel.clearSelectedExcercises()
                    pageStack.push(Qt.resolvedUrl("CreateWorkoutPage.qml"))
                }
            }
            MenuItem {
                text: "Settings"
                onClicked: {
                    //GymModel.Mode = "normal"
                    pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
                }
            }
            MenuItem {
                text: "Profile"
                onClicked: {
                    //GymModel.Mode = "normal"
                    pageStack.push(Qt.resolvedUrl("ProfilePage.qml"))
                }
            }
            MenuItem {
                text: "Start Workout"
                onClicked: pageStack.push(Qt.resolvedUrl("WorkoutStartPage.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: parent.height

        PageHeader {
            title: "SaliFish"
        }

        Label {
            id: label
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 120
            text: qsTr("Choose action from pulldown menu")
            color: Theme.secondaryColor
            font.pixelSize: Theme.fontSizeMedium
        }

        SectionHeader {
            anchors.top: label.bottom
            anchors.topMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 20
            text: qsTr("Recent Workouts")
        }

        SilicaListView {
            width: 540
            height: 960
            anchors.top: parent.top
            anchors.topMargin: 270
            //anchors.bottom: parent.bottom
            //spacing: Theme.paddingSmall

            model: 2

            delegate: TextField {
                text: "PENKKIHAUKKA"
                readOnly: true
            }
        }
    }
}

