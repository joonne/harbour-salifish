import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: profilepage

    property bool editMode: false

    function updateAll() {
        controller.user.name = name.text
        controller.user.age = age.text
        controller.user.gender = gender.text
        controller.user.height = height.text
        controller.user.weight = weight.text
    }

    Component.onDestruction: updateAll()

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {

            MenuItem {
                text: qsTr("Add entry")
            }

            MenuItem {
                text: editMode ? qsTr("Save") : qsTr("Edit")
                onClicked: {
                    if (editMode) {
                        updateAll()
                    }
                    editMode = !editMode
                }
            }
        }

        Column {
            id: column
            width: parent.width

            PageHeader {
                title: qsTr("My Profile")
            }

            TextField {
                id: name
                text: controller.user.name
                label: qsTr("Name")
                readOnly: !editMode
                width: parent.width
            }

            TextField {
                id: age
                text: controller.user.age
                label: qsTr("Age")
                readOnly: !editMode
                width: parent.width
            }

            Row {
                width: parent.width

                TextField {
                    id: gender
                    text: controller.user.gender
                    label: qsTr("Gender")
                    readOnly: !editMode
                    width: parent.width / 2
                }

                TextSwitch {
                    id: maleFemaleSwitch
                    text: controller.user.gender === "Male" ? qsTr("Male") : qsTr("Female")
                    description: qsTr("Changes gender")
                    visible: editMode
                    onCheckedChanged: {
                        controller.user.gender === qsTr("Male") ? controller.user.gender = "Female" : controller.user.gender = "Male"
                    }
                    width: parent.width / 2
                }
            }

            TextField {
                id: height
                text: controller.user.height
                label: qsTr("Height (cm)")
                readOnly: !editMode
                width: parent.width
            }

            TextField {
                id: weight
                text: controller.user.weight
                label: qsTr("Weight (kg)")
                readOnly: !editMode
                width: parent.width
            }

            TextField {
                id: bmi
                text: controller.user.BMI
                label: qsTr("BMI")
                readOnly: true
                width: parent.width
            }

            TextField {
                id: bmidescription
                text: controller.user.BMIdescription
                label: qsTr("BMI description")
                readOnly: true
                width: parent.width

            }

            TextField {
                id: bmr
                text: controller.user.BMR + " " + qsTr("kcal")
                label: qsTr("Basal Metabolic Rate (BMR)")
                readOnly: true
                width: parent.width
            }
        }
    }
}
