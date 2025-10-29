import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import libnovelist
import appnovelist
import libai

// import be.oncruyt.ai
ApplicationWindow {
    id: app

    width: 640
    height: 480
    visible: true
    title: qsTr("Novelist")

    readonly property ResponsesClient aiClient: ResponsesClient {
        id: aiClient

        // onResponseTextGenerated: (resonse, text) => {
        //                              chatPage.chatOutput.addAssistantMessage(
        //                                  `<p>${text}</p>`)
        //                          }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        ChatPage {
            id: chatPage
            Layout.fillWidth: true
            Layout.fillHeight: true

            onSendPressed: text => {
                               chatPage.chatOutput.addUserMessage(
                                   `<p>${text}</p>`)
                               response = aiClient.post(request)
                               response.textGenerated.connect(text => {
                                                                  chatPage.chatOutput.addAssistantMessage(
                                                                      `<p>${text}</p>`)
                                                              })
                           }
        }

        SettingsPage {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        NodeListView {
            node: storage.elementStorage.element(4)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        FieldListView {
            element: storage.elementStorage.element(4)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        FieldTypeListView {
            elementType: storage.elementTypeStorage.elementType(1)
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ElementTypeTableView {
            model: ElementTypeTableModel {
                elementTypes: [storage.elementTypeStorage.elementType(1)]
                onElementTypesChanged: console.log(elementTypes)
            }
            onModelChanged: console.log(model)
            Component.onCompleted: console.log(model)
        }
        Layout.fillWidth: true
        Layout.fillHeight: true
    }

    footer: TabBar {
        id: tabBar
        width: parent.width
        currentIndex: 5
        TabButton {
            text: qsTr("Chat")
            width: implicitWidth
        }
        TabButton {
            text: qsTr("Settings")
            width: implicitWidth
        }
        TabButton {
            text: qsTr("NodeListView")
            width: implicitWidth
        }
        TabButton {
            text: qsTr("FieldListView")
            width: implicitWidth
        }
        TabButton {
            text: qsTr("FieldTypeListView")
            width: implicitWidth
        }
        TabButton {
            text: qsTr("ElementTypeTableView")
            width: implicitWidth
        }
    }
}
