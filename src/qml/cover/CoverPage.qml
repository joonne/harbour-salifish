import QtQuick 2.0
import Sailfish.Silica 1.0

CoverBackground {

    CoverPlaceholder {
        id: placeholder
        // enabled: GymModel.Mode === "normal"
        enabled: true
        text: qsTr("SaliFish")
        icon.source: "image://theme/harbour-salifish"
    }

//    CoverActionList {
//        enabled: GymModel.Mode === "workout"
//        id: workoutActions
//        CoverAction {
//            iconSource: "image://theme/icon-cover-previous"
//            onTriggered: placeholder.text = GymModel.previousCoverExercise()
//        }
//        CoverAction {
//            iconSource: "image://theme/icon-cover-next"
//            onTriggered: {
//                GymModel.removeWorkoutExercise(placeholder.text)
//                placeholder.text = GymModel.nextCoverExercise()
//            }
//        }
//    }
}
