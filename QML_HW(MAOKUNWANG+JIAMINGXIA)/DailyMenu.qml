import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: dailyMenu
    width: 400
    height: 800
    implicitWidth: 400
    implicitHeight: 300
    header: Label {
        text: qsTr("Daily Menu Detail")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 30
        wrapMode: Text.NoWrap
        fontSizeMode: Text.HorizontalFit
        textFormat: Text.AutoText
        horizontalAlignment: Text.AlignHCenter
        padding: 10
    }

    Column {
        x: 0
        y: 386
        width: 355
        height: 156
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            font.pointSize: 24
            style: Text.Outline
            text: "Pork(Recommended)"
        }
        Text {
            font.pointSize: 24
            text: "Beef"
            style: Text.Raised
            styleColor: "#AAAAAA"
        }
        Text {
            font.pointSize: 24
            text: "Chicken"

            styleColor: "red"
        }
        Text {
            font.pointSize: 24
            text: "Fish"
            style: Text.Sunken
            styleColor: "#AAAAAA"
        }
    }
}
