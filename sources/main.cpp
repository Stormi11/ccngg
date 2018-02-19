//
// Created by p.weisser on 26.01.2018.
//
/**/
#include <TGUI/TGUI.hpp>
#include <windows.h>


#include "Utilities.h"


//#define ICINGA_API_FILE ...



tgui::MenuBar::Ptr init_menubar();

tgui::Panel::Ptr init_services(tgui::Group::Ptr services_arr[MAX_ELEMENTS_SERVICES],
                               tgui::Button::Ptr button[MAX_ELEMENTS_SERVICES],
                               tgui::Label::Ptr label[MAX_ELEMENTS_SERVICES][6]);

tgui::Panel::Ptr hosts();

void refresh_services(tgui::Label::Ptr label[MAX_ELEMENTS_SERVICES][6],
                      tgui::Button::Ptr button[MAX_ELEMENTS_SERVICES]);

void acknowledgetest()


{
    //system(command_s.c_str()) ;
    std::string whole ("map-1@map-server-beijing-1");
    std::size_t found = whole.rfind('@');
    std::string service (whole.substr(0,found));
    std::string host (whole.substr(found + 1));
    std::cout << host << '!' << service << std::endl;

}




int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Icinga2 GUI");
    window.setFramerateLimit(60);

    tgui::Gui gui(window);

    tgui::Theme theme{"../themes/Black.txt"};
    tgui::Theme::setDefault(&theme);
    gui.add(tgui::Picture::create("../themes/TechniSat.jpg"));

    tgui::Group::Ptr services_arr [MAX_ELEMENTS_SERVICES];
    tgui::Button::Ptr button [MAX_ELEMENTS_SERVICES];
    tgui::Label::Ptr label [MAX_ELEMENTS_SERVICES][6];

    gui.add(init_services(services_arr,button,label));
    gui.add(hosts());

    gui.add(init_menubar());



    //gui.add(fast_ack_window.get_window());
   // std::cout << var_curl << std::endl;

    //acknowledgetest();
     while (window.isOpen())
    {

        ///refreshes services every XX seconds

         if (gui_clock.get_time_as_seconds() > REFRESH_TIME_IN_SECONDS)
        {
            std::cout<< "refreshed" << std::endl;
            refresh_services(label,button);
            gui_clock.restart();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //if ((event.type==sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::LControl))
              //  std::cout << "krasse scheisse" << std::endl;

            gui.handleEvent(event);
        }



        window.clear();
        gui.draw();
        window.display();
    }

    return EXIT_SUCCESS;
}
//*/
/*/
#include <iostream>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

int main()
{
    std::ifstream i("C:/icingaGUI/cmake-build-debug/data/result.json");
    json j;
    i >> j;
    //json n = j.at("results");
    std::ofstream o("C:/icingaGUI/cmake-build-debug/data/pretty.json");
    o<<std::setw(4)<<j<<std::endl;
}
//*/