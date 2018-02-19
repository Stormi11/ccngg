//
// Created by p.weisser on 14.02.2018.
//
#include "FastAckWindow.h"


FastAckWindow::FastAckWindow(std::string service_name) {


    m_window = tgui::ChildWindow::create();
    m_window->setTitle("Fast Acknowledge");
    m_window->setSize({"30%", "20%"});
    m_window->setPosition({"35%", "40%"});

    m_text_box = tgui::TextBox::create();
    m_window->add(m_text_box, "fast_ack_textbox");
    m_text_box->setText("Comment: This post was acknowledged by USERNAME");
    m_text_box->setSize({"95%", "50%"});
    m_text_box->setPosition({"2.5%", "2.5%"});

    m_sticky = tgui::CheckBox::create();
    m_window->add(m_sticky, "fast_ack_sticky");
    m_sticky->setText("Sticky?");
    m_sticky->setSize("5%", "10%");
    m_sticky->setPosition({"2.5%", "55%"});

    m_timelimit = tgui::CheckBox::create();
    m_window->add(m_timelimit, "fast_ack_timelimit");
    m_timelimit->setText("Ablaudatum?");
    m_timelimit->setSize("5%", "10%");
    m_timelimit->setPosition({"47.5%", "55%"});

    m_timelimit_group = tgui::Group::create();
    m_timelimit_group->hide();

    m_timelimit->connect("Checked",&FastAckWindow::timelimit_checked_handler, this, m_timelimit_group);
    m_timelimit->connect("Unchecked",&FastAckWindow::timelimit_unchecked_handler, this, m_timelimit_group);

    m_timelimit_hour = tgui::EditBox::create();
    m_timelimit_group->add(m_timelimit_hour, "fast_ack_timelimit_hour");
    m_timelimit_hour->setSize({"7.5%","12%"});
    m_timelimit_hour->setPosition({"2.5%","67.5%"});

    m_timelimit_colon = tgui::Label::create(':');
    m_timelimit_group->add(m_timelimit_colon);
    m_timelimit_colon->setSize({"3%","12%"});
    m_timelimit_colon->setTextSize(16);
    m_timelimit_colon->setPosition({"10%","65.5%"});

    m_timelimit_minute = tgui::EditBox::create();
    m_timelimit_group->add(m_timelimit_minute, "fast_ack_timelimit_minute");
    m_timelimit_minute->setSize({"7.5%","12%"});
    m_timelimit_minute->setPosition({"12%","67.5%"});

    m_timelimit_day = tgui::EditBox::create();
    m_timelimit_group->add(m_timelimit_day, "fast_ack_timelimit_day");
    m_timelimit_day->setSize({"7.5%","12%"});
    m_timelimit_day->setPosition({"25%","67.5%"});

    m_timelimit_point1 = tgui::Label::create('.');
    m_timelimit_group->add(m_timelimit_point1);
    m_timelimit_point1->setSize({"3%","12%"});
    m_timelimit_point1->setTextSize(16);
    m_timelimit_point1->setPosition({"31.75%","65.5%"});

    m_timelimit_month = tgui::EditBox::create();
    m_timelimit_group->add(m_timelimit_month, "fast_ack_timelimit_month");
    m_timelimit_month->setSize({"7.5%","12%"});
    m_timelimit_month->setPosition({"33.5%","67.5%"});

    m_timelimit_point2 = tgui::Label::create('.');
    m_timelimit_group->add(m_timelimit_point2);
    m_timelimit_point2->setSize({"3%","12%"});
    m_timelimit_point2->setTextSize(16);
    m_timelimit_point2->setPosition({"40.25%","65.5%"});

    m_timelimit_year = tgui::EditBox::create();
    m_timelimit_group->add(m_timelimit_year, "fast_ack_timelimit_year");
    m_timelimit_year->setSize({"12%","12%"});
    m_timelimit_year->setPosition({"42%","67.5%"});

    m_window->add(m_timelimit_group, "fast_ack_group");

    m_submit_button = tgui::Button::create();
    m_window->add(m_submit_button, "fast_ack_submitbutton");
    m_submit_button->setSize({"40%", "17%"});
    m_submit_button->setPosition({"30%", "80.5%"});
    m_submit_button->setText("Submit");

    m_submit_button->connect("Pressed",&FastAckWindow::submit_button_handler, this, m_window);

    m_invalid_window = tgui::ChildWindow::create();
    m_window->add(m_invalid_window, "fast_ack_invalid_window");
    m_invalid_window->hide();
    m_invalid_window->setTitleButtons(0);
    m_invalid_window ->setTitle("Invalid input...");
    m_invalid_window->setSize({"80%","80%"});
    m_invalid_window->setPosition({"10%","5%"});

    m_invalid_button = tgui::Button::create();
    m_invalid_window->add(m_invalid_button,"fast_ack_invalid_button");
    m_invalid_button->setText("OK");
    m_invalid_button->setSize({"50%","30%"});
    m_invalid_button->setPosition({"25%","60%"});
    m_invalid_button->connect("Pressed",&FastAckWindow::invalid_input_close, this, m_invalid_window);

    m_invalid_label  = tgui::Label::create();
    m_invalid_window->add(m_invalid_label,"fast_ack_invalid_label");
    m_invalid_label->setSize({"90%","30%"});
    m_invalid_label->setText("The given time was wrong.\nPlease try again :)");
    m_invalid_label->setTextSize(16);
    m_invalid_label->setPosition({"5%","5%"});
    m_invalid_label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);

    m_service_name=service_name;

}

