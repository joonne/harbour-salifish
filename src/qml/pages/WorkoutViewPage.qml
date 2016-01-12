import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: workoutViewPage

    SilicaFlickable {
        anchors.fill: parent

        SlideshowView {

            id: workoutView
            width: workoutViewPage.width
            height: workoutViewPage.height
            itemWidth: width

            model: VisualItemModel {
                id: items
                Workout { id: workout }
                WorkoutStatus { id: status }
            }
        }
    }
}
