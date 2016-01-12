import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: workoutstartpage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                text: qsTr("Start")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("WorkoutViewPage.qml"))
                }
            }
        }

        PageHeader {
            id: header
            title: "Rinta 1"
        }

        Column {
            id: column
            spacing: Theme.paddingLarge
            anchors {
                top: header.bottom
                topMargin: 5 * Theme.paddingMedium
            }

            Label {
                id: muscles
                text: "4 muscle groups"
                font.pixelSize: Theme.fontSizeLarge
                anchors {
                    left: parent.left
                    leftMargin: (workoutstartpage.width - muscles.width) / 2
                }
            }

            Label {
                id: excercises
                text: "12 excercises"
                font.pixelSize: Theme.fontSizeLarge
                anchors {
                    left: parent.left
                    leftMargin: (workoutstartpage.width - excercises.width) / 2
                }
            }

            Label {
                id: weights
                text: "1800 kg"
                font.pixelSize: Theme.fontSizeLarge
                anchors {
                    left: parent.left
                    leftMargin: (workoutstartpage.width - weights.width) / 2
                }
            }

            Label {
                id: time
                text: "Estimated Time 2h 15min"
                font.pixelSize: Theme.fontSizeLarge
                anchors {
                    left: parent.left
                    leftMargin: (workoutstartpage.width - time.width) / 2
                }
            }
        }
    }
}
