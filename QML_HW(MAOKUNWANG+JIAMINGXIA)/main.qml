import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 500
    height: 480
    title: qsTr("QML_HOMEWORK by (JIAMING XIA+MAOKUN WANG)")

    function showMenuPage() {
        panelLoader.setSource("qrc:/DailyMenu.qml")
    }
    function showTablePage() {
        panelLoader.setSource("qrc:/RestaurantTable.qml")
    }
    SwipeView {
        id: swipeView
        anchors.rightMargin: 0
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        RestaurantTable {
            anchors.centerIn: parent

            //anchors.fill: parent
        }
    }
    Loader {
        id: panelLoader
        //anchors.top: headRect.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        function setSource(source, vehicleComponent) {
            panelLoader.vehicleComponent = vehicleComponent
            panelLoader.source = source
        }

        function setSourceComponent(sourceComponent, vehicleComponent) {
            panelLoader.vehicleComponent = vehicleComponent
            panelLoader.sourceComponent = sourceComponent
        }

        property var vehicleComponent
    }
    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Table+Guests")
            onClicked: {
                showTablePage()
            }
        }
        TabButton {
            text: qsTr("Daily Menu")
            onClicked: {
                showMenuPage()
            }
        }
    }
}
