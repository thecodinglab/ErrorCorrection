/* IDPA
 * Copyright (C) 2018  TheCodingLab, Altara
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

//template<typename T>
static uint16_t* hamming_16(const void *buffer, size_t length)
{
    const uint8_t *input = static_cast<const uint8_t *>(buffer);
    uint16_t *data = new uint16_t[length];

    for (size_t i = 0; i < length; i++) {
        uint16_t block = input[i];

        // Make spaces for parity bits
        for (uint16_t parity = 1; parity <= 8; parity <<= 1) {
            uint16_t mask = (0xffff << (parity - 1));
            block = ((block & mask) << 1) | (block & ~mask);
        }

        // Calculate parity bits and insert them
        for (uint16_t paritybit = 1; paritybit <= 8; paritybit <<= 1) {
            uint8_t parity = 0;
            uint8_t index = paritybit - 1;
            while (index < 16) {
                for (size_t j = 0; j < paritybit; j++) {
                    parity ^= 0x1 & (block >> index);
                    index++;
                }
                index += paritybit;
            }
            block |= ((0x1 & parity) << (paritybit - 1));
        }
        data[i] = block;
    }

    return data;
}

#include <iostream>

static uint16_t hamming_16_byte(uint8_t input)
{
	uint16_t message = input; // The final message with error correcting codes
	const uint8_t countParityBits = 4; // The amount of parity bits in the final message

	uint16_t parityIndex = 1; // The position of the currently used parity bit
	while (parityIndex < (1 << countParityBits)) // Go through all parity bits and create spaces in the message for them
	{
		uint16_t upperMask = 0xffff << (parityIndex - 1);
		message = ((message & upperMask) << 1) | (message & ~upperMask); // Shift all bits above the parity bit one to the left
																		 // (create space for parity bit)
		parityIndex <<= 1; // Go to the next parity bit
	}

	message = message & 0x7fff; // TODO DEBUG ONLY
	parityIndex >>= 1;

	while (parityIndex)
	{
		size_t val = 0;
		for (size_t i = 0; i < 15; i++)
		{
			if ((i + 1) & parityIndex)
				val ^= 0x1 & (message >> i);
		}

		message |= val << (parityIndex - 1);
		
		parityIndex >>= 1;
	}

	return message;
}
