import QtQuick

Image {
    id: control

    property alias running: animation.running
    property int duration: 2000

    source: "bubble-square.svg"

    Item {
        width: ai.width
        height: ai.height
        clip: true
        Image {
            id: ai
            source: "ai-square.svg"
        }
        Image {
            id: computer
            source: "computer-square.svg"
        }
    }

    ParallelAnimation {
        id: animation
        running: true
        SequentialAnimation {
            loops: Animation.Infinite
            NumberAnimation {
                target: ai
                property: "x"
                duration: control.duration / 2
                easing.type: Easing.InOutCubic
                from: -ai.width
                to: 0
            }
            PauseAnimation {
                duration: control.duration / 2
            }
            NumberAnimation {
                target: ai
                property: "x"
                duration: control.duration / 2
                easing.type: Easing.InOutCubic
                from: 0
                to: ai.width
            }
            PauseAnimation {
                duration: control.duration / 2
            }
        }
        SequentialAnimation {
            loops: Animation.Infinite
            NumberAnimation {
                target: computer
                property: "x"
                duration: control.duration / 2
                easing.type: Easing.InOutCubic
                from: 0
                to: computer.width
            }
            PauseAnimation {
                duration: control.duration / 2
            }
            NumberAnimation {
                target: computer
                property: "x"
                duration: control.duration / 2
                easing.type: Easing.InOutCubic
                from: -computer.width
                to: 0
            }
            PauseAnimation {
                duration: control.duration / 2
            }
        }
    }
}
