// MainWindow.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Minesweeper")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Text {
            text: "Minesweeper"
            font.pixelSize: 24
            Layout.alignment: Qt.AlignHCenter
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter
            RowLayout {
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter

                ToolButton {
                    id: recordsButton
                    icon.source: "qrc:/images/trophy.png"
                    onClicked: stackView.currentIndex = 2
                }

                ComboBox {
                    id: difficultyComboBox
                    model: ["Выберите сложность", "Лёгкая", "Средняя", "Сложная", "Экстрим", "Безумие", "Своя"]
                    onCurrentIndexChanged: {
                        if (currentIndex > 0) {
                            startButton.enabled = true
                            if (currentIndex === 1) {
                                difficultyComboBox.model[0] = "Выберите сложность (неактивно)"
                            }
                        }
                        if (currentIndex === 6) {
                            stackView.currentIndex = 1
                        } else {
                            stackView.currentIndex = 0
                        }
                    }
                }

                ToolButton {
                    id: settingsButton
                    icon.source: "qrc:/images/settings.png"
                    onClicked: stackView.currentIndex = 0
                }
            }

            StackLayout {
                id: stackView
                Layout.fillWidth: true
                Layout.fillHeight: true

                SettingsPage {}
                CustomGamePage {}
                RecordsPage {}
            }

            Button {
                id: startButton
                text: "Играть"
                enabled: false
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    // Здесь будет логика запуска игры
                    console.log("Начало игры с выбранной сложностью:", difficultyComboBox.currentText)
                }
            }

            Button {
                text: "Выйти"
                Layout.alignment: Qt.AlignHCenter
                onClicked: Qt.quit()
            }
        }
    }
}
