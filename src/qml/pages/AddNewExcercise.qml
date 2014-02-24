import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: addexcercisepage

    SilicaFlickable {

        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                id: savebutton
                text: "Save"
                onClicked: {
                    GymModel.Name = excercisename.text
                    GymModel.Description = description.text
                    GymModel.insertExcercise()
                }
            }
        }

        PageHeader {
            title: "Add New Excercise"
        }


        TextField {
            id: excercisename
            anchors.top: parent.top
            anchors.topMargin: 100
            placeholderText: "Enter a name for your excercise"
            label: "Excercise name"
            width: addexcercisepage.width
            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­next"
            EnterKey.onClicked: description.focus = true
        }

        TextArea {
            id: description
            anchors.top: parent.top
            anchors.topMargin: 250
            placeholderText: "Enter a name for your excercise"
            label: "Description"
            width: addexcercisepage.width
            height: 500
            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: focus = false

        }
    }
}
