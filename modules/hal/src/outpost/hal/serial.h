/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 *
 * This file is part of outpost 0.6.
 *
 * It is distributed under the terms of the GNU General Public License with a
 * linking exception. See the file "LICENSE" for the full license governing
 * this code.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */
// ----------------------------------------------------------------------------

#ifndef COBC_HAL_SERIAL_H
#define COBC_HAL_SERIAL_H

#include <cstddef>
#include <stdint.h>

#include <outpost/time/duration.h>
#include <outpost/utils/bounded_array.h>

namespace outpost
{
namespace hal
{
/**
 * Serial Interface
 *
 * \author  Fabian Greif
 */
class Serial
{
public:
    virtual
    ~Serial() = 0;

    /**
     * Close the UART device
     */
    virtual void
    close() = 0;

    /**
     * Check if data is available in the input buffers.
     *
     * \retval true   Data is available and can be read via read(...).
     * \retval false  No data available.
     */
    virtual bool
    isAvailable() = 0;

    /**
     * Check how many bytes are available in the input buffers.
     * \return  Number of bytes in the buffer
     */
    virtual size_t
    getNumberOfBytesAvailable() = 0;

    /**
     * Read a block of bytes.
     *
     * Waits until the timeout occurs to read the given number of
     * bytes. May return earlier if enough bytes are available. The
     * exact number of bytes read will be return, it will be up to
     * \p length byte but can also be any value lower.
     *
     * \param *data
     *      Pointer to a buffer big enough to storage \p length bytes
     * \param  length
     *      Number of bytes to be read
     *
     * \return    Number of bytes which could be read, maximal \p length
     */
    virtual size_t
    read(outpost::BoundedArray<uint8_t> data,
         outpost::time::Duration timeout = outpost::time::Duration::maximum()) = 0;

    /**
     * Write a block of bytes with timeout.
     *
     *
     *
     * \param *data
     *      Pointer to a buffer
     * \param length
     *      Number of bytes to be write
     * \return  Number of bytes written.
     */
    virtual size_t
    write(outpost::BoundedArray<const uint8_t> data,
          outpost::time::Duration timeout = outpost::time::Duration::maximum()) = 0;

    /**
     * Flush receive buffers.
     *
     * Data remaining in the receive buffer is discarded. Afterwards all
     * internal buffers are empty.
     */
    virtual void
    flushReceiver() = 0;

    /**
     * Sends eventually buffered data. Afterwards all internal buffers
     * are empty.
     */
    virtual void
    flushTransmitter() = 0;
};

}
}

#endif // COBC_HAL_SERIAL_H