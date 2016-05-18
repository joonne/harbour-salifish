import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: editworkoutpage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                id: savebutton
                text: qsTr("Save")
                onClicked: {
                    //GymModel.setWorkoutName(workoutname.text)
                    //GymModel.createWorkout()
                    //GymModel.insertWorkoutExcercises()
                }
            }
        }

        Column {
            id: column
            anchors.fill: parent

            PageHeader {
                title: qsTr("Save workout")
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
        }
    }
}
