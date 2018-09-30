package ch.kbw.algorithms;

public class CRC {

    public static int crc(int generator, byte[] buffer) {
        int crc = 0; // Set the initial value to zero

        for (int i = 0; i < buffer.length; i++) { // Loop for as long as there are bytes left in buffer
            crc ^= buffer[i] << 24; // XOR current byte value with crc

            for (byte j = 0; j < 8; j++) { // Repeat for 8 bits in current byte
                if ((crc & 0x80000000) != 0) { // Check if most significant bit is set

                    // If it is: Shift the crc one bit to the left to discard the most significant bit
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
}
