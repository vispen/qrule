import QtQuick 2.3
import QtQuick.Window 2.2

Window {
    id: ident1
    visible: true
    anchor.fill: parent   
    Item {
        function fname(a, b) {
               var Z = {asd: 123};
           }
    }
    Item{
    id: window1
    	height: 100
    	width: 200
    	//visible: ident1.visible
    }
}
