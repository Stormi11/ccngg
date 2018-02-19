//
// Created by p.weisser on 13.02.2018.
//

#include <TGUI/TGUI.hpp>
tgui::Panel::Ptr hosts()
{
    tgui::Panel::Ptr hosts = tgui::Panel::create({"98%","30%"});
    hosts->setPosition("1%", "69%");

    return hosts;
}