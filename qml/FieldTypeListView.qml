import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

ListView {
    id: control

    property ElementType elementType

    spacing: 0

    model: elementType?.fieldTypeListModel ?? null

    delegate: ItemDelegate {
        id: delegate

        required property FieldType fieldType
        required property string name
        required property string label
        required property string info
        required property string iconSource
        required property ValueTypeListModel valueTypes

        property bool detailsVisible

        padding: 0
        // height: 48
        width: control.width
        text: label
        icon.source: iconSource ? iconSource : "field.svg"
        icon.width: 32
        icon.height: 32

        onClicked: {
            detailsVisible = !detailsVisible
            if (detailsVisible)
                control.forceLayout()
        }

        contentItem: ColumnLayout {
            id: col

            spacing: 0

            FieldTypeListViewDelegateRow {
                id: row0
                Layout.fillWidth: true
                Layout.preferredHeight: 48
                dot.topVisible: false //delegate.field.indexIn(control.element) > 0
                dot.bottomVisible: delegate.detailsVisible
                text: delegate.text
                iconSource: "fieldtype.svg"
            }

            FieldTypeListViewDelegateRow {
                id: row1
                Layout.fillWidth: true
                Layout.preferredHeight: 48
                visible: delegate.detailsVisible
                text: "Label"
                iconSource: "field.svg"
            }

            FieldTypeListViewDelegateRow {
                id: row2
                Layout.fillWidth: true
                Layout.preferredHeight: 48
                visible: delegate.detailsVisible
                text: "Info"
                iconSource: "field.svg"
            }

            FieldTypeListViewDelegateRow {
                id: row3
                Layout.fillWidth: true
                Layout.preferredHeight: 48
                visible: delegate.detailsVisible
                text: "Icon"
                iconSource: "field.svg"
            }

            ValueTypeListView {
                Layout.fillWidth: true
                Layout.preferredHeight: 48 * count
                fieldType: delegate.fieldType
                visible: delegate.detailsVisible
            }
        }

        background: Rectangle {
            color: delegate.pressed
                   || delegate.activeFocus ? delegate.palette.base : "transparent"
        }
    }
}
