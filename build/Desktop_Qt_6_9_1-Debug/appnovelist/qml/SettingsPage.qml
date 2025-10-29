import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import appnovelist
import libai

Page {
    id: page

    property responsesRequest request

    ListView {
        id: listView

        anchors.fill: parent
        anchors.margins: 32

        model: [{
                "label": "API Url",
                "description": "...",
                "icon": "ai.svg",
                "type": "url",
                "value": page.request.url
            }, {
                "label": "API Key",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": page.request.apiKey
            }, {
                "label": "Background",
                "description": "...",
                "icon": "ai.svg",
                "type": "boolean",
                "value": page.request.background
            }, {
                "label": "Conversation",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": "" //page.request.conversation
            }, {
                "label": "Include",
                "description": "...",
                "icon": "ai.svg",
                "type": "array",
                "value": "" //page.request.include
            }, {
                "label": "Input",
                "description": "...",
                "icon": "ai.svg",
                "type": "array",
                "value": page.request.input
            }, {
                "label": "Instructions",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": page.request.instructions
            }, {
                "label": "MaxOutputTokens",
                "description": "...",
                "icon": "ai.svg",
                "type": "integer",
                "value": 0
            }, {
                "label": "MaxToolCalls",
                "description": "...",
                "icon": "ai.svg",
                "type": "integer",
                "value": 0
            }, {
                "label": "Metadata",
                "description": "...",
                "icon": "ai.svg",
                "type": "map",
                "value": null
            }, {
                "label": "Model",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": ""
            }, {
                "label": "parallelToolCalls",
                "description": "...",
                "icon": "ai.svg",
                "type": "boolean",
                "value": true
            }, {
                "label": "previousResponseId",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": ""
            }, {
                "label": "Prompt",
                "description": "...",
                "icon": "ai.svg",
                "value": null
            }, {
                "label": "promptCacheKey",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": ""
            }, {
                "label": "reasoning",
                "description": "...",
                "icon": "ai.svg",
                "value": null
            }, {
                "label": "safetyIdentifier",
                "description": "...",
                "icon": "ai.svg",
                "type": "string",
                "value": ""
            }, {
                "label": "serviceTier",
                "description": "...",
                "icon": "ai.svg",
                "value": null
            }, {
                "label": "store",
                "description": "...",
                "icon": "ai.svg",
                "type": "boolean",
                "value": true
            }, {
                "label": "stream",
                "description": "...",
                "icon": "ai.svg",
                "type": "boolean",
                "value": false
            }, {
                "label": "StreamOptions",
                "description": "...",
                "icon": "ai.svg",
                "value": null
            }, {
                "label": "temperature",
                "description": "...",
                "icon": "ai.svg",
                "type": "real",
                "value": 1.0
            }, {
                "label": "tools",
                "description": "...",
                "icon": "ai.svg",
                "value": []
            }, {
                "label": "topLogprobs",
                "description": "...",
                "icon": "ai.svg",
                "type": "integer",
                "value": 0
            }, {
                "label": "topP",
                "description": "...",
                "icon": "ai.svg",
                "type": "real",
                "value": 1.0
            }, {
                "label": "Truncation",
                "description": "...",
                "icon": "ai.svg",
                "value": null
            }]

        delegate: Item {
            id: d
            required property string label
            required property string description
            required property string icon
            required property string type
            required property var value

            width: listView.width
            implicitWidth: row.implicitWidth + 2 * row.anchors.margins
            implicitHeight: row.implicitHeight + 2 * row.anchors.margins

            RowLayout {
                id: row

                anchors.fill: parent
                anchors.margins: 4
                spacing: 4

                Image {
                    source: d.icon
                    sourceSize.width: 22
                    sourceSize.height: 22
                }

                Label {
                    Layout.preferredWidth: 150
                    text: d.label
                    padding: 8
                }
                Label {
                    id: valueLabel
                    Layout.fillWidth: true
                    text: d.value
                    padding: 8

                    TapHandler {
                        onTapped: {
                            switch (d.type) {
                            default:

                            case "string":
                                loader.sourceComponent = stringEditor
                                break
                            case "integer":
                                loader.sourceComponent = integerEditor
                                break
                            case "real":
                                loader.sourceComponent = realEditor
                                break
                            case "boolean":
                                loader.sourceComponent = booleanEditor
                                break
                            }
                            loader.item.forceActiveFocus()
                        }
                    }

                    Loader {
                        id: loader
                        anchors.fill: parent
                    }

                    Component {
                        id: stringEditor
                        TextField {
                            id: valueEdit
                            anchors.fill: parent
                            text: d.value
                            padding: 8
                            visible: activeFocus
                            onActiveFocusChanged: if (activeFocus)
                                                      selectAll()
                        }
                    }
                    Component {
                        id: integerEditor
                        TextField {
                            id: valueEdit
                            anchors.fill: parent
                            text: d.value
                            padding: 8
                            validator: IntValidator {
                                bottom: 0
                                top: 100
                            }
                            visible: activeFocus
                            onActiveFocusChanged: if (activeFocus)
                                                      selectAll()
                        }
                    }
                    Component {
                        id: realEditor
                        TextField {
                            id: valueEdit
                            anchors.fill: parent
                            text: d.value
                            padding: 8
                            validator: DoubleValidator {
                                bottom: 0
                                top: 100
                            }
                            visible: activeFocus
                            onActiveFocusChanged: if (activeFocus)
                                                      selectAll()
                        }
                    }
                    Component {
                        id: booleanEditor
                        Switch {
                            id: valueEdit
                            anchors.fill: parent
                            visible: activeFocus
                            text: checked
                            padding: 8
                            checked: d.value
                        }
                    }
                }
            }
        }
    }
}
