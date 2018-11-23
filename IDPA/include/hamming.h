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

#define MATRIX_ROW_1 0x7F80 /* 111111110000000 */
#define MATRIX_ROW_2 0x7878 /* 111100001111000 */
#define MATRIX_ROW_3 0x6666 /* 110011001100110 */
#define MATRIX_ROW_4 0x5555 /* 101010101010101 */

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

static uint16_t hamming_16_byte(uint16_t input) // Sorry, had to make it 16 bit for benchmark
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


static uint16_t hamming_15_4(uint16_t data) {
    uint16_t r1 = data & MATRIX_ROW_1;
    uint16_t r2 = data & MATRIX_ROW_2;
    uint16_t r3 = data & MATRIX_ROW_3;
    uint16_t r4 = data & MATRIX_ROW_4;

    uint16_t p1 = 0, p2 = 0, p3 = 0, p4 = 0;
    for (size_t i = 0; i < 15; i++) {
        p1 ^= r1 & 1;
        p2 ^= r2 & 1;
        p3 ^= r3 & 1;
        p4 ^= r4 & 1;

        r1 >>= 1;
        r2 >>= 1;
        r3 >>= 1;
        r4 >>= 1;
    }

    return data ^ (p1 << 3) ^ (p2 << 2) ^ (p3 << 1) ^ p4;
}

static uint16_t hamming_15_4_performance(uint16_t data) {
    uint16_t r1 = data & MATRIX_ROW_1;
    uint16_t r2 = data & MATRIX_ROW_2; 
    uint16_t r3 = data & MATRIX_ROW_3;
    uint16_t r4 = data & MATRIX_ROW_4;

    uint16_t p1 = 1 & ((r1 & 1) ^ ((r1 >> 1) & 1) ^ ((r1 >> 2) & 1) ^ ((r1 >> 3) & 1) ^ ((r1 >> 4) & 1) ^ ((r1 >> 5) & 1) ^ ((r1 >> 6) & 1) ^ ((r1 >> 7) & 1) ^ ((r1 >> 8) & 1) ^ ((r1 >> 9) & 1) ^ ((r1 >> 10) & 1) ^ ((r1 >> 11) & 1) ^ ((r1 >> 12) & 1) ^ ((r1 >> 13) & 1) ^ ((r1 >> 14) & 1));
    uint16_t p2 = 1 & ((r2 & 1) ^ ((r2 >> 1) & 1) ^ ((r2 >> 2) & 1) ^ ((r2 >> 3) & 1) ^ ((r2 >> 4) & 1) ^ ((r2 >> 5) & 1) ^ ((r2 >> 6) & 1) ^ ((r2 >> 7) & 1) ^ ((r2 >> 8) & 1) ^ ((r2 >> 9) & 1) ^ ((r2 >> 10) & 1) ^ ((r2 >> 11) & 1) ^ ((r2 >> 12) & 1) ^ ((r2 >> 13) & 1) ^ ((r2 >> 14) & 1));
    uint16_t p3 = 1 & ((r3 & 1) ^ ((r3 >> 1) & 1) ^ ((r3 >> 2) & 1) ^ ((r3 >> 3) & 1) ^ ((r3 >> 4) & 1) ^ ((r3 >> 5) & 1) ^ ((r3 >> 6) & 1) ^ ((r3 >> 7) & 1) ^ ((r3 >> 8) & 1) ^ ((r3 >> 9) & 1) ^ ((r3 >> 10) & 1) ^ ((r3 >> 11) & 1) ^ ((r3 >> 12) & 1) ^ ((r3 >> 13) & 1) ^ ((r3 >> 14) & 1));
    uint16_t p4 = 1 & ((r4 & 1) ^ ((r4 >> 1) & 1) ^ ((r4 >> 2) & 1) ^ ((r4 >> 3) & 1) ^ ((r4 >> 4) & 1) ^ ((r4 >> 5) & 1) ^ ((r4 >> 6) & 1) ^ ((r4 >> 7) & 1) ^ ((r4 >> 8) & 1) ^ ((r4 >> 9) & 1) ^ ((r4 >> 10) & 1) ^ ((r4 >> 11) & 1) ^ ((r4 >> 12) & 1) ^ ((r4 >> 13) & 1) ^ ((r4 >> 14) & 1));

    return data ^ (p1 << 3) ^ (p2 << 2) ^ (p3 << 1) ^ p4;
}

