import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

Page {
    id: createworkoutpage

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {
            visible: listview.count > 0

            MenuItem {
                text: qsTr("Clear")
                onClicked: GymModel.clearSelectedExcercises()
            }

            MenuItem {
                text: qsTr("Continue")
                onClicked: pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
            }
        }

        PageHeader {
            id: header
            title: qsTr("Choose muscle group")
        }

        Column {
            id: column
            anchors.top: parent.top
            anchors.topMargin: 150
            spacing: Theme.paddingMedium

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

                } Button {
                    id: hamstrings
                    text: qsTr("Hamstrings")
                    onClicked: {
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                    }
                }
            }

            SectionHeader {
                text: "Selected excercises"
                visible: listview.count > 0
            }

            SilicaListView {
                id: listview
                width: 540
                height: 960
                spacing: Theme.paddingSmall

                model: controller.workoutModel
                delegate: Label {
                    text: name
                    font.pixelSize: Theme.fontSizeSmall
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                }

                ViewPlaceholder {
                    enabled: listview.count === 0
                    text: qsTr("Selected excercises will appear here.")
                    anchors.centerIn: listview

                }

                VerticalScrollDecorator {}
            }
        }
    }
}
