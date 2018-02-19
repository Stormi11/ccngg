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
std::string var_curl (R"(curl -k -s -u )" + config.get_apiusername() + ':' + config.get_apiuserpassword()+
                              R"( -H "accept: application/json" -X POST ")" + config.get_address() +
                              R"(actions/acknowledge-problem?service=icinga2!disk22" -d )");

//std::string var_curl (R"(curl -k -s -u root:icinga -H "accept: application/json" -X POST "https://192.168.33.5:5665/v1/actions/acknowledge-problem?type=Service&filter=service.state==2&service.state_type=1" -d )");
std::string var_json1 (R"(\"author\": \"icingaadmin\")");
std::string var_json2 (R"(\"comment\": \"Global outage. Working on it.\")");
std::string var_json3 (R"(\"notify\": true)");

std::string command_s ( var_curl + "\"{" + var_json1 + "," + var_json2 + "," + var_json3 + "}\"");

void acknowledgetest()


{
    system(command_s.c_str()) ;
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
        /*
        if (gui.get("testWindow") != nullptr)
            std::cout << "testWindow found :)" << std::endl;
        else
            std::cout << "not found" << std::endl;
        ///refreshes services every XX seconds
        */
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
//**/
/*/
#include <iostream>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

int main()
{
    std::ifstream i("C:/temp/test.json");
    json j;
    i >> j;
    json n = j.at("results");
    std::ofstream o("C:/temp/pretty.json");
    o<<std::setw(4)<<n<<std::endl;
}
//*/