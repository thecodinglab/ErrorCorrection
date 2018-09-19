/* IDPA
 * Copyright (C) 2018  TheCodingLab
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <stdint.h>

template<typename T, size_t MSB>
static T crc(T generator, const void *buf, size_t len)
{
    const uint8_t *in = static_cast<const uint8_t *>(buf);
    T crc = 0;

    for (size_t i = 0; i < len; i++)
    {
        crc ^= static_cast<T>(in[i] << MSB);
        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & (1 << (MSB + 7))) // Check if most significant bit is set
                crc = (crc << 1) ^ generator;
            else
                crc <<= 1;
        }
    }

    return crc;
}