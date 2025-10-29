import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import appnovelist
import libai

Page {
    id: page

    readonly property ChatOutput chatOutput: chatOutput
    property alias outputText: chatOutput.text
    property alias inputText: inputTextArea.text
    property responsesRequest request
    property ResponsesResponse response

    signal addPressed
    signal speakPressed
    signal sendPressed(string text)

    SplitView {
        id: splitView

        anchors.fill: parent
        anchors.margins: 32
        orientation: Qt.Vertical

        handle: Rectangle {
            id: handle
            height: 4
            containmentMask: Item {
                y: -16
                width: handle.width
                height: handle.height + 32
            }
        }

        ChatOutput {
            id: chatOutput

            SplitView.fillHeight: true
            SplitView.fillWidth: true
        }

        RowLayout {
            SplitView.fillWidth: true
            SplitView.minimumHeight: 50
            SplitView.maximumHeight: 500
            SplitView.preferredHeight: 50

            spacing: 16

            RoundButton {
                action: addAction
                opacity: enabled ? 1 : .3
                Layout.alignment: Qt.AlignTop
            }

            ScrollView {
                id: inputScrollView

                Layout.fillWidth: true
                Layout.fillHeight: true

                TextArea {
                    id: inputTextArea

                    text: qsTr("Hello!")
                }
            }

            RoundButton {
                action: speakAction
                opacity: enabled ? 1 : .3
                Layout.alignment: Qt.AlignTop
            }

            RoundButton {
                action: sendAction
                opacity: enabled ? 1 : .3
                Layout.alignment: Qt.AlignTop
            }
        }
    }

    SquareBubble {}

    Action {
        id: addAction
        text: qsTr("Add...")
        icon.name: "list-add"
        enabled: false
        onTriggered: page.addPressed()
    }

    Action {
        id: speakAction
        text: qsTr("Speak")
        icon.name: "audio-input-microphone"
        enabled: false
        onTriggered: page.speakPressed()
    }

    Action {
        id: sendAction
        text: qsTr("Send")
        icon.name: "arrow-up"
        enabled: inputTextArea.text
        onTriggered: {
            var text = page.inputText.trim()
            page.inputText = ""

            var request = page.request

            request.setInput(text)

            if (page.response)
                request.previousResponseId = page.response.id

            page.request = request

            page.sendPressed(text)
        }
    }
}
