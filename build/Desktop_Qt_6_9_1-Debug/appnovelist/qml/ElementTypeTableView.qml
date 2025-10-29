import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

TableView {
    id: tableView

    delegate: TableViewDelegate {// id: delegate

        // required property string itemType

        // contentItem: Loader {
        //     source: delegate.itemType === "label" ? "ElementTreeviewDelegateLabel.qml" : "ElementTreeviewDelegateValue.qml"
        // }
    }
}
