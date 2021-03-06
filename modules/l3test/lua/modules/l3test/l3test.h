/*
 * Copyright (c) 2014-2017, German Aerospace Center (DLR)
 *
 * This file is part of the development version of OUTPOST.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Authors:
 * - 2014-2017, Fabian Greif (DLR RY-AVS)
 */
// ----------------------------------------------------------------------------

#ifndef L3TEST_H
#define L3TEST_H

extern "C"
{
#include <lauxlib.h>

/**
 *
 *
 * \param L
 *      Lua State.
 *
 * \return
 */
int
luaopen_l3test(lua_State* L);
}

#endif // L3TEST_H
