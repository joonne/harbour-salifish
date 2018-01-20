import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {


            MenuItem {
                text: "Delete"
                onClicked: {
                    GymModel.deleteWorkoutFromDB(header.title)
                    pageStack.pop()
                }
            }

            MenuItem {
                text: "Edit"
                onClicked: {
                    GymModel.getWorkout(header.title)
                    //pageStack.pop(PageStackAction.Immediate)
                    //pageStack.pop(PageStackAction.Immediate)
                    //pageStack.push(Qt.resolvedUrl("CreateWorkout.qml"),PageStackAction.Immediate)
                    pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
                    //pageStack.replaceAbove(Qt.resolvedUrl("FirstPage.qml"), Qt.resolvedUrl("CreateWorkoutPage.qml"))
                }
            }

            MenuItem {
                text: "Select"
                onClicked: {
                    GymModel.Mode = "workout"
                    pageStack.push(Qt.resolvedUrl("WorkoutPage.qml"))
                }
            }
        }

        PageHeader {
            id: header
            title: GymModel.getWorkoutName()
        }

        SilicaListView {
            width: 540
            height: 960
            anchors.top: parent.top
            anchors.topMargin: 200

            model: exercisesModel
            delegate: TextField {
                text: modelData
                readOnly: true
            }
        }
    }
}
