//
// Created by p.weisser on 29.01.2018.
//
#include <TGUI/TGUI.hpp>
#include "json.hpp"
#include <iostream>
#include <fstream>

#define ICINGA_API_FILE "data/result.json"
#define TIME_FACTOR (1)

using json = nlohmann::json;

std::string convert_time(int unixtime)
{

    if (unixtime<1500000)
        return "n/a";

    int rest;
    rest = unixtime % (60 * 60 * 24 );

    int hour_int;
    hour_int = rest / (60*60) + TIME_FACTOR;

    int minute_int;
    minute_int = rest % (60*60) / 60;



    std::string hour_str;

    if (hour_int >= 10)
        hour_str = std::to_string(hour_int);
    else
        hour_str = '0' + std::to_string(hour_int);

    std::string minute_str;

    if (minute_int >= 10)
        minute_str = std::to_string(minute_int);
    else
        minute_str = '0' + std::to_string(minute_int);


    return hour_str + ':' + minute_str;
}
std::string convert_time_special(int lo_time, int ref_time)
{
    if (lo_time<1500000)
        return "n/a";

    int lo_days;
    int ref_days;

    lo_days = lo_time / (60 * 60 * 24);
    ref_days = ref_time / (60 * 60 * 24);
    if (lo_days - ref_days == 0)
        return convert_time(lo_time);
    else
        return  convert_time(lo_time) + '+' + std::to_string(ref_days - lo_days) + 'd';
}
void command()
{
    system("curl -k -s -u root:icinga \"https://192.168.33.5:5665/v1/objects/services?"
                   "filter=service.state!=0"
                   "&all_joins=1"
                   "&attrs=acknowledgement"
                   "&attrs=name"
                   "&attrs=downtime_depth"
                   "&attrs=last_check"
                   "&attrs=next_check"
                   "&attrs=last_state_ok"
                   "&attrs=state"
                   "&attrs=last_check_result"
                   "&last_check_result=output\" -o data/result.json");
   // "&joins=host.state"
     //       "&joins=host.name"
}


float active_tab (float input)
{
    static float s_active_tab = 0.0;
    if (input == 33)
        return s_active_tab;
    else if ((input == 0) || (input == 1) || (input == 2))
        s_active_tab = input;
    else
        std::cerr << "MISTAKES WERE MADE -> fuction \"active_tab\" from services.cpp accessed with wrong input"<< std::endl;
}
void dropdown_service_handler (std::string& item)
{

    if (item == "New")
        active_tab(0.0);
    else if (item == "Acknowledged")
        active_tab(1.0);

    else if (item == "Overdue")
        active_tab(2.0);
    else
        std::cerr << "Could not find tab in Dropdown" << std::endl;
}

void refresh_services(tgui::Label::Ptr label[31][6],tgui::Button::Ptr button[31])
{
    static float s_tab;
    s_tab = active_tab(33);

    command();

    std::ifstream loaded_files(ICINGA_API_FILE);
    json all_hosts;
    json temp_service;
    loaded_files >> all_hosts;
    all_hosts = all_hosts.at("results");

    int current_element = 0;
    int current_service = 0;

    for(;current_element<31;current_service++)
    {
        if (all_hosts[current_service]["joins"]["host"]["state"] != nullptr)
        {

            if ((all_hosts[current_service]["joins"]["host"]["state"].get<float>() == 0.0)
                && all_hosts[current_service]["attrs"]["state"].get<float>() == 2.0
                && all_hosts[current_service]["attrs"]["acknowledgement"].get<float>() == s_tab)
            {

                temp_service = all_hosts[current_service].at("attrs");
                button[current_element]->show();

                label[current_element][0]->setText(temp_service["name"].get<std::string>()
                                                   + '@'
                                                   + all_hosts[current_service]["joins"]["host"]["name"].get<std::string>());
                label[current_element][0]->show();
                label[current_element][1]->setText("->" + temp_service["last_check_result"]["output"].get<std::string>());
                label[current_element][1]->show();
                label[current_element][2]->setText("LC: " + convert_time(temp_service["last_check"].get<int>()));

                label[current_element][2]->show();
                label[current_element][3]->setText("NC: " + convert_time(temp_service["next_check"].get<int>()));
                label[current_element][3]->show();
                label[current_element][4]->setText("LO: " + convert_time_special(temp_service["last_state_ok"].get<int>(),
                                                                                 temp_service["last_check"].get<int>()));
                label[current_element][4]->show();
                current_element++;

            }

            //else if (all_hosts[j]["attrs"]["name"] == "")
            //     break;
        }
        else
        {
            while (current_element < 31)
            {
                label[current_element][0]->hide();
                label[current_element][1]->hide();
                label[current_element][2]->hide();
                label[current_element][3]->hide();
                label[current_element][4]->hide();
                button[current_element]->hide();
                current_element++;
            }
            break;
        }
    }
}

