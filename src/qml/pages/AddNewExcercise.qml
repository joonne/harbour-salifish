import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: addexcercisepage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                id: savebutton
                text: qsTr("Save")
                onClicked: {
                    //                    GymModel.Name = excercisename.text
                    //                    GymModel.Description = description.text
                    //                    GymModel.insertExcercise()
                }
            }
        }

        Column {

            PageHeader {
                title: qsTr("Add a new excercise")
            }

            TextField {
                id: excercisename
                placeholderText: qsTr("Enter a name for your excercise")
                label: qsTr("Excercise name")
                width: addexcercisepage.width
                EnterKey.enabled: text.length > 0
//                EnterKey.iconSource: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­next"
                EnterKey.onClicked: description.focus = true
            }

            TextArea {
                id: description
                placeholderText: qsTr("Enter a name for your excercise")
                label: "Description"
                width: addexcercisepage.width
                height: 300
                EnterKey.enabled: text.length > 0
                EnterKey.onClicked: focus = false
            }
        }
    }
}
