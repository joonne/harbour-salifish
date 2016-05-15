import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: selectedexcercicespage

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: column
            anchors.fill: parent

            PageHeader {
                title: qsTr("Selected Excercises")
            }

            SilicaListView {
                id: listview
                width: parent.width
                height: parent.height
                spacing: Theme.paddingSmall
                model: controller.workoutModel

                section {
                    property: "category"
                    criteria: ViewSection.FullString
                    delegate: SectionHeader {
                        text: section
                    }
                }

                delegate: Label {
                    text: name
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingLarge
                }

                ViewPlaceholder {
                    enabled: listview.count === 0
                    text: qsTr("Selected excercises will appear here.")
                    anchors.centerIn: listview

                }

                VerticalScrollDecorator {}
            }
        }
    }
}

