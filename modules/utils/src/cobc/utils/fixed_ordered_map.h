/*
 * Copyright (c) 2015, German Aerospace Center (DLR)
 * 
 * This file is part of libCOBC 0.4.
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

#ifndef COBC_UTILS_FIXED_ORDERED_MAP_H
#define COBC_UTILS_FIXED_ORDERED_MAP_H

#include <stdint.h>
#include <stddef.h>

namespace cobc
{

/**
 *
// Performs a binary search over the ID of all stored functions.
// Functions have to be stored in an ascending order!
 *
 * \author  Fabian Greif
 */
template <typename Entry, typename Key>
class FixedOrderedMap
{
public:
    /**
     * Create list from an array without explicit size.
     *
     * \param entries
     *      C style array of entries.
     */
    template <size_t N>
    explicit inline
    FixedOrderedMap(Entry (&entries)[N]) :
        mNumberOfEntries(N),
        mEntries(entries)
    {
    }

    /**
     * Constructor.
     *
     * \param entries
     *      List of all entries. The entries must be ordered with a
     *      ascending mKey value!
     * \param numberOfEntries
     *      Number of entries in the list. The number of entries must be
     *      greater than zero!
     */
    FixedOrderedMap(Entry* entries,
                    int numberOfEntries);

    /**
     * Get the number of entries.
     *
     * \return  Number of entries.
     */
    inline int
    getNumberOfEntries() const
    {
        return mNumberOfEntries;
    }

    /**
     * Find a entry.
     *
     * Uses a binary search over the list of entries.
     *
     * \param key
     *      Key identifying the entry.
     * \return
     *      Pointer to the entry or 0 if no entry with the
     *      requested key is found.
     */
    Entry*
    getEntry(Key key);

private:
    const int mNumberOfEntries;
    Entry* const mEntries;
};

}

#include "fixed_ordered_map_impl.h"

#endif // COBC_UTILS_FIXED_ORDERED_MAP_H