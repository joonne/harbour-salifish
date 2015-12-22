import QtQuick 2.0
import Sailfish.Silica 1.0

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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: shoulders
                    text: qsTr("Shoulders")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))
                    }
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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: biceps
                    text: qsTr("Biceps")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: quads
                    text: qsTr("Quads")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: trapezius
                    text: qsTr("Trapezius")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: triceps
                    text: qsTr("Triceps")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

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
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: hamstrings
                    text: qsTr("Hamstrings")
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }
                }
            }
        }

        SilicaListView {

            VerticalScrollDecorator {}

            id: listview
            width: 540
            height: 960
            anchors.top: column.bottom
            anchors.topMargin: 50
            anchors.bottom: parent.bottom
            spacing: 10 //Theme.paddingSmall

            model: selectedExcercisesModel
            delegate: TextField {
                text: modelData
                readOnly: true
                onPressAndHold: {

                }
            }

            ViewPlaceholder {
                enabled: listview.count === 0
                text: "Selected excercises will appear here."
                anchors.centerIn: listview

            }
        }
    }
}
