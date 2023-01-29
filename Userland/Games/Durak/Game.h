/*
 * Copyright (c) 2021, Jamie Mansfield <jmansfield@cadixdev.org>
 * Copyright (c) 2022, the SerenityOS developers.
 * Copyright (c) 2022, Sam Atkins <atkinssj@serenityos.org>
 * Copyright (c) 2023, Jan Ole Hüser
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Array.h>
#include <LibCards/CardGame.h>
#include <LibCards/CardStack.h>

using Cards::Card;
using Cards::CardStack;

namespace Durak {

class Game final : public Cards::CardGame {
    C_OBJECT_ABSTRACT(Game)
public:
    static ErrorOr<NonnullRefPtr<Game>> try_create();
    ~Game() override = default;

private:
    Game();
};
}
