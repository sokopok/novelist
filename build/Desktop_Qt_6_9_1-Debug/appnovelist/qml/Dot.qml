import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

Item {
    id: dotIcon

    property bool topVisible: true
    property color topColor: "black"
    property real topStroke: .5
    property bool dotVisible: true
    property color dotColor: "black"
    property real dotRadius: 4
    property bool bottomVisible: true
    property color bottomColor: "black"
    property real bottomStroke: .5

    Rectangle {
        id: topLine
        anchors.top: parent.top
        anchors.bottom: dot.top
        anchors.bottomMargin: 2
        anchors.horizontalCenter: dot.horizontalCenter
        width: dotIcon.topStroke
        height: (parent.height - dotIcon.dotRadius - 4) / 2
        radius: width / 2
        color: dotIcon.topColor
        opacity: dotIcon.topVisible
        Behavior on color {
            ColorAnimation {}
        }
        Behavior on width {
            NumberAnimation {}
        }
        Behavior on height {
            NumberAnimation {}
        }
    }
    Rectangle {
        id: dot
        anchors.centerIn: parent
        width: dotIcon.dotRadius * 2
        height: dotIcon.dotRadius * 2
        radius: dotIcon.dotRadius
        color: dotIcon.dotColor
        opacity: dotIcon.dotVisible
        Behavior on color {
            ColorAnimation {}
        }
        Behavior on width {
            NumberAnimation {}
        }
        Behavior on height {
            NumberAnimation {}
        }
    }
    Rectangle {
        id: bottomLine
        anchors.top: dot.bottom
        anchors.topMargin: 2
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: dot.horizontalCenter
        width: dotIcon.bottomStroke
        height: (parent.height - dotIcon.dotRadius - 4) / 2
        radius: width / 2
        color: dotIcon.bottomColor
        opacity: dotIcon.bottomVisible
        Behavior on color {
            ColorAnimation {}
        }
        Behavior on width {
            NumberAnimation {}
        }
        Behavior on height {
            NumberAnimation {}
        }
    }
}
