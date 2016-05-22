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
            pageStack.pushAttached(Qt.resolvedUrl("SelectedExcercisesPage.qml"))
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
                    showMuscles ? gridView.model = controller.getCategoryModel() : gridView.model = controller.getMuscleModel()
                    showMuscles ? showMuscles = false : showMuscles = true
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
                    pageStack.push(Qt.resolvedUrl("ExcercisePage.qml"), {selectedMuscle: text})
                }
            }
        }
    }
}
