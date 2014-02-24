import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: excercisepage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: "Add New Excercise"
                onClicked: pageStack.push(Qt.resolvedUrl("AddNewExcercise.qml"))
            }
        }

        PageHeader {
            title: GymModel.SelectedMuscle
        }

        TextField {
            id: searchfield
            y: 100
            placeholderText: "Search"
            width: excercisepage.width
            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: focus = false
        }

        SilicaListView {
            width: 540
            height: 960
            anchors.top: searchfield.bottom

            model: excerciseNamesModel
            delegate: TextSwitch {
                text: modelData
                onClicked: {
                    checked ? GymModel.SelectedExcercise = text : GymModel.SelectedExcercise = ""
                    checked ? GymModel.addExcercise(text) : GymModel.removeExcercise(text)
                }
                onPressAndHold: {
                    GymModel.SelectedExcercise = text
                    GymModel.getExcercise(text)
                    pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"))
                }

                checked: GymModel.isExcerciseSelected(text) ? checked = true : checked = false
            }
        }
    }
}

