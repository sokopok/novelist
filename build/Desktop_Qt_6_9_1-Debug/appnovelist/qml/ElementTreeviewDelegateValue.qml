import QtQuick
import QtQuick.Controls

ScrollView {
    id: control
    property alias text: textArea.text
    TextArea {
        id: textArea
    }
}