void FastAckWindow::submit_button_handler(tgui::ChildWindow::Ptr window) {
    std::cout << "submit_button_handler called" << std::endl;


    auto box = window->get<tgui::TextBox>("fast_ack_textbox");
    std::string comment = box->getText();

    auto sticky = window->get<tgui::CheckBox>("fast_ack_sticky");
    bool is_sticky = sticky->isChecked();

    auto timelimit = window->get<tgui::CheckBox>("fast_ack_timelimit");
    bool is_timelimit = timelimit->isChecked();
    tm tmp_tm{0};
    tm *timelimit_tm = &tmp_tm;

    bool valid_input(true);

    if (is_timelimit) {
        auto timelimit_hour = window->get<tgui::EditBox>("fast_ack_timelimit_hour");
        std::string hour_s = timelimit_hour->getText();
        timelimit_tm->tm_hour = std::stoi(hour_s);
        if ((timelimit_tm->tm_hour > 23) || (timelimit_tm->tm_hour < 0))
            valid_input = false;

        auto timelimit_minute = window->get<tgui::EditBox>("fast_ack_timelimit_minute");
        std::string minute_s = timelimit_minute->getText();
        timelimit_tm->tm_min = std::stoi(minute_s);
        //timelimit_tm->tm_min = 5;
        if ((timelimit_tm->tm_min > 59) || (timelimit_tm->tm_min < 0))
            valid_input = false;

        auto timelimit_day = window->get<tgui::EditBox>("fast_ack_timelimit_day");
        std::string day_s = timelimit_day->getText();
        timelimit_tm->tm_mday = std::stoi(day_s);
        if (timelimit_tm->tm_mday > 31 || timelimit_tm->tm_mday < 1)
            valid_input = false;

        auto timelimit_month = window->get<tgui::EditBox>("fast_ack_timelimit_month");
        std::string month_s = timelimit_month->getText();
        timelimit_tm->tm_mon = std::stoi(month_s) - 1;
        if (timelimit_tm->tm_mon > 12 || timelimit_tm->tm_mon < 1)
            valid_input = false;

        auto timelimit_year = window->get<tgui::EditBox>("fast_ack_timelimit_year");
        std::string year_s = timelimit_year->getText();
        timelimit_tm->tm_year = std::stoi(year_s) - 1900;
        if (timelimit_tm->tm_year < 118)
            valid_input = false;

        time_t now;
        time(&now);
        if (difftime(mktime(timelimit_tm), now) <= 0)
            valid_input = false;
        std::cout << " difference is: " << difftime(mktime(timelimit_tm), now) << std::endl;
    }
    if (!valid_input) {

        FastAckWindow::invalid_input_caller(window);
        return;
    }

    FastAckWindow::post_input(comment);


        std::cout << "valid input? " << valid_input << std::endl;

        /*std::cout << comment << " + stick ist set to : " << is_sticky << " and timelimit is set to: " << is_timelimit
                  << ' ' << std::to_string(timelimit_tm->tm_hour) << std::endl;
        */FastAckWindow::valid_input_caller(window);
        //window->destroy();


}
void FastAckWindow::timelimit_checked_handler(tgui::Group::Ptr group)
{

    group -> show();

    time_t  system_time_unix;
    time(&system_time_unix);
    system_time_unix += 60*60; //sets time 1h ahead of the current time
    tm * system_time;
    system_time = localtime(&system_time_unix);

    auto hour = group->get<tgui::EditBox>("fast_ack_timelimit_hour");
    if (system_time->tm_hour > 9)
        hour->setText(std::to_string(system_time->tm_hour));
    else
        hour->setText('0' + std::to_string(system_time->tm_hour));

    auto minute = group->get<tgui::EditBox>("fast_ack_timelimit_minute");
    if (system_time->tm_min > 9)
        minute->setText(std::to_string(system_time->tm_min));
    else
        minute->setText('0' + std::to_string(system_time->tm_min));

    auto day = group->get<tgui::EditBox>("fast_ack_timelimit_day");
    day->setText(std::to_string(system_time->tm_mday));

    auto month = group->get<tgui::EditBox>("fast_ack_timelimit_month");
    month->setText(std::to_string(system_time->tm_mon + 1));

    auto year = group->get<tgui::EditBox>("fast_ack_timelimit_year");
    year->setText(std::to_string(system_time->tm_year + 1900));
}

