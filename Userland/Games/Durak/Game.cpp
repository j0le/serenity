/*
 * Copyright (c) 2021, Jamie Mansfield <jmansfield@cadixdev.org>
 * Copyright (c) 2022, Jonas Höpner <me@jonashoepner.de>
 * Copyright (c) 2022, the SerenityOS developers.
 * Copyright (c) 2023, Jan Ole Hüser
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Game.h"
#include <AK/Random.h>
#include <LibGUI/Event.h>
#include <LibGUI/Painter.h>
#include <LibGfx/Palette.h>


template<class T>
static T get_minimum(T a, T b){
    if (a < b)
        return a;
    return b;
}


REGISTER_WIDGET(Durak, Game);

namespace Durak {

ErrorOr<NonnullRefPtr<Game>> Game::try_create()
{
    auto game = TRY(adopt_nonnull_ref_or_enomem(new (nothrow) Game()));

    return game;
}

Game::Game() = default;


void Game::paint_event(GUI::PaintEvent& event)
{
    //Gfx::Color background_color = this->background_color();

    GUI::Frame::paint_event(event);

    GUI::Painter painter(*this);
    painter.add_clip_rect(frame_inner_rect());
    painter.add_clip_rect(event.rect());

    Gfx::Color cyan(Gfx::Color::NamedColor::Cyan);
    painter.draw_line(m_line_start_point, m_mouse_position, cyan);
}

void Game::mousedown_event(GUI::MouseEvent& event)
{
    GUI::Frame::mousemove_event(event);
    m_mouse_position = event.position();

    int x = get_minimum(m_line_start_point.x(), m_mouse_position.x());
    int y = get_minimum(m_line_start_point.y(), m_mouse_position.y());

    int width = AK::abs(m_line_start_point.x()- m_mouse_position.x());
    int hight = AK::abs(m_line_start_point.y()- m_mouse_position.y());


    update(Gfx::IntRect(x,y,width,hight));
}

}
