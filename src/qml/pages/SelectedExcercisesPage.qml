import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: selectedexercicespage

    SilicaFlickable {
        anchors.fill: parent

        PageHeader {
            id: header
            title: qsTr("Selected Exercises")
        }

        PullDownMenu {
            MenuItem {
                text: qsTr("Clear")
                onClicked: controller.workoutModel.clearExercises()
            }

            MenuItem {
                text: qsTr("Continue")
                onClicked: pageStack.push(Qt.resolvedUrl("EditWorkoutPage.qml"))
            }
        }

        SilicaListView {
            id: listview
            width: selectedexercicespage.width
            height: selectedexercicespage.height - header.height
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
                    height: 15 * Theme.paddingLarge
                    anchors.left: parent.left
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.right: parent.right
                    anchors.rightMargin: Theme.paddingMedium
                }

                Label {
                    id: exerciseName
                    text: name
                    width: background.width - 2 * Theme.paddingLarge
                    truncationMode: TruncationMode.Fade
                    anchors {
                        left: background.left
                        leftMargin: Theme.paddingLarge
                        top: parent.top
                        topMargin: (background.height - exerciseName.height - repeatsRow.height - weightsRow.height - buttonRow.height) / 5
                    }
                }

                Row {
                    id: repeatsRow
                    spacing: Theme.paddingMedium
                    anchors {
                        left: background.left
                        leftMargin: Theme.paddingLarge
                        top: exerciseName.bottom
                        topMargin: (background.height - exerciseName.height - repeatsRow.height - weightsRow.height - buttonRow.height) / 5
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
                        width: (4 * Theme.paddingLarge)
                        horizontalAlignment: TextEdit.AlignHCenter
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
                    spacing: Theme.paddingMedium
                    anchors {
                        left: background.left
                        leftMargin: Theme.paddingLarge
                        top: repeatsRow.bottom
                        topMargin: (background.height - exerciseName.height - repeatsRow.height - weightsRow.height - buttonRow.height) / 5
                    }

                    Label {
                        text: qsTr("Weights")
                    }

                    Image {
                        source: "image://theme/icon-m-remove"

                        Timer {
                            id: weightsReducer
                            interval: 200
                            onTriggered: weights >= 0 ? weights = weights - 0.5 : weights = 0
                            running: false
                            repeat: true
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: weights >= 0 ? weights = weights - 0.25 : weights = 0
                            onPressAndHold: weightsReducer.running = true
                            onPressedChanged: {
                                if(!pressed) {
                                    weightsReducer.running = false
                                }
                            }
                        }
                    }

                    Label {
                        text: weights
                        font.pixelSize: Theme.fontSizeLarge
                        width: (4 * Theme.paddingLarge)
                        horizontalAlignment: TextEdit.AlignVCenter
                    }

                    Image {
                        source: "image://theme/icon-m-add"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: weights = weights + 0.25
                        }
                    }
                }

                Row {
                    id: buttonRow
                    spacing: (background.width - addButton.width - removeButton.width) / 3
                    anchors {
                        left: background.left
                        leftMargin: (background.width - addButton.width - removeButton.width) / 3
                        top: weightsRow.bottom
                        topMargin: (background.height - exerciseName.height - repeatsRow.height - weightsRow.height - buttonRow.height) / 5
                    }

                    Button {
                        id: addButton
                        text: qsTr("Add")
                        onClicked: controller.workoutModel.addExercise(index, "1", name, description, category, weights, reps)
                    }

                    Button {
                        id: removeButton
                        text: qsTr("Remove")
                        onClicked: controller.workoutModel.removeExerciseByIndex(index)
                    }
                }
            }

            ViewPlaceholder {
                enabled: listview.count === 0
                text: qsTr("Selected exercises will appear here.")
                anchors.centerIn: listview

            }

            VerticalScrollDecorator {}
        }
    }
}

