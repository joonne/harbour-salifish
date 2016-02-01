import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

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
            spacing: Theme.paddinglarge
            anchors.top: pageheader.bottom

            SearchField {
                id: searchfield
                placeholderText: qsTr("Search")
                width: excercisepage.width
                EnterKey.enabled: text.length > 0
                EnterKey.onClicked: focus = false
            }

            SilicaListView {
                id: listView
                width: excercisepage.width
                height: excercisepage.height - pageheader.height - searchfield.height

                model: controller.excerciseModel

                delegate: TextSwitch {
                    text: name
                    onPressAndHold: {
                        pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"), {excerciseName: name, excerciseDescription: description})
                    }
                    onClicked: {
                        controller.workoutModel.addExcercise("1", name, description, category, 80, 7);
                    }
                }
            }
        }
    }
}

