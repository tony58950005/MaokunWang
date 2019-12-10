import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import Restaurant 1.0

ColumnLayout {
    Frame {
        ListView {
            implicitWidth: 400
            implicitHeight: 300
            clip: true //outside is not visible\
            header: Label {
                text: qsTr("Booking Detail")
                font.pixelSize: 30
                wrapMode: Text.NoWrap
                fontSizeMode: Text.HorizontalFit
                textFormat: Text.AutoText
                horizontalAlignment: Text.AlignHCenter
                //horizontalAlignment: Text.AlignHCenter
                padding: 10
            }
            // anchors.fill: parent
            model: RestaurantTableModel {
                list: restaurantModel
            }


            /*ListModel
            {

                    ListElement
                    {
                        done:true
                        description: "Table 1"

                    }

                    ListElement
                    {
                        done:true
                        description: "Table 2"

                    }

                    ListElement
                    {
                        done:true
                        description: "Table 3"

                    }

                    ListElement
                    {
                        done:true
                        description: "Table 4"

                    }

                }*/
            delegate: RowLayout {
                width: parent.width
                CheckBox {
                    checked: model.done
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description //will be stored in the model in textfield
                    onEditingFinished: model.desription = text
                    Layout.fillWidth: true // make the TextField as wide as possible
                }
            }
        }
    }

    RowLayout {
        // RowLayout
        //{
        Button {
            text: qsTr("Add new reservation   ")
            onClicked: restaurantModel.appendItem()
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Remove reservation   ")
            onClicked: restaurantModel.removeCompletedItems()
            Layout.fillWidth: true
        }
        // }
        Button {
            text: qsTr("QUIT")
            Layout.fillWidth: true
            onClicked: Qt.quit()
        }
    }
}
/*Page {
    width: 600
    height: 400

    header: Label {
        text: qsTr("Page 1")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Label {
        text: qsTr("You are on Page 1.")
        anchors.centerIn: parent
    }
}
*/

