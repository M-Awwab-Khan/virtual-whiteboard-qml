import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: Screen.width
    height: Screen.height
    visible: true
    title: qsTr("OpencvToQml")

    RowLayout {
        id: imageRect
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: parent.height

        Image {
            id: opencvImage
            fillMode: Image.PreserveAspectFit
            source: "image://live/image"
            cache: false
            Layout.maximumHeight: 600
            Layout.maximumWidth: 800

            function reload() {
                source = "image://live/image?id=" + Date.now()
            }
        }

        Image {
            id: whiteboardSpace
            fillMode: Image.PreserveAspectFit
            source: "image://whiteboard/image"
            cache: false
            Layout.maximumHeight: 600
            Layout.maximumWidth: 800
            Layout.alignment: Qt.AlignRight

            function reload() {
                source = "image://whiteboard/image?id=" + Date.now()
            }
        }
    }

    Button {
        text: "Clear Whiteboard"
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        onClicked: WhiteboardManager.clearWhiteboard()
    }

    Button {
        text: "Save Snapshot"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onClicked: {
            var filePath = "snapshot.png"
            WhiteboardManager.saveSnapshot(filePath)
            console.log("Snapshot saved to " + filePath)
        }
    }

    Connections{

        target: liveImageProvider
        function onImageChanged() {
            opencvImage.reload()
        }

    }

    Connections {
        target: whiteboardImageProvider
        function onImageChanged() {
            whiteboardSpace.reload()
        }
    }
}