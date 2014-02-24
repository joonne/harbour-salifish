import QtQuick 2.0
import Sailfish.Silica 1.0

Page {

    id: showdescriptionpage

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PageHeader {
            title: "Description"
        }

        PullDownMenu {

            MenuItem {
                id: menuitem
                text: "Delete"
                onClicked: {
                    remorse.execute("Deleting excercise...",GymModel.deleteExcerciseFromDB())
                    GymModel.getExcercises()
                    //pageStack.pop()
                }
                RemorsePopup {id: remorse}
                //onClicked: GymModel.deleteExcerciseFromDB()
            }

            MenuItem {
                text: "Edit"
                onClicked: {
                    header.readOnly == true ? header.readOnly = false : header.readOnly = true
                    description.readOnly == true ? description.readOnly = false : description.readOnly = true
                    if(text === "Save") {
                        GymModel.Name = header.text
                        GymModel.Description = description.text
                        GymModel.updateExcercise()
                    }
                    text == "Edit" ? text = "Save" : text = "Edit"
                }
            }
        }

        TextField {
            id: header
            anchors.top: parent.top
            anchors.topMargin: 150
            text: GymModel.ExcerciseName
            width: showdescriptionpage.width
            readOnly: true
            EnterKey.enabled: text.length > 0
            EnterKey.iconSource: "image://theme/icon­-m-­enter-­next"
            EnterKey.onClicked: description.focus = true

        } TextArea {
            id: description
            text: GymModel.ExcerciseDescription
            anchors.top: parent.top
            anchors.topMargin: 250
            width: showdescriptionpage.width
            readOnly: true
            height: 500
            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: focus = false
        }
    }
}
