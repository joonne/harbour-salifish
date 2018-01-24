import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: exercisepage

    property string selectedMuscle: ""

    Component.onCompleted: controller.exerciseModel.populate(selectedMuscle)

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Add a new exercise")
                onClicked: pageStack.push(Qt.resolvedUrl("AddNewExercise.qml"))
            }
            MenuItem {
                text: qsTr("Select all")
                onClicked: console.log("Select all")
            }
        }

        PageHeader {
            id: pageheader
            title: selectedMuscle
        }

        Column {
            spacing: Theme.paddingLarge
            anchors.top: pageheader.bottom

            SearchField {
                placeholderText: qsTr("Search")
                width: parent.width - Theme.paddingLarge
                anchors {
                    left: parent.left
                    leftMargin: (parent.width - widht) / 2
                }
            }

            SilicaListView {
                id: listView
                width: exercisepage.width
                height: exercisepage.height - pageheader.height

                model: controller.exerciseModel

                delegate: TextSwitch {
                    text: name
                    checked: controller.workoutModel.isSelected(name)

                    onPressAndHold: pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"), {
                                                       exerciseName: name,
                                                       exerciseDescription: description,
                                                       exerciseImage: image
                                                    })
                    onClicked: checked
                               ? controller.workoutModel.addExercise(0, "1", name, description, category, 80, 7)
                               : controller.workoutModel.removeExerciseByName(name)
                }
            }
        }
    }
}

