import QtQuick 2.0
import Sailfish.Silica 1.0
//import harbour.salifish 1.0

Page {
    id: page

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

            SectionHeader {
                anchors.left: parent.left
                anchors.leftMargin: 20
                text: qsTr("Recent Workouts")
//                visible: listView.count !== 0
            }

//            SilicaListView {
//                id: listView
//                width: parent.width
//                height: parent.height
//                spacing: Theme.paddingLarge

//                ViewPlaceholder {
//                    enabled: listview.count === 0
//                    text: qsTr("Completed workouts will appear here.")
//                    anchors.centerIn: listview
//                }
//            }
        }
    }
}

