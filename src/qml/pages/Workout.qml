import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: workoutItem
    height: workoutView.height;
    width: workoutView.width;

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: column
            spacing: Theme.paddingLarge
            anchors.centerIn: parent

            Row {
                id: seriesrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - seriesrow.width) / 2
                }
                spacing: Theme.paddingLarge

                Image {
                    source: "image://theme/icon-m-remove"
                }

                Label {
                    text: qsTr("Series")
                }

                Label {
                    text: "1/3"
                }

                Image {
                    source: "image://theme/icon-m-add"
                }

            }

            Row {
                id: excerciserow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - excerciserow.width) / 2
                }

                Label {
                    text: "Bench Press"
                }
            }

            Row {
                id: weightsrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - weightsrow.width) / 2
                }

                Label {
                    text: qsTr("Weights")
                }

            }

            Row {
                id: changesweightsrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - changesweightsrow.width) / 2
                }
                spacing: Theme.paddingLarge

                Image {
                    source: "image://theme/icon-m-remove"
                }

                Label {
                    text: "80 kg"
                }

                Image {
                    source: "image://theme/icon-m-add"
                }
            }

            Button {
                id: next
                text: "NEXT"
                onClicked: console.log("NEXT EXCERCISE")
                anchors {
                    left: parent.left
                    leftMargin: (workoutView.width - next.width) / 2
                }
            }
        }
    }
}

