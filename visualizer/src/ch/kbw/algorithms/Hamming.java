package ch.kbw.algorithms;

public class Hamming {

    public static short[] generate(short[] buffer) {
        short[] data = new short[buffer.length];

        for (int i = 0; i < buffer.length; i++) {
            int block = buffer[i];
            //System.out.println(Integer.toBinaryString(block));

            // Make spaces for parity bits
            for (short parity = 1; parity <= 8; parity <<= 1) {
                int mask = (0xffffffff << (parity - 1));
                block = ((block & mask) << 1) | (block & ~mask);
                //System.out.println(Integer.toBinaryString(block));
            }

            // Calculate parity bits and insert them
            for (int paritybit = 1; paritybit <= 8; paritybit <<= 1) {
                byte parity = 0;
                int index = paritybit - 1;
                while (index < 16) {
                    for (int j = 0; j < paritybit; j++) {
                        //System.out.println("i:" + index + " bit:" + Integer.toBinaryString(0x1 & (block >> index)));
                        parity ^= 0x1 & (block >> index);
                        index++;
                    }
                    index += paritybit;
                }
                block |= ((0x1 & parity) << (paritybit - 1));
                //System.out.println(Integer.toBinaryString(block) + " Parity: " + Integer.toBinaryString(parity));
            }
            data[i] = (short) block;
        }

        return data;
    }
}
