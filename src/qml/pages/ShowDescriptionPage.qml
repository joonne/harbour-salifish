import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: showdescriptionpage

    property string excerciseName: ""
    property string excerciseDescription: ""

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {

            MenuItem {
                id: menuitem
                text: qsTr("Delete")
                onClicked: {
                    remorse.execute(qsTr("Deleting excercise"), function() {
                        //                        GymModel.getExcercises()
                        pageStack.pop()
                    });

                }
            }

            MenuItem {
                text: qsTr("Edit")
                onClicked: {
                    header.readOnly == true ? header.readOnly = false : header.readOnly = true
                    description.readOnly == true ? description.readOnly = false : description.readOnly = true
                    if(text === qsTr("Save")) {
                        //                        GymModel.Name = header.text
                        //                        GymModel.Description = description.text
                        //                        GymModel.updateExcercise()
                    }
                    text == "Edit" ? text = "Save" : text = "Edit"
                }
            }

            RemorsePopup { id: remorse }
        }

        Column {
            id: column
            spacing: Theme.paddingSmall

            PageHeader {
                title: qsTr("Description")
            }

            TextField {
                id: header
                text: excerciseName
                width: showdescriptionpage.width
                readOnly: true
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon­-m-­enter-­next"
                EnterKey.onClicked: description.focus = true

            }

            TextArea {
                id: description
                text: excerciseDescription
                width: showdescriptionpage.width
                readOnly: true
                height: 500
                EnterKey.enabled: text.length > 0
                EnterKey.onClicked: focus = false
            }
        }
    }
}
