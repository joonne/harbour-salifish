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

        SilicaListView {

            VerticalScrollDecorator {}

            id: list
            width: 540
            height: 960
            anchors.top: workoutname.bottom
            anchors.bottom: parent.bottom
            //spacing: 170

            model: selectedExcercisesModel
            delegate:

                TextSwitch {
                id: item
                text: modelData
                width: editworkoutpage.width
                description: "There is going to be a small description of all excercises."
                //"The bench press is a great excercise for building a powerful chest and body mass."
                onClicked: {
                    GymModel.removeExcercise(item.text)
                }

                onPressAndHold: {
                    GymModel.SelectedExcercise = item.text
                    GymModel.getExcercise(text)
                    pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"))
                }

                checked: GymModel.isExcerciseSelected(text) ? checked = true : checked = false


                Row {
                    id: currentSeries
                    anchors.top: item.bottom
                    anchors.topMargin: 10

                    IconButton {
                        icon.source: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­previous.png"
                        onClicked: GymModel.decreaseCurrentSeriesIndex()
                    }

                    TextField {
                        id: seriesLabel
                        text: "Current Series:"
                        readOnly: true

                    } TextField {
                        id: seriesCount
                        text: GymModel.currentSeriesIndex + " / " + GymModel.getSeries(item.text)
                        readOnly: true

                    }

                    IconButton {
                        icon.source: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­next.png"
                        onClicked: GymModel.increaseCurrentSeriesIndex()
                    }
                }

                Row {
                    id: specifications
                    anchors.top: currentSeries.bottom
                    anchors.topMargin: 10

                    TextField {
                        id: series
                        width: (editworkoutpage.width - 40) / 3
                        text: GymModel.getSeries(item.text)
                        anchors.top: item.bottom
                        anchors.topMargin: 10
                        label: "Series"
                        focus: false
                        EnterKey.enabled: text.length > 0
                        EnterKey.onClicked: {
                            GymModel.setSeries(item.text,GymModel.getCurrentSeriesIndex())
                            repeats.focus = true
                        }

                    } TextField {
                        id: repeats
                        width: (editworkoutpage.width - 40) / 3
                        text: GymModel.getRepeats(item.text,GymModel.currentSeriesIndex)
                        anchors.top: item.bottom
                        anchors.topMargin: 10
                        label: "Repeats"
                        focus: false
                        EnterKey.enabled: text.length > 0
                        EnterKey.onClicked: {
                            GymModel.setRepeats(item.text,repeats.text,GymModel.getCurrentSeriesIndex())
                            weights.focus = true
                        }

                    } TextField {
                        id: weights
                        width: (editworkoutpage.width - 40) / 3
                        text: GymModel.getWeights(item.text,GymModel.currentSeriesIndex)
                        anchors.top: item.bottom
                        anchors.topMargin: 10
                        label: "Weights"
                        focus: false
                        EnterKey.enabled: text.length > 0
                        EnterKey.onClicked: {
                            GymModel.setWeights(item.text,weights.text,GymModel.getCurrentSeriesIndex())
                            focus = false
                        }
                    }
                }
            }
        }
    }
}

    //    Component {
    //        id: excercisedelegate

    //        TextSwitch {
    //            id: excercisename
    //            text: modelData
    //            width: editworkoutpage.width
    //            description: "There is going to be a small description of all excercises."
    //            //"The bench press is a great excercise for building a powerful chest and body mass."
    //            onClicked: {
    //                GymModel.removeExcercise(item.text)
    //            }
    //            //                onCheckedChanged: {
    //            //                    checked ? currentSeries.visible = true : currentSeries.visible = false
    //            //                    checked ? specifications.visible = true : specifications.visible = false
    //            //                }

    //            onPressAndHold: {
    //                GymModel.SelectedExcercise = item.text
    //                GymModel.getExcercise(text)
    //                pageStack.push(Qt.resolvedUrl("ShowDescriptionPage.qml"))
    //            }

    //            checked: GymModel.isExcerciseSelected(text) ? checked = true : checked = false

    //            Row {
    //                id: currentSeries
    //                anchors.top: item.bottom
    //                anchors.topMargin: 10
    //                //visible: false
    //                TextField {
    //                    id: seriesLabel
    //                    text: "Current Series:"
    //                    readOnly: true

    //                } TextField {
    //                    id: seriesCount
    //                    text: " / " + series.text
    //                    readOnly: true

    //                }

    //                IconButton {
    //                    //icon.source: "image:/usr/share/themes/jolla-ambient/meegotouch/icons/icon­-m-­enter-­next.png"
    //                }
    //            }

    //            Row {
    //                id: specifications
    //                //                    visible: false
    //                anchors.top: currentSeries.bottom
    //                anchors.topMargin: 10

    //                TextField {
    //                    id: series
    //                    width: (editworkoutpage.width - 40) / 3
    //                    //text: workoutname.text === "" ? GymModel.getSeries(item.text) : text = ""
    //                    //                        anchors.top: item.bottom
    //                    //                        anchors.topMargin: 10
    //                    //                        anchors.left: item.left
    //                    label: "Series"
    //                    focus: false

    //                } TextField {
    //                    id: repeats
    //                    width: (editworkoutpage.width - 40) / 3
    //                    //text: workoutname.text === "" ? GymModel.getRepeats(item.text) : text = ""
    //                    //                        anchors.top: item.bottom
    //                    //                        anchors.topMargin: 10
    //                    //                        anchors.left: series.right
    //                    label: "Repeats"
    //                    focus: false

    //                } TextField {
    //                    id: weights
    //                    width: (editworkoutpage.width - 40) / 3
    //                    //text: workoutname.text ? GymModel.getWeights(item.text) : text = ""
    //                    //                        anchors.top: item.bottom
    //                    //                        anchors.topMargin: 10
    //                    //                        anchors.left: repeats.right
    //                    label: "Weights"
    //                    focus: false

    //                }
    //            }
    //        }
    //    }

