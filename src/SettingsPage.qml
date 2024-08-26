import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        ComboBox {
            id: musicComboBox
            model: ["Пак#1 (2 шт. Общие)"]
            Layout.fillWidth: true
        }

        Label {
            text: "Уровень звука: " + volumeSlider.value.toFixed(0) + "%"
        }

        Slider {
            id: volumeSlider
            from: 0
            to: 100
            value: 25
            Layout.fillWidth: true
        }

        CheckBox {
            text: "Подсмотреть поле в конце игры"
        }
    }
}
