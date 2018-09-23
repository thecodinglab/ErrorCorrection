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
static T crc(T generator, const void *buffer, size_t length)
{
    const uint8_t *input = static_cast<const uint8_t *>(buffer);
    T crc = 0; // Set the initial value to zero

    for (size_t i = 0; i < length; i++) // Loop for as long as there are bytes left in buffer
    {
        crc ^= static_cast<T>(input[i] << MSB); // XOR current byte value with crc

        for (uint8_t j = 0; j < 8; j++) // Repeat for 8 bits in current byte
        {
			if (crc & (1 << (MSB + 7))) { // Check if most significant bit (MSB) is set

				// If it is: Shift the crc one bit to the left to discard the MSB
				// and XOR the crc with the polynomial (generator)
				crc = (crc << 1) ^ generator;
			}
			else {
				// If not shift the crc 1 bit to the left
				crc <<= 1;
			}
                 
        }
    }

    return crc;
}