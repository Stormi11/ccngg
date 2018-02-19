//
// Created by p.weisser on 14.02.2018.
//

#ifndef ICINGAGUI_FASTACKWINDOW_H
#define ICINGAGUI_FASTACKWINDOW_H

#include <TGUI/TGUI.hpp>
#include <ctime>
#include <iostream>

class FastAckWindow {
private:
    tgui::ChildWindow::Ptr m_window;

    tgui::TextBox::Ptr m_text_box;
    tgui::Button::Ptr m_submit_button;
    tgui::CheckBox::Ptr m_sticky;
    tgui::CheckBox::Ptr m_timelimit;

    tgui::Group::Ptr m_timelimit_group;

    tgui::Label::Ptr m_timelimit_colon;
    tgui::Label::Ptr m_timelimit_point1;
    tgui::Label::Ptr m_timelimit_point2;
    tgui::EditBox::Ptr m_timelimit_hour;
    tgui::EditBox::Ptr m_timelimit_minute;
    tgui::EditBox::Ptr m_timelimit_day;
    tgui::EditBox::Ptr m_timelimit_month;
    tgui::EditBox::Ptr m_timelimit_year;

    tgui::ChildWindow::Ptr m_invalid_window;
    tgui::Label::Ptr m_invalid_label;
    tgui::Button::Ptr m_invalid_button;

public:
    FastAckWindow();

    tgui::ChildWindow::Ptr get_window() {
        return m_window;
    }


    void submit_button_handler(tgui::ChildWindow::Ptr);

    void timelimit_checked_handler(tgui::Group::Ptr);

    void timelimit_unchecked_handler(tgui::Group::Ptr);

    void window_destroy(tgui::ChildWindow::Ptr);

    void invalid_input_caller(tgui::ChildWindow::Ptr);

    void invalid_input_close(tgui::ChildWindow::Ptr);

    void valid_input_caller(tgui::ChildWindow::Ptr);



};

#endif //ICINGAGUI_FASTACKWINDOW_H
