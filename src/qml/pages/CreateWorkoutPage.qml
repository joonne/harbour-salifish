import QtQuick 2.0
import Sailfish.Silica 1.0

import '../components'

Page {
    id: createworkoutpage

    Component.onCompleted: timer.start()

    Timer {
        id: timer
        interval: 500
        onTriggered: {
            pageStack.pushAttached(Qt.resolvedUrl("SelectedExcercisesPage.qml"))
        }
    }

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {

            MenuItem {
                text: qsTr("Clear")
                onClicked: GymModel.clearSelectedExcercises()
            }

            MenuItem {
                text: qsTr("Continue")
                onClicked: pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
            }

            MenuItem {
                text: qsTr("Filter by Muscles")
            }
        }

        Column {
            id: column
            anchors.top: parent.top
            spacing: Theme.paddingMedium

            PageHeader {
                id: header
                title: qsTr("Choose excercise group")
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: chest
                    text: qsTr("Chest")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})

                    }

                } Button {
                    id: shoulders
                    text: qsTr("Shoulders")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})                    }
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: abs
                    text: qsTr("Abs")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                } Button {
                    id: biceps
                    text: qsTr("Biceps")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: forearms
                    text: qsTr("Forearms")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                } Button {
                    id: quads
                    text: qsTr("Quads")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: calves
                    text: qsTr("Calves")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                } Button {
                    id: trapezius
                    text: qsTr("Trapezius")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: lats
                    text: qsTr("Lats")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                }

                Button {
                    id: triceps
                    text: qsTr("Triceps")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: (createworkoutpage.width - chest.width - shoulders.width) / 3
                width: createworkoutpage.width
                spacing: (createworkoutpage.width - chest.width - shoulders.width) / 3

                Button {
                    id: glutes
                    text: qsTr("Glutes")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }

                }

                Button {
                    id: hamstrings
                    text: qsTr("Hamstrings")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }
                }
            }

            HorizontalSeparator { }

            Label {
                id: advice
                text: qsTr("Selected excercises ->")
                anchors {
                    left: parent.left
                    leftMargin: (parent.width - advice.width) / 2
                }
            }
        }
    }
}
