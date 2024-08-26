import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Repeater {
            model: ["Лёгкая", "Средняя", "Сложная", "Экстрим", "Безумие"]
            Label {
                text: modelData + ": лучшее время: ?"
                Layout.fillWidth: true
            }
        }
    }
}
