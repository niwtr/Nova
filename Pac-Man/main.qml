import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

import CustomGeometry 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Pan-Man")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

    }

    Actor{

    }

    footer: TabBar {
        id: tabBar
    }
}