void FastAckWindow::timelimit_unchecked_handler(tgui::Group::Ptr group)
{
    group -> hide();
}

void FastAckWindow::invalid_input_caller(tgui::ChildWindow::Ptr fast_ack_window)
{

    auto invalid_window = fast_ack_window->get<tgui::ChildWindow>("fast_ack_invalid_window");
    invalid_window->show();
    fast_ack_window->setTitle("Invalid Input...");
    timelimit_checked_handler(fast_ack_window->get<tgui::Group>("fast_ack_group"));

}

void FastAckWindow::valid_input_caller(tgui::ChildWindow::Ptr window)
{
    auto invalid_window = window->get<tgui::ChildWindow>("fast_ack_invalid_window");
    invalid_window->show();
    invalid_window->setTitle("Success!");
    (window->get<tgui::Label>("fast_ack_invalid_label"))->setText("Acknowledgement has been set :)");
    (window->get<tgui::Button>("fast_ack_invalid_button"))->connect("Pressed",&FastAckWindow::window_destroy, this, window);
}

void FastAckWindow::post_input(std::string comment) {
    std::cout << m_service_name << std::endl;
     //std::string whole = m_service_name;
    //std::size_t pos = whole.rfind('@');
    //std::string service (whole.substr(0,pos));
   // std::string host (whole.substr(pos + 1));
    //std::cout << host << '!' << service << std::endl;

   /* std::string var_curl (R"(curl -k -s -u )" + config.get_apiusername() + ':' + config.get_apiuserpassword()+
                          R"( -H "accept: application/json" -X POST ")" + config.get_address() +
                          R"(actions/acknowledge-problem?service=)" + host + '!' + service + " -d )");

//std::string var_curl (R"(curl -k -s -u root:icinga -H "accept: application/json" -X POST "https://192.168.33.5:5665/v1/actions/acknowledge-problem?type=Service&filter=service.state==2&service.state_type=1" -d )");
    std::string var_json1 (R"(\"author\":)" + config.get_username());
    std::string var_json2 (R"(\"comment\":)" + comment);
    std::string var_json3 (R"(\"notify\": true)");

    std::string command_s ( var_curl + "\"{" + var_json1 + "," + var_json2 + "," + var_json3 + "}\"");
    system(command_s.c_str());
*/
}

void FastAckWindow::invalid_input_close(tgui::ChildWindow::Ptr window)
{
    window->hide();
}

void FastAckWindow::window_destroy(tgui::ChildWindow::Ptr window)
{
    window->destroy();
}
