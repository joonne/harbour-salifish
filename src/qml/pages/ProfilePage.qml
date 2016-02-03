import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: profilepage

    SilicaFlickable {

        PullDownMenu {

            MenuItem {
                text: qsTr("Edit profile")
            }
        }

        Column {
            spacing: Theme.paddingLarge

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
                TextField {
                    id: gender
                    text: controller.user.gender
                    label: qsTr("Gender")
                    readOnly: true
                }

                TextSwitch {
                    id: maleFemaleSwitch
                    text: controller.user.gender
                    description: qsTr("Changes gender")
                    visible: false
                    onCheckedChanged: {
                        controller.user.gender === qsTr("Male") ? controller.user.gender = qsTr("Female") : controller.user.gender = qsTr("Male")
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
                label: qsTr("Weight (kg)")
                readOnly: true
            }
        }

        BackgroundItem {

            TextSwitch {
                id: editSwitch
                text: qsTr("Edit")
                description: qsTr("Edit profile")
                onCheckedChanged: {

                    checked ? name.readOnly = false : name.readOnly = true
                    checked ? age.readOnly = false : age.readOnly = true
                    checked ? gender.visible = false : gender.visible = true
                    checked ? maleFemaleSwitch.visible = true : maleFemaleSwitch.visible = false
                    checked ? height.readOnly = false : height.readOnly = true
                    checked ? weight.readOnly = false : weight.readOnly = true

                    controller.user.name = name.text
                    controller.user.age = age.text
                    controller.user.gender = gender.text
                    controller.user.height = height.text
                    controller.user.weight = weight.text

                }
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
