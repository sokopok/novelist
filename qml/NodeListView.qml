import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

ListView {
    id: control

    property Node node

    model: node?.nodeListModel ?? null

    delegate: ItemDelegate {
        required property string name
        required property string label
        required property string info
        required property string iconSource

        height: 64
        width: control.width
        text: label
        icon.source: iconSource ? iconSource : "node.svg"
        icon.width: 32
        icon.height: 32
    }
}
