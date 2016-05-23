import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

Page {
    id: page

    Component.onCompleted: {
        var model = ["Chest 23.05.2016 670kcal", "Legs 25.05.2016 800kcal"];
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {

            MenuItem {
                text: qsTr("About")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Select a Workout")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("SavedWorkoutsPage.qml"))
                }
            }
            MenuItem {
                text: qsTr("Create a new Workout")
                onClicked: {
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
                anchors.leftMargin: Theme.paddingLarge
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
                spacing: Theme.paddingLarge

                model: model

                delegate: Label {
                    text: modelData
                    anchors {
                        left: parent.left
                        leftMargin: Theme.paddingLarge
                    }
                }
            }
        }
    }
}

