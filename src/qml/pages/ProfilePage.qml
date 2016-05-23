import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: profilepage

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        PullDownMenu {

            MenuItem {
                text: qsTr("Edit profile")
            }

            MenuItem {
                text: qsTr("Add entry")
            }
        }

        Column {
            id: column
            width: parent.width

            PageHeader {
                title: qsTr("My Profile")
            }

            TextSwitch {
                id: editSwitch
                text: qsTr("Edit")
                description: qsTr("Edit profile")
                onCheckedChanged: {

                    name.readOnly = checked ? false : true
                    age.readOnly = checked ? false : true
                    gender.visible = checked ? false : true
                    maleFemaleSwitch.visible = checked ? true : false
                    height.readOnly = checked ? false : true
                    weight.readOnly = checked ?  false : true

                    controller.user.name = name.text
                    controller.user.age = age.text
                    controller.user.gender = gender.text
                    controller.user.height = height.text
                    controller.user.weight = weight.text

                }
            }

            TextField {
                id: name
                text: controller.user.name
                label: qsTr("Name")
                readOnly: true
                width: parent.width
            }

            TextField {
                id: age
                text: controller.user.age
                label: qsTr("Age")
                readOnly: true
                width: parent.width
            }

            Row {
                width: parent.width

                TextField {
                    id: gender
                    text: controller.user.gender
                    label: qsTr("Gender")
                    readOnly: true
                    width: parent.width / 2
                }

                TextSwitch {
                    id: maleFemaleSwitch
                    text: controller.user.gender === "Male" ? qsTr("Male") : qsTr("Female")
                    description: qsTr("Changes gender")
                    visible: false
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
                readOnly: true
                width: parent.width
            }

            TextField {
                id: weight
                text: controller.user.weight
                label: qsTr("Weight (kg)")
                readOnly: true
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
