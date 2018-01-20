import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: addexercisepage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                id: savebutton
                text: qsTr("Save")
                onClicked: {
                    //                    GymModel.Name = exercisename.text
                    //                    GymModel.Description = description.text
                    //                    GymModel.insertExercise()
                }
            }
        }

        Column {

            PageHeader {
                title: qsTr("Add a new exercise")
            }

            TextField {
                id: exercisename
                placeholderText: qsTr("Enter a name for your exercise")
                label: qsTr("Exercise name")
                width: addexercisepage.width
                EnterKey.enabled: text.length > 0
//                EnterKey.iconSource: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­next"
                EnterKey.onClicked: description.focus = true
            }

            TextArea {
                id: description
                placeholderText: qsTr("Enter a name for your exercise")
                label: "Description"
                width: addexercisepage.width
                height: 300
                EnterKey.enabled: text.length > 0
                EnterKey.onClicked: focus = false
            }
        }
    }
}
