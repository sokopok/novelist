import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

ListView {
    id: control

    property FieldType fieldType

    spacing: 0

    model: fieldType?.valueTypeListModel ?? null

    delegate: ItemDelegate {
        id: delegate

        required property ValueType valueType
        required property string name
        required property string label
        required property string info
        required property string iconSource

        property bool valueTypesVisible

        padding: 0
        // height: 48
        width: control.width
        text: label
        icon.source: iconSource ? iconSource : "value.svg"
        icon.width: 32
        icon.height: 32

        onClicked: {
            if (valueTypes.rowCount() == 0)
                return
            valueTypesVisible = !valueTypesVisible
            if (valueTypesVisible)
                control.forceLayout()
        }

        contentItem: ColumnLayout {
            id: col
            spacing: 0
            RowLayout {
                id: row
                spacing: 0
                Layout.fillWidth: true
                Layout.preferredHeight: 48

                Dot {
                    id: dotIcon
                    implicitHeight: row.height
                    implicitWidth: implicitHeight
                    topVisible: true
                    bottomVisible: false
                }

                Image {
                    Layout.preferredWidth: 24
                    Layout.preferredHeight: 24
                    Layout.rightMargin: 16
                    source: "valuetype.svg"
                }

                Label {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 48
                    text: delegate.text
                    font.bold: delegate.valueType.modified
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        background: Rectangle {
            color: delegate.pressed
                   || delegate.activeFocus ? delegate.palette.base : "transparent"
        }
    }
}
