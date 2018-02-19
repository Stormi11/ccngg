//
// Created by p.weisser on 14.02.2018.
//

#ifndef ICINGAGUI_UTILITIES_H
#define ICINGAGUI_UTILITIES_H

#include <TGUI/TGUI.hpp>
#include <SFML/System.hpp>
#include "json.hpp"
#include <iostream>

///defines//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define WINDOW_WIDTH (1366)
#define WINDOW_HEIGHT (768)
#define MAX_ELEMENTS_SERVICES (31)
#define REFRESH_TIME_IN_SECONDS (10)
#define ICINGA_API_FILE "data/result.json"

using json = nlohmann::json;

///This class creates a custom clock, using the in SFML build in clock
///just needed to rewrite it, so that i can force a refresh at any time with doing nothing more than adding seconds
///to this clock

class Clock {
private:
     sf::Clock m_clock;
     int m_factor;

public:
    Clock();

    void restart();

    int ischanged();

    float get_time_as_seconds();

    void change(int value);

};

extern Clock gui_clock;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Config{
private:
    json m_config;
public:
    Config();

    std::string get_apiusername();

    std::string get_apiuserpassword();

    std::string get_username();

    std::string get_address();

    int get_window_height();

    int get_window_width();

};

extern Config config;

class Commandbuilder {
private:
    json m_config;
public:
    void load_config();
};

#endif //ICINGAGUI_UTILITIES_H
