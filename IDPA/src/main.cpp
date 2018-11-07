#include <iostream>
#include <bitset>
#include "crc.h"
#include "hamming.h"

// Reference algorithm from http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html:
uint32_t Compute_CRC32_Simple(const uint8_t *bytes, size_t length)
{
    const uint32_t polynomial = 0x04C11DB7;
    uint32_t crc = 0;

    for (size_t i = 0; i < length; i++)
    {
        crc ^= (uint32_t)(bytes[i] << 24); 

        for (int i = 0; i < 8; i++)
        {
            if ((crc & 0x80000000) != 0)
                crc = (uint32_t)((crc << 1) ^ polynomial);
            else
                crc <<= 1;
        }
    }

    return crc;
}

#include <chrono>

#define COUNT 10000000

void benchmarkPhilip()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for (size_t i = 0; i < COUNT; i++)
	{
		hamming_16(&i, 1);
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Took " << ms.count() << "ms for Philip's algorithm" << std::endl;
}

void benchmarkFlorian()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for (size_t i = 0; i < COUNT; i++)
	{
		hamming_16_byte(i);
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Took " << ms.count() << "ms for Florian's algorithm" << std::endl;
}

int main()
{
    const char *string = "The quick brown fox jumps over the lazy dog";

    // CRC
    /*std::cout << std::hex << Compute_CRC32_Simple((uint8_t*)string, strlen(string)) << std::endl;
    std::cout << std::hex << crc<uint32_t, 24>(0x04C11DB7, string, strlen(string)) << std::endl;*/

	uint8_t data = 0xff;

	benchmarkPhilip();
	benchmarkFlorian();

    // Hamming-Code
    // 1st letter: "T", UTF-8-code 84 = 1010100
    /*std::cout << std::bitset<16>(84) << std::endl;
    const uint16_t *data = hamming_16((uint8_t*)string, strlen(string));
    std::cout << std::bitset<16>(data[0]) << std::endl;*/

    std::cin.get();
    return 0;
}