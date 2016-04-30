import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: workoutStatusItem
    height: workoutView.height;
    width: workoutView.width;

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: column
            spacing: Theme.paddingLarge

            ProgressCircleBase {

                property real weights: 60

                id: kgcircle
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - width) / 2
                height: width
                value: (60.0 / 1500) * 100
                borderWidth: 3
                progressColor: Theme.highlightColor

                Column {
                    width: parent.width * 0.7
                    anchors.centerIn: parent

                    property real topVal: kgcircle.weights
                    property real botVal: kgcircle.value

                    property string topUnit : "kg"
                    property string botUnit : "%"

                    Text {
                        width: parent.width
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeLarge
                        horizontalAlignment: Text.AlignHCenter
                        text: "60kg"
                    }

                    Rectangle {
                        color: Theme.highlightColor
                        width: parent.width
                        height: 2
                        opacity: 0.4
                    }

                    Text {
                        width: parent.width
                        color: Theme.highlightColor
                        opacity: 0.6
                        font.pixelSize: Theme.fontSizeLarge
                        horizontalAlignment: Text.AlignHCenter
                        text: "1500kg"
                    }
                }
               }

            ProgressCircleBase {

                property real weights: 60

                id: timecircle
                width: parent.width
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - width) / 2
                height: width
                value: (40/123.0)*100.0
                borderWidth: 3
                progressColor: Theme.highlightColor

                Column {
                    width: parent.width * 0.7
                    anchors.centerIn: parent

                    property real topVal: kgcircle.weights
                    property real botVal: kgcircle.value

                    property string topUnit : "min"
                    property string botUnit : "min"

                    Text {
                        width: parent.width
                        color: Theme.highlightColor
                        font.pixelSize: Theme.fontSizeLarge
                        horizontalAlignment: Text.AlignHCenter
                        text: "40min"
                    }

                    Rectangle {
                        color: Theme.highlightColor
                        width: parent.width
                        height: 2
                        opacity: 0.4
                    }

                    Text {
                        width: parent.width
                        color: Theme.highlightColor
                        opacity: 0.6
                        font.pixelSize: Theme.fontSizeLarge
                        horizontalAlignment: Text.AlignHCenter
                        text: "123min"
                    }
                }
               }

            Row {
                id: seriesrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutStatusItem.width - seriesrow.width) / 2
                }

                Label {
                    text: "4 series to go"
                }
            }
        }
    }
}