static uint16_t hamming_15_4_oneliner(uint16_t data) {
	return data ^ ((1 & (((data & 0x6D58) & 1) ^ (((data & 0x6D58) >> 1) & 1) ^ (((data & 0x6D58) >> 2) & 1) ^ (((data & 0x6D58) >> 3) & 1) ^ (((data & 0x6D58) >> 4) & 1) ^ (((data & 0x6D58) >> 5) & 1) ^ (((data & 0x6D58) >> 6) & 1) ^ (((data & 0x6D58) >> 7) & 1) ^ (((data & 0x6D58) >> 8) & 1) ^ (((data & 0x6D58) >> 9) & 1) ^ (((data & 0x6D58) >> 10) & 1) ^ (((data & 0x6D58) >> 11) & 1) ^ (((data & 0x6D58) >> 12) & 1) ^ (((data & 0x6D58) >> 13) & 1) ^ (((data & 0x6D58) >> 14) & 1))) << 3) ^ ((1 & (((data & 0x5B34) & 1) ^ (((data & 0x5B34) >> 1) & 1) ^ (((data & 0x5B34) >> 2) & 1) ^ (((data & 0x5B34) >> 3) & 1) ^ (((data & 0x5B34) >> 4) & 1) ^ (((data & 0x5B34) >> 5) & 1) ^ (((data & 0x5B34) >> 6) & 1) ^ (((data & 0x5B34) >> 7) & 1) ^ (((data & 0x5B34) >> 8) & 1) ^ (((data & 0x5B34) >> 9) & 1) ^ (((data & 0x5B34) >> 10) & 1) ^ (((data & 0x5B34) >> 11) & 1) ^ (((data & 0x5B34) >> 12) & 1) ^ (((data & 0x5B34) >> 13) & 1) ^ (((data & 0x5B34) >> 14) & 1))) << 2) ^ ((1 & (((data & 0x38F2) & 1) ^ (((data & 0x38F2) >> 1) & 1) ^ (((data & 0x38F2) >> 2) & 1) ^ (((data & 0x38F2) >> 3) & 1) ^ (((data & 0x38F2) >> 4) & 1) ^ (((data & 0x38F2) >> 5) & 1) ^ (((data & 0x38F2) >> 6) & 1) ^ (((data & 0x38F2) >> 7) & 1) ^ (((data & 0x38F2) >> 8) & 1) ^ (((data & 0x38F2) >> 9) & 1) ^ (((data & 0x38F2) >> 10) & 1) ^ (((data & 0x38F2) >> 11) & 1) ^ (((data & 0x38F2) >> 12) & 1) ^ (((data & 0x38F2) >> 13) & 1) ^ (((data & 0x38F2) >> 14) & 1))) << 1) ^ (1 & (((data & 0x7F1) & 1) ^ (((data & 0x7F1) >> 1) & 1) ^ (((data & 0x7F1) >> 2) & 1) ^ (((data & 0x7F1) >> 3) & 1) ^ (((data & 0x7F1) >> 4) & 1) ^ (((data & 0x7F1) >> 5) & 1) ^ (((data & 0x7F1) >> 6) & 1) ^ (((data & 0x7F1) >> 7) & 1) ^ (((data & 0x7F1) >> 8) & 1) ^ (((data & 0x7F1) >> 9) & 1) ^ (((data & 0x7F1) >> 10) & 1) ^ (((data & 0x7F1) >> 11) & 1) ^ (((data & 0x7F1) >> 12) & 1) ^ (((data & 0x7F1) >> 13) & 1) ^ (((data & 0x7F1) >> 14) & 1)));
}

uint16_t hamming_matrix_asm(uint16_t in)
{
    __asm {
        mov ax, 0

        mov cx, in              // Move input variable into cx (16-bit) register
        and cx, MATRIX_ROW_1    // Perform the binary matrix multiplication with the first row (0*0=0, 0*1=0, 1*0=0, 1*1=1 => logical and)
        popcnt cx, cx           // Summing up (calculate Hamming Weight [amount of set bits in the register])
        and cx, 1               // Update register to a bit value whether the amount of set bits is even
        or ax, cx               // Move the result into the return register
        shl ax, 1               // Shift return value by one and start calculation of next value

        mov cx, in              // Move input variable into cx (16-bit) register
        and cx, MATRIX_ROW_2    // Perform the binary matrix multiplication with the second row
        popcnt cx, cx           // Calculate hamming weight
        and cx, 1               // Update register to a bit value whether the amount of set bits is even
        or ax, cx               // Move the result into the return register
        shl ax, 1               // Shift return value by one and start calculation of next value

        mov cx, in              // Move input variable into cx (16-bit) register
        and cx, MATRIX_ROW_3    // Perform the binary matrix multiplication with the third row
        popcnt cx, cx           // Calculate hamming weight
        and cx, 1               // Update register to a bit value whether the amount of set bits is even
        or ax, cx               // Move the result into the return register
        shl ax, 1               // Shift return value by one and start calculation of next value

        mov cx, in              // Move input variable into cx (16-bit) register
        and cx, MATRIX_ROW_4    // Perform the binary matrix multiplication with the fourth row
        popcnt cx, cx           // Calculate hamming weight
        and cx, 1               // Update register to a bit value whether the amount of set bits is even
        or ax, cx               // Move the result into the return register
    }
}