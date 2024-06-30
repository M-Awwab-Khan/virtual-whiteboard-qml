import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform

Window {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("OpencvToQml")

    Button {
        width: 100
        height: 50
        text: "Clear Whiteboard"
        anchors.top: parent.top
        anchors.left: parent.left
        onClicked: WhiteboardManager.clearWhiteboard()
    }

    Button {
        width: 100
        height: 50
        text: "Save Snapshot"
        anchors.top: parent.top
        anchors.right: parent.right
        onClicked: {
            var filePath = "snapshot1.png"
            WhiteboardManager.saveSnapshot(filePath)
            console.log("Snapshot saved to " + filePath)
        }
    }

    Button {
        width: 100
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Upload Image"
        onClicked: {
            fileDialog.open()
            focusArea.focus = true
        }
    }

    FileDialog {
        id: fileDialog
        title: "Select an Image"
        onAccepted: {
            WhiteboardManager.loadImage(fileDialog.file.toString())
            focusArea.focus = true
        }
        onRejected: {
            console.log("Canceled")
            focusArea.focus = true
        }
    }

    RowLayout {
        id: imageRect
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height

        // Image {
        //     id: opencvImage
        //     fillMode: Image.PreserveAspectFit
        //     source: "image://live/image"
        //     cache: false
        //     Layout.maximumHeight: 600
        //     Layout.maximumWidth: 800

        //     function reload() {
        //         source = "image://live/image?id=" + Date.now()
        //     }
        // }
        Item {
            id: focusArea
            Layout.preferredHeight: 600
            Layout.preferredWidth: 800
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
            focus: true
            Keys.onPressed: {
                if (event.key === Qt.Key_Control) {
                    WhiteboardManager.enableDrawing()
                }
            }

            Keys.onReleased: {
                if (event.key === Qt.Key_Control) {
                    WhiteboardManager.disableDrawing()
                }
            }

            Image {
                id: whiteboardSpace
                fillMode: Image.PreserveAspectFit
                source: "image://whiteboard/image"
                cache: false

                function reload() {
                    source = "image://whiteboard/image?id=" + Date.now()
                }
            }
        }
    }

    // Connections {

    //     target: liveImageProvider
    //     function onImageChanged() {
    //         opencvImage.reload()
    //     }
    // }
    Connections {
        target: whiteboardImageProvider
        function onImageChanged() {
            whiteboardSpace.reload()
        }
    }
}