tgui::Panel::Ptr init_services(tgui::Group::Ptr services[31],
                               tgui::Button::Ptr button[31],
                               tgui::Label::Ptr label[31][6])
{

    command();

    tgui::Panel::Ptr p_services = tgui::Panel::create({"98%","64%"});
    p_services->setPosition("1%", "4%");

    tgui::Group::Ptr services_left = tgui::Group::create({"100%", "100%"});
    services_left->setPosition("1%", "1%");

    tgui::Group::Ptr services_right = tgui::Group::create({"100%", "100%"});
    services_right->setPosition("51%", "1%");




    std::ifstream loaded_files(ICINGA_API_FILE);
    json all_hosts;
    json single_host;
    loaded_files >> all_hosts;
    all_hosts = all_hosts.at("results");


    //std::ofstream o("Z:/pretty.json");
    //o<< std::setw(4) << single_host << std::endl;

    json temp_service;

    for(int i=0;i<31;i++)
    {

        services[i] = tgui::Group::create({"100%", "10%"});

        button[i]   =  tgui::Button::create();
        button[i]   -> setPosition({"47.3%", "10%"});
        button[i]   -> setSize({"18", "18"});
        button[i]   -> hide();
        services[i] -> add(button[i]);


        temp_service = all_hosts[i].at("attrs");
        //auto test = temp["name"].get<std::string>();

        ///service(at)host
        label[i][0] =  tgui::Label::create();
        label[i][0] -> setPosition({"0%,0%"});
        label[i][0] -> setTextSize(14);
        label[i][0] ->hide();
        services[i] -> add(label[i][0]);

        ///what problem
        label[i][1] = tgui::Label::create();
        label[i][1]->setTextSize(8);
        label[i][1]->setPosition({"4%", "34%"});
        label[i][1] ->hide();
        services[i]->add(label[i][1]);

        //unixTimeConvert(static_cast<unsigned long int>(temp_service["last_check"].get<int>()), temp_hour, temp_minute);
        //std::cout << temp_service["last_check"].get<int>();
        ///last_check label
        label[i][2] = tgui::Label::create();
        label[i][2]->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        label[i][2]->setTextSize(8);
        label[i][2]->setPosition({"44%", "10%"});
        label[i][2] ->hide();
        services[i]->add(label[i][2]);

        ///next_check Label
        label[i][3] = tgui::Label::create();
        label[i][3]->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
        label[i][3]->setTextSize(8);
        label[i][3]->setPosition({"44%", "30%"});
        label[i][3] ->hide();
        services[i]->add(label[i][3]);

        ///down_since label
        label[i][4] = tgui::Label::create();
        label[i][4]->setTextSize(8);
        label[i][4]->setPosition({"0.1%", "34%"});
        label[i][4] ->hide();
        services[i]->add(label[i][4]);

        if (i<16)
        {
            services_left->add(services[i]);
            services[i]->setPosition({"0%", std::to_string(i * 6 + 1) + "%"});
        }
        else
        {
            services[i]->setPosition({"0%", std::to_string((i-16) * 6 + 1) + "%"});
            services_right->add(services[i]);
        }
    }
    tgui::ComboBox::Ptr dropdown = tgui::ComboBox::create();
    dropdown->setPosition({"0%","91%"});
    dropdown->addItem("New");
    dropdown->setSelectedItem("New");
    dropdown->addItem("Acknowledged");
    dropdown->addItem("Overdue");
    dropdown->connect("ItemSelected", [](std::string item){ dropdown_service_handler(item); });
    services_right->add(dropdown);

    p_services->add(services_right);
    p_services->add(services_left);

    refresh_services(label,button);

    return p_services;
}

