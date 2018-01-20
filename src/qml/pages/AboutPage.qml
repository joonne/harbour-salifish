import QtQuick 2.0
import Sailfish.Silica 1.0

import '../components'

Page {
    id: aboutpage

    readonly property string _APP_VERSION: appVersion
    readonly property string _APP_BUILD_NUMBER: appBuildNum

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            width: parent.width

            PageHeader {
                title: qsTr("About")
            }

            Image {
                id: icon
                source: "image://theme/harbour-salifish"
                anchors.left: parent.left
                anchors.leftMargin: (aboutpage.width - icon.width) / 2
            }

            HorizontalSeparator { }

            Label {
                id: appname
                text: "SaliFish"
                anchors.left: parent.left
                anchors.leftMargin: (aboutpage.width - appname.width) / 2
                color: Theme.primaryColor
            }

            Label {
                id: version
                text: qsTr("Version %1.%2").arg(_APP_VERSION).arg(_APP_BUILD_NUMBER)
                anchors.left: parent.left
                anchors.leftMargin: (aboutpage.width - version.width) / 2
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeExtraSmall
            }

            HorizontalSeparator { }

            SectionHeader {
                text: qsTr("General")
            }

            TextArea {
                width: aboutpage.width
                readOnly: true
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("SaliFish.")
            }

            SectionHeader {
                text: qsTr("Creator")
            }

            TextArea {
                id: creator
                width: aboutpage.width
                readOnly: true
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Jonne Pihlanen, 'joonne'")
                anchors {
                    left: parent.left
                    leftMargin: (aboutpage.width - creator.width) / 2
                }
            }

            Button {
                id: email
                text: "jonne.pihlanen@gmail.com"
                onClicked: Qt.openUrlExternally("mailto:jonne.pihlanen@gmail.com?subject=SailSeries&body=")
                anchors.left: parent.left
                anchors.leftMargin: (aboutpage.width - email.width) / 2
            }

            HorizontalSeparator { }

            SectionHeader {
                text: qsTr("Contributors")
            }

            Repeater {

                model: []

                TextField {
                    width: aboutpage.width
                    readOnly: true
                    color: Theme.primaryColor
                    font.pixelSize: Theme.fontSizeSmall
                    text: modelData
                }
            }

            SectionHeader {
                text: qsTr("Licence")
            }

            TextArea {
                width: aboutpage.width
                readOnly: true
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("This software is licenced under GPLv2.")
            }

            SectionHeader {
                text: qsTr("Content")
            }

            TextArea {
                width: aboutpage.width
                readOnly: true
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("Exercise data comes from wger API.")
            }

            SectionHeader {
                text: qsTr("Source Code")
            }

            TextArea {
                width: aboutpage.width
                readOnly: true
                color: Theme.primaryColor
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("The source code is available at GitHub. Contributions, ideas and bug reports are welcome.")
            }

            Button {
                id: sourcecode
                text: qsTr("Project in GitHub")
                onClicked: Qt.openUrlExternally("https://github.com/joonne/harbour-salifish")
                anchors.left: parent.left
                anchors.leftMargin: (aboutpage.width - sourcecode.width) / 2
                width: email.width
            }

//            SectionHeader {
//                text: qsTr("Translations")
//            }
//
//            TextArea {
//                width: aboutpage.width
//                readOnly: true
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//                text: qsTr("SaliFish uses the Transifex translation platform to host the translations.")
//            }

//            Button {
//                id: transifex
//                text: qsTr("Help with translations")
//                onClicked: Qt.openUrlExternally("https://www.transifex.com/joonne/sailseries/")
//                anchors.left: parent.left
//                anchors.leftMargin: (aboutpage.width - sourcecode.width) / 2
//                width: email.width
//            }

//            HorizontalSeparator { }
        }

        VerticalScrollDecorator { }
    }
}
