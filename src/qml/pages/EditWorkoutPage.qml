import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: editworkoutpage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                text: qsTr("Save as a template")
                onClicked: controller.workoutModel.saveWorkoutTemplate(workoutName.text)
            }

            MenuItem {
                text: qsTr("I did this already")
                onClicked: controller.workoutModel.saveWorkout(workoutName.text)
            }
        }

        Column {
            id: column
            anchors.fill: parent

            PageHeader {
                title: qsTr("Save Workout")
            }

            TextField {
                id: workoutName
                anchors {
                    left: column.left
                    leftMargin: Theme.paddingLarge
                }
                placeholderText: qsTr("New workout")
                label: qsTr("Workout name")
                width: column.width
            }

            Label {
                id: totalWeights
                anchors {
                    left: column.left
                    leftMargin: (column.width - totalWeights.width) / 2
                }
                text: qsTr("%1 kg").arg(controller.workoutModel.calculateTotalWeights())
            }

            Label {
                id: time
                anchors {
                    left: column.left
                    leftMargin: (column.width - time.width) / 2
                }
                text: qsTr("%1 minutes").arg(controller.workoutModel.calculateDuration(controller.user.pause))
            }
        }
    }
}
