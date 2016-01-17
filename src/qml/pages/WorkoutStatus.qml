import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: workoutStatusItem
    height: workoutView.height;
    width: workoutView.width;

    SilicaFlickable {
        anchors.fill: parent

        Column {
            id: column
            spacing: Theme.paddingLarge

            Row {
                id: seriesrow
                anchors {
                    left: parent.left
                    leftMargin: (workoutStatusItem.width - seriesrow.width) / 2
                }

                Label {
                    text: "4 series to go"
                }
            }
        }
    }
}

