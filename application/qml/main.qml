import QtQuick 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.1

import "qrc:/qml/components"

import SceneGraphRendering 1.0

Item {
  id: root

  signal toggleHidBindView
  onToggleHidBindView: hid_bind_view.toggle()

  signal updateHeight(string ht)
  onUpdateHeight: heightLabel.text = ht

  Renderer {
    id: renderer

    anchors.fill: parent

    rcpair_name: rc_pair_cb.currentText

    ComboBox {
      id: rc_pair_cb
      anchors.top: parent.top
      anchors.left: parent.left
      anchors.margins: 5

      width: 128

      opacity: 0.7

      model: rc_name_model
      textRole: "display"
    }

    Rectangle
    {
        id: heightBox
        anchors
        {
            margins: 10
            bottom:     parent.bottom
            right:   parent.right
        }

        width:  100
        height: 25

        color:   "#d3d3d3"
        opacity: 0.7

        border.color: "black"
        border.width: 2


        Text
        {
          id: heightLabel
          anchors.centerIn: parent

          function toggle()
          {
              //return scenario.displayHeight()
          }
        }

    }

    Button {
      text: "?"
      anchors.top: parent.top
      anchors.right: parent.right
      anchors.margins: 5

      width: height
      opacity: 0.7

      onClicked: hid_bind_view.toggle()
    }


    HidBindingView {
      id: hid_bind_view
      anchors.fill: parent
      anchors.margins: 50
      visible:false

      states: [
        State{
          name: "show"
          PropertyChanges {
            target: hid_bind_view
            visible: true
          }
        }
      ]

      function toggle() {

        if(state === "") state = "show"
        else state = ""

      }
    }

  }

}

