import QtQuick 2.9
import QtQuick.Controls 2.2

Item {
    id: root
    width: 760; height: 340

    Button {
        id: buttonRedo
        objectName: "buttonRedo"
        x: 51
        y: 215
        width: 77
        height: 51
        text: qsTr("Вперед")
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
        text: qsTr("Назад")
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
        text: qsTr("Лево")
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
        text: qsTr("Право")
        signal pressedMy()
        onPressed: pressedMy()
        signal relessedMy()
        onReleased: relessedMy()
    }
}
