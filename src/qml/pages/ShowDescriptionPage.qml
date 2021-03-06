import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: showdescriptionpage

    property string exerciseName: ""
    property string exerciseDescription: ""
    property string exerciseImage: ""

    onExerciseNameChanged: {
        console.log("name", exerciseName)
    }

    onExerciseDescriptionChanged: {
        console.log("description", exerciseDescription)
    }

    onExerciseImageChanged: {
        console.log("image", exerciseImage)
    }

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {

            MenuItem {
                id: menuitem
                text: qsTr("Delete")
                onClicked: {
                    remorse.execute(qsTr("Deleting exercise"), function() {
                        //                        GymModel.getExercises()
                        pageStack.pop()
                    });

                }
            }

            MenuItem {
                text: qsTr("Edit")
                onClicked: {
                    header.readOnly == true ? header.readOnly = false : header.readOnly = true
                    description.readOnly == true ? description.readOnly = false : description.readOnly = true
                    if (text === qsTr("Save")) {
                        //                        GymModel.Name = header.text
                        //                        GymModel.Description = description.text
                        //                        GymModel.updateExercise()
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
                title: exerciseName
            }

            Image {
                source: exerciseImage
                sourceSize.width: parent.width - Theme.paddingLarge
                anchors.left: parent.left
                anchors.leftMargin: (parent.width - width) / 2
            }

            TextField {
                id: header
                text: '"' + exerciseName.toLocaleLowerCase() + '"'
                font.italic: true
                width: showdescriptionpage.width
                readOnly: true
                EnterKey.enabled: text.length > 0
                EnterKey.iconSource: "image://theme/icon­-m-­enter-­next"
                EnterKey.onClicked: description.focus = true
            }

            TextArea {
                id: description
                text: exerciseDescription
                width: showdescriptionpage.width
                readOnly: true
                height: 500
                EnterKey.enabled: text.length > 0
                EnterKey.onClicked: focus = false
            }
        }
    }
}
