import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    PageHeader {
        title: "About SaliFish"
    }

    TextArea {
        width: parent.width
        height: 400
        readOnly: true
        anchors.centerIn: parent
        color: Theme.highlightColor
        font.pixelSize: Theme.fontSizeSmall
        text: "Created by Jonne Pihlanen.\n" +
              "This software is licenced under GPLv2.\n" +
              "http://github.com/joonne/GymTracker"
    }
}
