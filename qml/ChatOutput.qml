import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import appnovelist
import libai

ScrollView {
    id: chatOutput

    property alias text: textArea.text

    TextArea {
        id: textArea

        readOnly: true
    }

    function addUserMessage(text) {
        textAreaUtils.insertHtmlAt(textArea.textDocument,
                                   textArea.cursorPosition, text, "blue")
    }
    function addAssistantMessage(text) {
        textAreaUtils.insertHtmlAt(textArea.textDocument,
                                   textArea.cursorPosition, text, "green")
    }

    TextAreaUtils {
        id: textAreaUtils
    }
}
