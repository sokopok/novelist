import QtQuick
import QtQuick.Controls
import "util.js" as Util

ToolButton {
    id: control

    implicitHeight: implicitWidth
    height: width

    display: AbstractButton.IconOnly

    opacity: enabled ? 1 : .25

    property color highlightColor: "#ff00aad4"

    icon.width: 48
    icon.height: 48

    background: Rectangle {
        radius: width / 2
        color: enabled ? (control.down ? Util.transparent(
                                             control.highlightColor,
                                             .4) : control.hovered ? "#ffdddddd" : control.flat ? "#00000000" : "#ffffffff") : (control.flat ? "#00000000" : "#ffffffff")
        border.color: enabled
                      && control.highlighted ? Util.transparent(
                                                   control.highlightColor,
                                                   .4) : "#00000000"
    }
}
