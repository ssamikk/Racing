import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 300; height: 150
    Button {
        height: 100
        width: 100
        text: "lol"
    }
    Canvas {
            id: cloud
            anchors.fill: parent

            onPaint: {
                var ctx = getContext("2d");
                ctx.beginPath();
                var x = 100;
                var y = 170;
                ctx.arc(x, y, 60, Math.PI * 0.5, Math.PI * 1.5);
                ctx.arc(x + 70, y - 60, 70, Math.PI * 1, Math.PI * 1.85);
                ctx.arc(x + 152, y - 45, 50, Math.PI * 1.37, Math.PI * 1.91);
                ctx.arc(x + 200, y, 60, Math.PI * 1.5, Math.PI * 0.5);
                ctx.moveTo(x + 200, y + 60);
                ctx.lineTo(x, y + 60);
                ctx.strokeStyle = "#797874";
                ctx.stroke();
                ctx.fillStyle = "#8ED6FF";
                ctx.fill();
            }
        }
}
