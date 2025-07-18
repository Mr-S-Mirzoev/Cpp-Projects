#include <cassert>
#include <cstdint>
#include <cstring>

#include <concepts>
#include <iostream>
#include <stdexcept>

template <typename T>
concept UnsignedInteger = std::is_unsigned_v<T>;

static constexpr std::size_t CHUNK_SIZE = 7;
static constexpr std::size_t CHUNK_MASK = (1 << CHUNK_SIZE) - 1;
static constexpr std::size_t CHUNK_STOP = (1 << CHUNK_SIZE);
static_assert(CHUNK_STOP == 0x80, "Invalid chunk stop bit");
static_assert(CHUNK_MASK == 0x7F, "Invalid chunk mask");

template <UnsignedInteger UInt>
std::size_t encodeInteger(UInt val, uint8_t* buf, std::size_t len) {
    std::size_t written = 0;
    do {
        // Check buffer overflow
        if (written >= len)
            return 0;

        // Extract lower 7 bits of the value
        uint8_t byte = val & CHUNK_MASK;
        val >>= 7;

        // Set stop-bit if more data follows
        if (val != 0) {
            byte |= CHUNK_STOP;
        }

        buf[written++] = byte;
    } while (val != 0);

    return written;
}

template <UnsignedInteger UInt>
UInt decodeInteger(const uint8_t* buf, std::size_t len) {
    UInt val = 0;
    std::size_t shift = 0;

    for (std::size_t i = 0; i < len; ++i) {
        // Read as uint8_t to prevent sign extension
        uint8_t byte = buf[i];

        // Store 7-bit chunk
        val |= static_cast<UInt>(byte & CHUNK_MASK) << shift;
        shift += CHUNK_SIZE;

        std::cout << "Decoded step: byte=" << std::hex << static_cast<int>(byte)
                  << " val=" << std::hex << val << " shift=" << shift << '\n';

        // Stop-bit
        if ((byte & 0x80) == 0) {
            return val;
        }
    }

    throw std::runtime_error("Malformed variable-length encoding: missing stop-bit");
}

// Test function
template <UnsignedInteger UInt>
void testEncodeDecode(UInt val, const uint8_t* expected, std::size_t expectedLen) {
    UInt dec = decodeInteger<UInt>(expected, expectedLen);
    std::cout << "Expected: " << std::hex << val << ", Decoded: " << std::hex << dec << '\n';
    assert(dec == val);

    uint8_t enc[10] = {0};
    std::size_t encLen = encodeInteger<UInt>(val, enc, sizeof(enc));
    
    std::cout << "Encoded length: " << encLen << ", Expected length: " << expectedLen << '\n';

    for (std::size_t i = 0; i < encLen; ++i) {
        std::cout << "Encoded[" << i << "]: " << std::hex << static_cast<int>(enc[i]) << '\n';
    }

    assert(encLen == expectedLen);
    assert(std::memcmp(enc, expected, expectedLen) == 0);
}

int main() {
    testEncodeDecode<unsigned>(128, reinterpret_cast<const uint8_t*>("\x80\x01"), 2);
    testEncodeDecode<unsigned>(19730, reinterpret_cast<const uint8_t*>("\x92\x9A\x01"), 3);

    return 0;
}