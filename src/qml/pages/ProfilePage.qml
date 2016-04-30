import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: profilepage

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: parent.height

        PullDownMenu {

            MenuItem {
                text: qsTr("Edit profile")
            }
        }

        Column {
            spacing: Theme.paddingLarge
            width: parent.width

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
            }

            TextField {
                id: age
                text: controller.user.age
                label: qsTr("Age")
                readOnly: true
            }

            Row {
                width: profilepage.width

                TextField {
                    id: gender
                    text: controller.user.gender
                    label: qsTr("Gender")
                    readOnly: true
                }

                TextSwitch {
                    id: maleFemaleSwitch
                    text: controller.user.gender === "Male" ? qsTr("Male") : qsTr("Female")
                    description: qsTr("Changes gender")
                    visible: false
                    onCheckedChanged: {
                        controller.user.gender === qsTr("Male") ? controller.user.gender = "Female" : controller.user.gender = "Male"
                    }
                }
            }

            TextField {
                id: height
                text: controller.user.height
                label: qsTr("Height (cm)")
                readOnly: true
            }

            TextField {
                id: weight
                text: controller.user.weight
                label: qsTr("Weight (kg)")
                readOnly: true
            }

            TextField {
                id: bmi
                text: controller.user.BMI
                label: qsTr("BMI")
                readOnly: true
            }

            TextField {
                id: bmidescription
                text: controller.user.BMIdescription
                label: qsTr("BMI description")
                readOnly: true

            }

            TextField {
                id: bmr
                text: controller.user.BMR + " " + qsTr("kcal")
                label: qsTr("Basal Metabolic Rate (BMR)")
                readOnly: true
            }
        }
    }
}
