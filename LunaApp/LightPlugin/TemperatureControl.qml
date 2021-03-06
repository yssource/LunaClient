import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

ColumnLayout {
    RowLayout {
        Label {
            text: qsTr("Color temperature")
        }

        Slider {
            id: temperatureSlider
            Layout.fillWidth: true
            from: 1666
            to: 12000
            value: Model.temperature
            onValueChanged: {
                Model.temperature = value
            }
        }

        Label {
            Layout.minimumWidth: 50
            text: Model.temperature.toFixed(0)
        }
    }

    Item {
        Layout.fillHeight: true
    }
}
