import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "Ширина: " + sliderX.value.toFixed(0)
        }

        Slider {
            id: sliderX
            from: 5
            to: 50
            Layout.fillWidth: true
        }

        ProgressBar {
            id: progressBarX
            value: sliderX.value / 50
            Layout.fillWidth: true
        }

        Label {
            text: "Высота: " + sliderY.value.toFixed(0)
        }

        Slider {
            id: sliderY
            from: 5
            to: 50
            Layout.fillWidth: true
        }

        ProgressBar {
            id: progressBarY
            value: sliderY.value / 50
            Layout.fillWidth: true
        }

        Rectangle {
            id: frame
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "lightgray"
            border.color: "gray"
            border.width: 1
        }
    }
}
