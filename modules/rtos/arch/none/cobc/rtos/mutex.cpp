/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 * All Rights Reserved.
 *
 * See the file "LICENSE" for the full license governing this code.
 */

#include "mutex.h"

#include <cobc/rtos/failure_handler.h>

// ----------------------------------------------------------------------------
cobc::rtos::Mutex::Mutex()
{
    // TODO
}

cobc::rtos::Mutex::~Mutex()
{
    // TODO
}

// ----------------------------------------------------------------------------
bool
cobc::rtos::Mutex::acquire()
{
    // TODO
    return false;
}

bool
cobc::rtos::Mutex::acquire(time::Duration timeout)
{
    (void) timeout;     // not used

    // TODO
    return false;
}
