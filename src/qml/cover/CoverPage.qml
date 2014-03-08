import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {

    CoverPlaceholder {
        id: placeholder
        enabled: GymModel.Mode === "normal"
        text: "SaliFish"
        icon.source: "image://theme/harbour-gymtracker"
    }

    CoverActionList {
        enabled: GymModel.Mode === "workout"
        id: workoutActions
        CoverAction {
            iconSource: "image://theme/icon-cover-previous"
            onTriggered: placeholder.text = GymModel.previousCoverExcercise()
        }
        CoverAction {
            iconSource: "image://theme/icon-cover-next"
            onTriggered: {
                GymModel.removeWorkoutExcercise(placeholder.text)
                placeholder.text = GymModel.nextCoverExcercise()
            }
        }
    }
}
