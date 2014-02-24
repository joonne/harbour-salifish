import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: profilepage

    SilicaListView {

        spacing: Theme.paddingMedium

        TextField {
            id: name
            y: 100
            x: 20
            text: "Name"
            readOnly: true
            color: Theme.highlightColor
        } TextField {
            id: nameEdit
            y: 100
            x: 250
            text: User.name
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            id: age
            y: 200
            x: 20
            text: "Age"
            readOnly: true
            color: Theme.highlightColor
        } TextField {
            id: ageEdit
            y: 200
            x: 300
            text: User.age
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            id: gender
            y: 300
            x: 20
            text: "Gender"
            readOnly: true
            color: Theme.highlightColor
        } TextField {
            id: genderEdit
            y: 300
            x: 300
            text: User.gender
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            id: height
            y: 400
            x: 20
            text: "Height (cm)"
            readOnly: true
            color: Theme.highlightColor
        } TextField {
            id: heightEdit
            y: 400
            x: 300
            text: User.height
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            id: weight
            y: 500
            x: 20
            text: "Weight (kg)"
            readOnly: true
            color: Theme.highlightColor
        } TextField {
            id: weightEdit
            y: 500
            x: 300
            text: User.weight
            readOnly: true
            color: Theme.highlightColor
        }
    }

    BackgroundItem {

        TextSwitch {
            y: 600
            id: editSwitch
            text: "Edit"
            description: "Edit profile"
            onCheckedChanged: {

                checked ? nameEdit.readOnly = false : nameEdit.readOnly = true
                checked ? ageEdit.readOnly = false : ageEdit.readOnly = true
                checked ? genderEdit.visible = false : genderEdit.visible = true
                checked ? maleFemaleSwitch.visible = true : maleFemaleSwitch.visible = false
                checked ? heightEdit.readOnly = false : heightEdit.readOnly = true
                checked ? weightEdit.readOnly = false : weightEdit.readOnly = true

                User.name = nameEdit.text
                User.age = ageEdit.text
                User.gender = genderEdit.text
                User.height = heightEdit.text
                User.weight = weightEdit.text

            }

        }

        TextField {
            y: 725
            x: 20
            text: "BMI"
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            y: 725
            x: 100
            text: User.BMI
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            id: bmidescription
            y: 775
            x: 20
            text: User.BMIdescription
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            y: 850
            x: 20
            text: "BMR"
            readOnly: true
            color: Theme.highlightColor

        } TextField {
            y: 850
            x: 100
            text: User.BMR + " kcal"
            readOnly: true
            color: Theme.highlightColor
        }

        TextSwitch {
            y: 280
            x: 250
            id: maleFemaleSwitch
            text: "Male"
            description: "Changes gender"
            visible: false
            onCheckedChanged: {
                checked ? text = "Female" : text = "Male"
                genderEdit.text = text
            }
        }
    }
}
