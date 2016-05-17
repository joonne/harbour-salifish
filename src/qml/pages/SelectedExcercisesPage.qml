import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: selectedexcercicespage

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Clear")
                onClicked: controller.workoutModel.clearExcercises()
            }
        }

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
                spacing: Theme.paddingMedium
                clip: true

                model: controller.workoutModel

                section {
                    property: "category"
                    criteria: ViewSection.FullString
                    delegate: SectionHeader {
                        text: section
                    }
                }

                delegate: ListItem {
                    id: listItem

                    contentHeight: background.height + Theme.paddingMedium
                    contentWidth: listview.width

                    Rectangle {
                        id: container
                        anchors.fill: background
                        radius: 5
                        color: Theme.rgba(Theme.highlightBackgroundColor, 0.3)
                    }

                    BackgroundItem {
                        id: background
                        height: 6 * Theme.paddingLarge
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.paddingMedium
                        anchors.right: parent.right
                        anchors.rightMargin: Theme.paddingMedium
                        onClicked: {
                            controller.workoutModel.addExcercise(index, "1", name, description, category, 80, 7)
                        }
                    }

                    Label {
                        id: excerciseName
                        text: name
                        anchors {
                            left: parent.left
                            leftMargin: Theme.paddingLarge
                            top: parent.top
                            topMargin: (background.height - excerciseName.height) / 2

                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: controller.workoutModel.removeExcerciseByIndex(index)
                        }
                    }

                    Row {
                        id: repeatsRow
                        spacing: Theme.paddingLarge
                        anchors {
                            left: excerciseName.right
                            leftMargin: Theme.paddingLarge
                            top: background.top
                            topMargin: (background.height - repeatsRow.height - weightsRow.height) / 2
                        }

                        Label {
                            text: "-"
                            font.pixelSize: Theme.fontSizeLarge

                            MouseArea {
                                anchors.fill: parent
                                onClicked: repeats > 0 ? repeats = repeats - 1 : repeats = 1
                            }
                        }

                        Label {
                            text: reps
                            font.pixelSize: Theme.fontSizeLarge
                        }

                        Label {
                            text: "+"
                            font.pixelSize: Theme.fontSizeLarge

                            MouseArea {
                                anchors.fill: parent
                                onClicked: repeats = repeats + 1
                            }
                        }
                    }

                    Row {
                        id: weightsRow
                        spacing: Theme.paddingLarge
                        anchors {
                            left: excerciseName.right
                            leftMargin: Theme.paddingLarge
                            top: repeatsRow.top
                            topMargin: (background.height - repeatsRow.height - weightsRow.height) / 2
                        }

                        Label {
                            text: "-"
                            font.pixelSize: Theme.fontSizeLarge

                            MouseArea {
                                anchors.fill: parent
                                onClicked: weights >= 0 ? weights = weights - 0.25 : weights = 0
                            }
                        }

                        Label {
                            text: weights
                            font.pixelSize: Theme.fontSizeLarge
                        }

                        Label {
                            text: "+"
                            font.pixelSize: Theme.fontSizeLarge

                            MouseArea {
                                anchors.fill: parent
                                onClicked: weights = weights + 0.25
                            }
                        }
                    }
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

