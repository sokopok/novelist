import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

ListView {
    id: control

    property Field field

    spacing: 0

    model: field?.valueListModel ?? null

    delegate: ItemDelegate {
        id: delegate

        required property Value value
        required property string name
        required property string label
        required property string info
        required property string iconSource
        required property var valueValue
        required property int valueType

        padding: 0
        height: 64
        width: control.width
        text: valueValue
        icon.source: iconSource ? iconSource : "value.svg"
        icon.width: 32
        icon.height: 32

        contentItem: ColumnLayout {
            id: col
            spacing: 0
            RowLayout {
                id: row
                spacing: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 64

                // Item {
                //     implicitHeight: row.height
                //     implicitWidth: implicitHeight
                //     Rectangle {
                //         implicitWidth: dotIcon.topStroke
                //         color: dotIcon.topColor
                //         height: parent.height
                //         anchors.horizontalCenter: parent.horizontalCenter
                //     }
                // }
                Dot {
                    id: dotIcon
                    implicitHeight: row.height
                    implicitWidth: implicitHeight
                    bottomVisible: delegate.value.indexIn(
                                       control.field) < control.field.values.length - 1
                }
                // ToolButton {
                //     id: valueIcon
                //     icon: delegate.icon
                //     onClicked: delegate.value.modified = !delegate.value.modified
                // }
                Label {
                    id: valueIndexIcon
                    text: delegate.value.indexIn(control.field) + 1
                    rightPadding: 16
                }
                Label {
                    Layout.fillWidth: true
                    text: delegate.text
                    font.bold: delegate.value.modified
                }
            }
        }

        background: Rectangle {
            color: delegate.pressed
                   || delegate.activeFocus ? delegate.palette.base : "transparent"
        }
    }
}
