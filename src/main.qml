import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 760; height: 340
//    MultiPointTouchArea {
//        anchors.fill: parent
//        minimumTouchPoints: 1
//        maximumTouchPoints: 5
//        touchPoints: [
//            TouchPoint {
//                id: pointId1
//            },
//            TouchPoint {
//                id: pointId2
//            },
//            TouchPoint {
//                id: pointId3
//            },
//            TouchPoint {
//                id: pointId4
//            },
//            TouchPoint {
//                id: pointId5
//            }
//        ]
//        Repeater {
//            model: parent.touchPoints
//            Rectangle {
//                color: "white";
//                x: modelData.x;
//                y: modelData.y;
//                width: 70;
//                height: 30
//                visible: modelData.pressed
//            }
//        }
//    }
    Button {
        id: buttonRedo
        objectName: "buttonRedo"
        x: 51
        y: 215
        width: 77
        height: 64
        text: qsTr("redo")
        signal pressedMy()
        onPressed: pressedMy()
        signal relessedMy()
        onReleased: relessedMy()
    }

    Button {
        id: buttonBeck
        objectName: "buttonBeck"
        x: 51
        y: 280
        width: 77
        height: 52
        text: qsTr("beck")
        signal pressedMy()
        onPressed: pressedMy()
        signal relessedMy()
        onReleased: relessedMy()
    }

    Button {
        id: buttonLeft
        objectName: "buttonLeft"
        x: 498
        y: 236
        width: 81
        height: 76
        text: qsTr("left")
        signal pressedMy()
        onPressed: pressedMy()
        signal relessedMy()
        onReleased: relessedMy()
    }

    Button {
        id: buttonRight
        objectName: "buttonRight"
        x: 611
        y: 236
        width: 88
        height: 76
        text: qsTr("right")
        signal pressedMy()
        onPressed: pressedMy()
        signal relessedMy()
        onReleased: relessedMy()
    }
}
