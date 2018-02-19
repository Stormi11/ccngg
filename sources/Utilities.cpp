//
// Created by p.weisser on 14.02.2018.
//

#include <fstream>
#include "Utilities.h"

///CLOCK////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Clock gui_clock;

Clock::Clock()
{
    m_factor = 0;
}

void Clock::restart()
{
    m_clock.restart();
    m_factor = 0;
}

int Clock::ischanged() {

    return m_factor;

}

float Clock::get_time_as_seconds() {

    return m_clock.getElapsedTime().asSeconds() + ischanged();

}

void Clock::change(int value) {
        m_factor+=value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Config///////////////////////////////////////////////////////////////////////////////////////////////////////////////

Config config;

Config::Config()
{
    std::ifstream loaded_files("data/config.json");
    loaded_files >> m_config;
}

std::string Config::get_apiusername()
{
    return m_config["apiuser"]["name"];
}

std::string Config::get_apiuserpassword()
{
    return m_config["apiuser"]["password"];
}

std::string Config::get_username()
{
    return m_config["user"]["name"];
}

std::string Config::get_address()
{
    return m_config["address"]["url"];
}

int Config::get_window_height()
{
    return m_config["resolution"]["window_height"];
}

int Config::get_window_width()
{
    return m_config["resolution"]["window_width"];
}