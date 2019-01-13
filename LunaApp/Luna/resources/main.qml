import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3
import QtQuick.Window 2.11

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 800
    title: qsTr("Luna")

    Shortcut {
        sequences: ["Esc", "Back"]
        enabled: stackView.depth > 1
        onActivated: {
            stackView.pop()
            listView.currentIndex = -1
        }
    }

    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: stackView.depth > 1 ? "images/back.png" : "images/drawer.png"
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                        listView.currentIndex = -1
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: titleLabel
                text: window.title
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) * 0.4
        height: window.height
        interactive: stackView.depth === 1

        ListView {
            id: listView
            currentIndex: 0
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                   stackView.push(model.source)
                   drawer.close()
               }
            }

            model: ListModel {
                ListElement { title: "Connections"; source: "qrc:/ConnectionsPage.qml"; }
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: TabPage {
            model: Effects
            onTabSelected: Luna.selectEffect(index)
        }
    }
}