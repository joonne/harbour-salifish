import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.salifish 1.0

Page {
    id: excercisepage

    property string selectedMuscle: ""

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Add a new excercise")
                onClicked: pageStack.push(Qt.resolvedUrl("AddNewExcercise.qml"))
            }
        }

        PageHeader {
            title: selectedMuscle
        }

        SearchField {
            id: searchfield
            y: 100
            placeholderText: qsTr("Search")
            width: excercisepage.width
            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: focus = false
        }

        SilicaListView {
            id: listView
            width: 540
            height: 960
            anchors.top: searchfield.bottom

            model: ExcerciseModel {
                id: excerciseModel
                Component.onCompleted: excerciseModel.populate(selectedMuscle.toLowerCase())
            }

            delegate: TextSwitch {
                text: name
                onClicked: {
//                    checked ? GymModel.SelectedExcercise = text : GymModel.SelectedExcercise = ""
//                    checked ? GymModel.addExcercise(text) : GymModel.removeExcercise(text)
                }
                onPressAndHold: {
//                    GymModel.SelectedExcercise = text
//                    GymModel.getExcercise(text)
                    pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"), {excerciseName: name, excerciseDescription: description})
                    console.log(description);
                }

//                checked: GymModel.isExcerciseSelected(text) ? checked = true : checked = false
            }
        }
    }
}

