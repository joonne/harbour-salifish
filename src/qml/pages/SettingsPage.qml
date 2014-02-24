import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: settingspage

    PageHeader {
        title: "Settings"
    }

    BackgroundItem {

        TextSwitch {
            id: unitSwitch
            anchors.top: parent.top
            anchors.topMargin: 100
            text: "Metric"
            description: "Unit System"
            onCheckedChanged: {
                checked ? text = "Imperial" : text = "Metric"
            }
        }

        TextSwitch {
            id: calendarexport
            anchors.top: parent.top
            anchors.topMargin: 200
            text: "Add finished workouts to calendar"

        }
    }
}

