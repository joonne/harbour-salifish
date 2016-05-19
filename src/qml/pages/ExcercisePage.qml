import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: excercisepage

    property string selectedMuscle: ""

    Component.onCompleted: controller.excerciseModel.populate(selectedMuscle)

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Add a new excercise")
                onClicked: pageStack.push(Qt.resolvedUrl("AddNewExcercise.qml"))
            }
        }

        PageHeader {
            id: pageheader
            title: selectedMuscle
        }

        Column {
            spacing: Theme.paddingLarge
            anchors.top: pageheader.bottom

            SilicaListView {
                id: listView
                width: excercisepage.width
                height: excercisepage.height - pageheader.height

                model: controller.excerciseModel

                delegate: TextSwitch {
                    text: name
                    checked: controller.workoutModel.isSelected(name)
                    onPressAndHold: {
                        pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"), {excerciseName: name, excerciseDescription: description})
                    }
                    onClicked: checked ? controller.workoutModel.addExcercise(0, "1", name, description, category, 80, 7) : controller.workoutModel.removeExcerciseByName(name)
                }
            }
        }
    }
}

