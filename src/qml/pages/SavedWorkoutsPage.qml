import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    PageHeader {
        id: header
        title: "Saved Workouts"
    }

    SilicaListView {
        id: list
        width: 540
        height: 960
        anchors.top: parent.top
        anchors.topMargin: 200

        model: workoutsModel
        delegate: TextSwitch {
            text: modelData
            checked: false
            onClicked: {
                GymModel.getWorkout(text)
                pageStack.push(Qt.resolvedUrl("ShowWorkoutPage.qml"))
                checked = false
            }

            onPressAndHold: {

            }

        }

        ViewPlaceholder {
            enabled: list.count === 0
            text: "No workouts yet."
            anchors.centerIn: list
        }

        ScrollDecorator { }

    }
}
