import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: createworkoutpage

    property bool showMuscles: false

    Component.onCompleted: timer.start()

    Timer {
        id: timer
        interval: 500
        onTriggered: {
            pageStack.pushAttached(Qt.resolvedUrl("SelectedExercisesPage.qml"))
        }
    }

    SilicaGridView {
        id: gridView
        anchors.fill: parent
        cellWidth: width / 2
        cellHeight: Theme.itemSizeLarge

        model: controller.getCategoryModel()

        PullDownMenu {

            MenuItem {
                text: showMuscles ? qsTr("Categories") : qsTr("Muscles")
                onClicked: {
                    gridView.model = showMuscles ? controller.getCategoryModel() : controller.getMuscleModel()
                    showMuscles = showMuscles ? false : true
                }
            }
        }

        header: PageHeader {
            title: showMuscles ? qsTr("Select a muscle") : qsTr("Select a category")
        }

        delegate: ListItem {
            width: gridView.cellWidth
            contentHeight: gridView.cellHeight
            clip: true

            Button {
                id: button
                anchors.centerIn: parent
                width: gridView.cellWidth - Theme.paddingLarge
                text: modelData.name
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("ExercisePage.qml"), {selectedMuscle: text})
                }
            }
        }
    }
}
