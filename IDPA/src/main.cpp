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

void benchmark(uint16_t (*algorithm)(uint16_t), const char * msg)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for (size_t i = 0; i < COUNT; i++)
	{
		algorithm(i);
	}

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Took " << ms.count() << "ms for " << msg << std::endl;
}

void benchmarkAlgorithms()
{
	benchmark(&hamming_16_byte, "Florian's algorithm"); // Florian
	benchmark(&hamming_15_4, "Matrix"); // Matrix
	benchmark(&hamming_15_4_performance, "Matrix without for loop");
	benchmark(&hamming_15_4_oneliner, "amazing oneliner");
	benchmark(&hamming_matrix_asm_generate, "matrix using assembly");
}

int main()
{
    //const char *string = "The quick brown fox jumps over the lazy dog";

    // CRC
    //std::cout << std::hex << Compute_CRC32_Simple((uint8_t*)string, strlen(string)) << std::endl;
    //std::cout << std::hex << crc<uint32_t, 24>(0x04C11DB7, string, strlen(string)) << std::endl;

	srand((int) time(0));

	while (1)
	{
		uint16_t input = 0b100111000110000;
		uint16_t parity = hamming_matrix_asm_generate(input);
		uint16_t message = input | (parity & 0xf);

		uint32_t flippedBit = rand() % 15;
		uint16_t received = input ^ (1 << flippedBit);

		uint16_t error = hamming_matrix_asm_check(received);

		std::cout << std::hex;
		std::cout << "Input: " << input << std::endl;
		std::cout << "Parity: " << parity << std::endl;
		std::cout << "Message: " << message << std::endl;

		std::cout << "Computed error: " << error << std::endl;
		std::cout << "Real error: " << flippedBit << std::endl;

		std::cout << std::endl;


		//benchmarkAlgorithms();

		std::cin.get();
	}
    return 0;
}