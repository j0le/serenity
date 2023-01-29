/*
 * Copyright (c) 2021, Jamie Mansfield <jmansfield@cadixdev.org>
 * Copyright (c) 2021, Mustafa Quraish <mustafa@serenityos.org>
 * Copyright (c) 2022-2023, Sam Atkins <atkinssj@serenityos.org>
 * Copyright (c) 2023, Jan Ole Hüser
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"
#include <Games/Durak/DurakGML.h>
#include <LibConfig/Client.h>
#include <LibCore/System.h>
#include <LibCore/Timer.h>
#include <LibGUI/Action.h>
#include <LibGUI/ActionGroup.h>
#include <LibGUI/Application.h>
#include <LibGUI/Icon.h>
#include <LibGUI/Menu.h>
#include <LibGUI/Menubar.h>
#include <LibGUI/MessageBox.h>
#include <LibGUI/Statusbar.h>
#include <LibGUI/Window.h>
#include <LibMain/Main.h>
#include <stdio.h>

ErrorOr<int> serenity_main(Main::Arguments arguments)
{
    auto app = TRY(GUI::Application::try_create(arguments));
    auto window = TRY(GUI::Window::try_create());
    window->set_title("Durak");

    auto widget = TRY(window->set_main_widget<GUI::Widget>());
    TRY(widget->load_from_gml(durak_gml));

    auto& game = *widget->find_descendant_of_type_named<Durak::Game>("game");
    game.set_focus(true);

    window->show();
    return app->exec();
}
