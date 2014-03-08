import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: editworkoutpage

    SilicaFlickable {

        anchors.fill: parent

        PullDownMenu {

            //visible: workoutname.text.length > 0

            MenuItem {
                id: savebutton
                text: "Save"
                onClicked: {
                    //GymModel.setWorkoutName(workoutname.text)
                    //GymModel.createWorkout()
                    //GymModel.insertWorkoutExcercises()
                }
            }
        }

        PageHeader {
            title: "Edit Workout"
        }

        TextField {
            id: workoutname
            focus: false
            placeholderText: "Give a name for your workout"
            label: "Workout's name"
            text: {
                if(GymModel.getWorkoutName() === "")
                    text = ""
                else
                    text = GymModel.getWorkoutName()
            }

            width: editworkoutpage.width
            anchors.top: parent.top
            anchors.topMargin: 100
            EnterKey.enabled: text.length > 0
            EnterKey.onClicked: {
                GymModel.setWorkoutName(workoutname.text)
                GymModel.createWorkout()
                focus = false
            }
        }


        Component {

            id: excerciseDelegate

            BackgroundItem {


                Rectangle {

                    id: container
                    width: editworkoutpage.width
                    height: 200
                    color: "transparent"
                    border.width: 10
                    border.color: Theme.hilightColor

                        Text {
                        id: item
                        text: modelData
                        width: editworkoutpage.width
                        color: Theme.highlightColor
                        anchors.top: container.top
                        anchors.topMargin: 20
                        anchors.left: parent.left
                        anchors.leftMargin: 50
                        //title: "There is going to be a small description of all excercises."
                        //"The bench press is a great excercise for building a powerful chest and body mass."


                        //checked: GymModel.isExcerciseSelected(item.text) ? checked = true : checked = false

                        MouseArea {
                            anchors.fill: item
                            onClicked: {
                                //GymModel.removeExcercise(item.text)
                            }

                            onPressAndHold: {
                                GymModel.SelectedExcercise = item.text
                                GymModel.getExcercise(text)
                                pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"))
                            }
                        }
                    }

                    Row {
                        id: currentSeries
                        anchors.top: item.bottom
                        anchors.topMargin: 30

                        IconButton {
                            icon.source: "image://theme/icon-cover-previous"
                            onClicked: GymModel.decreaseCurrentSeriesIndex()
                        }

                        TextField {
                            id: seriesLabel
                            text: "Current Series:"
                            color: Theme.highlightColor
                            readOnly: true

                        } TextField {
                            id: seriesCount
                            text: GymModel.currentSeriesIndex + " / " + GymModel.getSeries(item.text)
                            color: Theme.highlightColor
                            readOnly: true

                        }

                        IconButton {
                            icon.source: "image://theme/icon-cover-next"
                            onClicked: GymModel.increaseCurrentSeriesIndex()
                        }
                    }
                }

                //                Row {
                //                    id: specifications
                //                    anchors.top: currentSeries.bottom
                //                    anchors.topMargin: 10

                //                    TextField {
                //                        id: series
                //                        width: (editworkoutpage.width - 40) / 3
                //                        text: GymModel.getSeries(item.text)
                //                        anchors.top: item.bottom
                //                        anchors.topMargin: 10
                //                        label: "Series"
                //                        focus: false
                //                        EnterKey.enabled: text.length > 0
                //                        EnterKey.onClicked: {
                //                            GymModel.setSeries(item.text,GymModel.getCurrentSeriesIndex())
                //                            repeats.focus = true
                //                        }

                //                    } TextField {
                //                        id: repeats
                //                        width: (editworkoutpage.width - 40) / 3
                //                        text: GymModel.getRepeats(item.text,GymModel.currentSeriesIndex)
                //                        anchors.top: item.bottom
                //                        anchors.topMargin: 10
                //                        label: "Repeats"
                //                        focus: false
                //                        EnterKey.enabled: text.length > 0
                //                        EnterKey.onClicked: {
                //                            GymModel.setRepeats(item.text,repeats.text,GymModel.getCurrentSeriesIndex())
                //                            weights.focus = true
                //                        }

                //                    } TextField {
                //                        id: weights
                //                        width: (editworkoutpage.width - 40) / 3
                //                        text: GymModel.getWeights(item.text,GymModel.currentSeriesIndex)
                //                        anchors.top: item.bottom
                //                        anchors.topMargin: 10
                //                        label: "Weights"
                //                        focus: false
                //                        EnterKey.enabled: text.length > 0
                //                        EnterKey.onClicked: {
                //                            GymModel.setWeights(item.text,weights.text,GymModel.getCurrentSeriesIndex())
                //                            focus = false
                //                        }
                //                    }
            }
        }

        SilicaListView {

            VerticalScrollDecorator {}

            id: list
            width: 540
            height: 960
            anchors.top: workoutname.bottom
            anchors.bottom: parent.bottom
            spacing: 150

            model: selectedExcercisesModel
            delegate: excerciseDelegate

        }
    }
}
