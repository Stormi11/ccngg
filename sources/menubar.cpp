//
// Created by p.weisser on 13.02.2018.
//

//
// Created by p.weisser on 26.01.2018.
//
#include <TGUI/TGUI.hpp>
#include <iostream>

void signal_Handler_menu (std::string& item)
{
    if (item == "Einstellungen")
        std::cout << "JAAAAAA" << std::endl;
    if (item == "Exit")
        std::cout << "ALARM" << std::endl;
}

tgui::MenuBar::Ptr init_menubar ()
{
    tgui::MenuBar::Ptr menu = tgui::MenuBar::create(); ///create the Menubar
    menu->setSize("100%","3%");

    ///add Menu Datei & assigning it to its signal-function
    menu->addMenu("Datei");
    menu->addMenuItem("Datei", "Einstellungen");
    menu->addMenuItem("Datei", "Exit");

    menu->connect("MenuItemClicked", [](std::string item){ signal_Handler_menu(item); });



    menu->addMenu("Downtimeplaner");

    menu->addMenu("Hilfe");
    return menu;
}
