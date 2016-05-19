import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: selectedexcercicespage

    SilicaFlickable {
        anchors.fill: parent

        PageHeader {
            id: header
            title: qsTr("Selected Excercises")
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Clear")
                onClicked: controller.workoutModel.clearExcercises()
            }

            MenuItem {
                text: qsTr("Continue")
                onClicked: pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
            }
        }

        SilicaListView {
            id: listview
            width: selectedexcercicespage.width
            height: selectedexcercicespage.height - header.height
            spacing: Theme.paddingMedium
            anchors {
                top: header.bottom
            }
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
                    height: 10 * Theme.paddingLarge
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingMedium
                    onClicked: {
                        controller.workoutModel.addExcercise(index, "1", name, description, category, weights, reps)
                    }
                }

                Label {
                    id: excerciseName
                    text: name
                    width: background.width - 2 * Theme.paddingLarge
                    truncationMode: TruncationMode.Fade
                    anchors {
                        left: background.left
                        leftMargin: Theme.paddingLarge
                        top: parent.top
                        topMargin: Theme.paddingMedium
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
                        left: background.left
                        leftMargin: (background.width - repeatsRow.width) / 2
                        top: excerciseName.bottom
                        topMargin: (background.height - excerciseName.height - repeatsRow.height - weightsRow.height) / 4
                    }

                    Label {
                        text: qsTr("Repeats")
                    }

                    Image {
                        source: "image://theme/icon-m-remove"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: reps > 0 ? reps = reps - 1 : reps = 1
                        }
                    }

                    Label {
                        text: reps
                        font.pixelSize: Theme.fontSizeLarge
                    }

                    Image {
                        source: "image://theme/icon-m-add"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: reps = reps + 1
                        }
                    }
                }

                Row {
                    id: weightsRow
                    spacing: Theme.paddingLarge
                    anchors {
                        left: background.left
                        leftMargin: (background.width - weightsRow.width) / 2
                        top: repeatsRow.bottom
                        topMargin: (background.height - excerciseName.height - repeatsRow.height - weightsRow.height) / 4
                    }

                    Label {
                        text: qsTr("Weights")
                    }

                    Image {
                        source: "image://theme/icon-m-remove"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: weights >= 0 ? weights = weights - 0.25 : weights = 0
                        }
                    }

                    Label {
                        text: weights
                        font.pixelSize: Theme.fontSizeLarge
                    }

                    Image {
                        source: "image://theme/icon-m-add"

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

