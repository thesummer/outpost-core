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

#include <outpost/rtos/failure_handler.h>

#include <stdio.h>
#include <cstdlib>

#include <inttypes.h>

static void
defaultHandler(outpost::rtos::FailureCode code)
{
    //printf("Fatal Handler: %"PRIu32"\n", code.getCode());
    printf("Fatal Handler: 0x%08X\n", static_cast<int>(code.getCode()));
    exit(1);
}

outpost::rtos::FailureHandler::Handler outpost::rtos::FailureHandler::handler = &defaultHandler;
