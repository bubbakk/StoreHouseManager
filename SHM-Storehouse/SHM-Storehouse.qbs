import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        Depends { name: "Qt.core" }
        Depends { name: "Qt.gui" }
        Depends { name: "Qt.network" }

        cpp.cxxLanguageVersion: "c++11"

        cpp.defines: [
            // The following define makes your compiler emit warnings if you use
            // any feature of Qt which as been marked deprecated (the exact warnings
            // depend on your compiler). Please consult the documentation of the
            // deprecated API in order to know how to port your code away from it.
            "QT_DEPRECATED_WARNINGS",

            // You can also make your code fail to compile if you use deprecated APIs.
            // In order to do so, uncomment the following line.
            // You can also select to disable deprecated APIs only up to a certain version of Qt.
            //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        consoleApplication: true
        files: [
            "../sharedcode/chat.cpp",
            "../sharedcode/chat.h",
            "../sharedcode/messagehandler.h",
            "../sharedcode/shmrequest.cpp",
            "../sharedcode/shmrequest.h",
            "../sharedcode/shmrequestparser.cpp",
            "../sharedcode/shmrequestparser.h",
            "../sharedcode/tcpServer.cpp",
            "../sharedcode/tcpServer.h",
            "../sharedcode/tcpchat.cpp",
            "../sharedcode/tcpchat.h",
            "HOW_TO_TEST.md",
            "docs/architettura.md",
            "docs/objects_description.md",
            "docs/protocol.md",
            "main.cpp",
            "objectcylinder.cpp",
            "objectcylinder.h",
            "requests/not_valid_json_message.json",
            "requests/valid_json_message.json",
            "requests/valid_json_message_but_empty_array.json",
            "requests/valid_json_message_but_not_array.json",
            "storeobject.cpp",
            "storeobject.h",
            "warehouse.cpp",
            "warehouse.h",
            "warehousemajordomo.cpp",
            "warehousemajordomo.h",
        ]

        Group {     // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
        }
    }
}
