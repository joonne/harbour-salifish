import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: workoutItem
    height: workoutView.height;
    width: workoutView.width;

    property int series: 1
    property int seriesFull: 1
    property double weights: 80

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: column
            anchors {
                top: parent.top
                topMargin: 5 * Theme.paddingLarge
            }
            spacing: Theme.paddingLarge

            Row {
                id: exerciserow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - exerciserow.width) / 2
                }

                Label {
                    text: "Bench Press"
                    font.pixelSize: Theme.fontSizeHuge
                }
            }

            Row {
                id: seriesrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - seriesrow.width) / 2
                }
                spacing: Theme.paddingLarge

                Image {
                    source: "image://theme/icon-m-remove"
                    BackgroundItem {
                        anchors.fill: parent
                        onClicked: series -= 1
                    }
                }

                Label {
                    text: qsTr("Series")
                    font.pixelSize: Theme.fontSizeHuge
                }

                Label {
                    text: "1/" + series
                    font.pixelSize: Theme.fontSizeHuge
                }

                Image {
                    source: "image://theme/icon-m-add"
                    BackgroundItem {
                        anchors.fill: parent
                        onClicked: series += 1
                    }
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
                    font.pixelSize: Theme.fontSizeHuge
                }
            }

            Row {
                id: changesweightsrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutItem.width - changesweightsrow.width) / 2
                }
                spacing: Theme.paddingLarge

//                Slider {
//                    id: weightSlider
//                    width: parent.width
//                    minimumValue: 1
//                    maximumValue: 500
//                    value: 80
//                    valueText: value + " kg"
//                }

                Image {
                    source: "image://theme/icon-m-remove"
                    BackgroundItem {
                        anchors.fill: parent
                        onClicked: weights -= 0.25
                    }
                }

                Label {
                    text: weights
                    font.pixelSize: Theme.fontSizeHuge
                }

                Image {
                    source: "image://theme/icon-m-add"
                    BackgroundItem {
                        anchors.fill: parent
                        onClicked: weights += 0.25
                    }
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

