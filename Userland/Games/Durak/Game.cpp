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
    GUI::Frame::paint_event(event);
    //dbgln("Paint: x: {}, y: {}, widht: {}, hight: {}.", 
    //        event.rect().x(), 
    //        event.rect().y(), 
    //        event.rect().width(), 
    //        event.rect().height());

    GUI::Painter painter(*this);
    painter.add_clip_rect(frame_inner_rect());
    painter.add_clip_rect(event.rect());

    if (m_use_other_color) {
        Gfx::Color red(Gfx::Color::NamedColor::Red);
        painter.draw_line(m_line_start_point, m_line_end_point, red);
    }
    else{
        Gfx::Color cyan(Gfx::Color::NamedColor::Cyan);
        painter.draw_line(m_line_start_point, m_line_end_point, cyan);
    }
}

void Game::mousedown_event(GUI::MouseEvent&)
{
    m_mouse_went_down_in_widget = true;
}

void Game::mousemove_event(GUI::MouseEvent& event)
{
    GUI::Frame::mousemove_event(event);

    if (not m_mouse_went_down_in_widget)
        return;

    update_line_start_point(event.position());
}

void Game::update_line_start_point(Gfx::IntPoint point){

    int n = 0;
    auto fn = [&](){
        ++n;
        //dbgln("update_line_start_point: before {}. update.", n);
        auto rect = Gfx::IntRect::from_two_points(m_line_start_point, m_line_end_point);
        rect.inflate(1,1,1,1);
        //dbgln("update_line_start_point: x: {}, y: {}, widht: {}, hight: {}.", rect.x(), rect.y(), rect.width(), rect.height());
        update(rect);
        //dbgln("update_line_start_point: after {}. update.", n);
    };

    fn();

    m_line_end_point = point;
    fn();
}

}
