import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

ListView {
    id: control

    property Element element

    Rectangle {
        color: delegate.pressed
               || delegate.activeFocus ? delegate.palette.base : "blue"
        z: -1
    }
    spacing: 0

    model: (element?.fieldListModel as FieldListModel) ?? null

    delegate: ItemDelegate {
        id: delegate

        required property Field field
        required property string name
        required property string label
        required property string info
        required property string iconSource
        required property ValueListModel values

        property bool valuesVisible

        padding: 0
        // height: 64
        width: control.width
        text: label
        icon.source: iconSource ? iconSource : "field.svg"
        icon.width: 32
        icon.height: 32

        onClicked: {
            if (values.rowCount() == 0)
                return
            valuesVisible = !valuesVisible
            if (valuesVisible)
                control.forceLayout()
        }

        contentItem: ColumnLayout {
            id: col
            spacing: 0
            RowLayout {
                id: row
                spacing: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 64

                Dot {
                    id: dotIcon
                    implicitHeight: row.height
                    implicitWidth: implicitHeight
                    topVisible: false //delegate.field.indexIn(control.element) > 0
                    bottomVisible: delegate.valuesVisible
                }

                // ToolButton {
                //     id: fieldIcon
                //     icon: delegate.icon
                //     onClicked: delegate.field.modified = !delegate.field.modified
                // }
                // ToolButton {
                //     id: fieldModifiedIcon
                //     icon.source: delegate.iconSource ? delegate.iconSource : "modified.svg"
                //     icon.width: opacity * 32
                //     icon.height: opacity * 32
                //     Layout.preferredWidth: opacity * 48
                //     Layout.preferredHeight: opacity * 48
                //     enabled: opacity > 0
                //     opacity: delegate.field.modified ? 1 : 0
                //     Behavior on opacity {
                //         NumberAnimation {}
                //     }
                // }
                // ToolButton {
                //     id: fieldIndexIcon
                //     text: delegate.field.indexIn(control.element)+1
                // }
                Label {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 64
                    text: delegate.text
                    font.bold: delegate.field.modified
                    verticalAlignment: Text.AlignVCenter
                }
            }
            ValueListView {
                Layout.fillWidth: true
                Layout.preferredHeight: 64 * count
                field: delegate.field
                visible: delegate.valuesVisible
            }
        }

        background: Rectangle {
            color: delegate.pressed
                   || delegate.activeFocus ? delegate.palette.base : "transparent"
        }
    }
}
