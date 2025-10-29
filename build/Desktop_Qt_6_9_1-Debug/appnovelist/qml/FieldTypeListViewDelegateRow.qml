import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

RowLayout {
    id: row

    property alias text: label.text
    property alias iconSource: icon.source
    readonly property Dot dot: dot
    readonly property Image icon: icon
    readonly property Label label: label

    spacing: 0

    Dot {
        id: dot

        implicitHeight: row.height
        implicitWidth: implicitHeight
    }

    Image {
        id: icon

        Layout.preferredWidth: 24
        Layout.preferredHeight: 24
        Layout.rightMargin: 16
    }

    Label {
        id: label

        Layout.fillWidth: true
        Layout.preferredHeight: 48
        verticalAlignment: Text.AlignVCenter
    }
}
