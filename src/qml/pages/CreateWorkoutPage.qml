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
                text: "Clear"
                onClicked: GymModel.clearSelectedExcercises()
            }

            MenuItem {
                text: "Continue"
                onClicked: pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
            }
        }

        PageHeader {
            id: header
            title: "Choose Muscle Group"
        }

        SilicaListView {

            spacing: Theme.paddingMedium

            BackgroundItem {

                Button {
                    text: "Chest"
                    //y: 100
                    anchors.top: parent.top
                    anchors.topMargin: 100
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Shoulders"
                    y: 100
                    x: 270
                    //anchors.right: createworkoutpage.right
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))
                    }

                } Button {
                    text: "Abs"
                    y: 160
                    x: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Biceps"
                    y: 160
                    x: 270
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Forearms"
                    y: 220
                    x: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Quads"
                    y: 220
                    x: 270
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Calves"
                    y: 280
                    x: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Trapezius"
                    y: 280
                    x: 270
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Lats"
                    y: 340
                    x: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Triceps"
                    y: 340
                    x: 270
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    text: "Glutes"
                    y: 400
                    x: 10
                    onClicked: {
                        GymModel.SelectedMuscle = text
                        GymModel.getExcercises()
                        pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"))

                    }

                } Button {
                    id: hamstrings
                    text: "Hamstrings"
                    y: 400
                    x: 270
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
            anchors.top: parent.top
            anchors.topMargin: 550
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
