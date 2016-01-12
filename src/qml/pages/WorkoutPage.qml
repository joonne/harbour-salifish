import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: workoutpage

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {

            MenuItem {
                text: "Mark all as done"
                onClicked: {
                    GymModel.clearWorkout()
                }
            }
        }

        PageHeader {
            title: GymModel.getWorkoutName()
        }

        SilicaListView {
            id: workout
            width: 540
            height: 960
            anchors.top: parent.top
            anchors.topMargin: 200

            model: workoutModel
            delegate: TextSwitch {
                id: excercise
                text: modelData
                onClicked: {
                    //GymModel.insertDoneExcercise(excercise.text)
                    GymModel.removeWorkoutExcercise(text)
                }

            }

            ViewPlaceholder {
                text: qsTr("All done for now, remember to stretch and recover properly.")
                enabled: workout.count === 0
                anchors.centerIn: workout
            }
        }
    }
}
