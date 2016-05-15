import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {

            MenuItem {
                text: qsTr("About")
                onClicked: {
                    //GymModel.Mode = "normal"
                    pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Select a Workout")
                onClicked: {
                    //GymModel.Mode = "normal"
                    //GymModel.getWorkouts()
                    pageStack.push(Qt.resolvedUrl("SavedWorkoutsPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Create a new Workout")
                onClicked: {
                    //GymModel.Mode = "normal"
                    //GymModel.clearSelectedExcercises()
                    pageStack.push(Qt.resolvedUrl("CreateWorkoutPage.qml"))
                }
            }

            //            MenuItem {
            //                text: qsTr("Settings")
            //                onClicked: {
            //                    //GymModel.Mode = "normal"
            //                    pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
            //                }
            //            }

            MenuItem {
                text: qsTr("Profile")
                onClicked: {
                    //GymModel.Mode = "normal"
                    pageStack.push(Qt.resolvedUrl("ProfilePage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Start Workout")
                onClicked: pageStack.push(Qt.resolvedUrl("WorkoutStartPage.qml"))
            }
        }

        Column {
            id: column
            width: parent.width

            PageHeader {
                title: "SaliFish"
            }

            Label {
                id: label
                anchors.left: parent.left
                anchors.leftMargin: 20
                text: qsTr("Choose action from pulldown menu")
                color: Theme.secondaryColor
                font.pixelSize: Theme.fontSizeMedium
            }

            SectionHeader {
                anchors.left: parent.left
                anchors.leftMargin: 20
                text: qsTr("Recent Workouts")
            }

            SilicaListView {
                width: parent.width
                height: parent.height

                model: 2

                delegate: Label {
                    text: "PENKKIHAUKKA"
                }
            }
        }
    }
}

