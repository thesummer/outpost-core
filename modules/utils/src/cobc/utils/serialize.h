/*
 * Copyright (c) 2013, German Aerospace Center (DLR)
 * All Rights Reserved.
 *
 * See the file "LICENSE" for the full license governing this code.
 */
// ----------------------------------------------------------------------------

#ifndef COBC_UTILS_SERIALIZE_H
#define COBC_UTILS_SERIALIZE_H

#include <stddef.h>
#include <string.h>
#include <stdint.h>

namespace cobc
{
// LCOV_EXCL_START
// Functions are tested in \c test/unit/test_byteorder.cpp
// But as they are inline functions lcov can't generate useful
// coverage reports for them

/**
 * \author Fabian Greif
 */
class Serialize
{
public:
    explicit inline
    Serialize(uint8_t * outputBuffer) :
            buffer(outputBuffer), begin(outputBuffer)
    {
    }

    inline void
    store8(uint8_t data)
    {
        buffer[0] = data;
        buffer += 1;
    }

    inline void
    store16(uint16_t data)
    {
        buffer[0] = static_cast<uint8_t>(data >> 8);
        buffer[1] = static_cast<uint8_t>(data >> 0);
        buffer += 2;
    }

    inline void
    store24(uint32_t data)
    {
        buffer[0] = static_cast<uint8_t>(data >> 16);
        buffer[1] = static_cast<uint8_t>(data >> 8);
        buffer[2] = static_cast<uint8_t>(data >> 0);
        buffer += 3;
    }

    inline void
    store32(uint32_t data)
    {
        buffer[0] = static_cast<uint8_t>(data >> 24);
        buffer[1] = static_cast<uint8_t>(data >> 16);
        buffer[2] = static_cast<uint8_t>(data >> 8);
        buffer[3] = static_cast<uint8_t>(data >> 0);
        buffer += 4;
    }

    inline void
    store64(uint64_t data)
    {
        buffer[0] = static_cast<uint8_t>(data >> 56);
        buffer[1] = static_cast<uint8_t>(data >> 48);
        buffer[2] = static_cast<uint8_t>(data >> 40);
        buffer[3] = static_cast<uint8_t>(data >> 32);
        buffer[4] = static_cast<uint8_t>(data >> 24);
        buffer[5] = static_cast<uint8_t>(data >> 16);
        buffer[6] = static_cast<uint8_t>(data >> 8);
        buffer[7] = static_cast<uint8_t>(data >> 0);
        buffer += 8;
    }

    inline void
    storeFloat(float data)
    {
        const uint32_t* ptr = reinterpret_cast<const uint32_t *>(&data);
        store32(*ptr);
    }

    inline void
    storeDouble(double data)
    {
        const uint64_t* ptr = reinterpret_cast<const uint64_t *>(&data);
        store64(*ptr);
    }

    // get position of the buffer
    inline ptrdiff_t
    getPosition() const
    {
        return (buffer - begin);
    }

    inline Serialize&
    operator<<(uint8_t data)
    {
        store8(data);
        return *this;
    }

    inline Serialize&
    operator<<(uint16_t data)
    {
        store16(data);
        return *this;
    }

    inline Serialize&
    operator<<(uint32_t data)
    {
        store32(data);
        return *this;
    }

    inline Serialize&
    operator<<(int8_t data)
    {
        store8(static_cast<uint8_t>(data));
        return *this;
    }

    inline Serialize&
    operator<<(int16_t data)
    {
        store16(static_cast<uint16_t>(data));
        return *this;
    }

    inline Serialize&
    operator<<(int32_t data)
    {
        store32(static_cast<uint32_t>(data));
        return *this;
    }

    inline Serialize&
    operator<<(const float& data)
    {
        storeFloat(data);
        return *this;
    }

    inline Serialize&
    operator<<(const double& data)
    {
        storeDouble(data);
        return *this;
    }

private:
    uint8_t* buffer;
    const uint8_t* const begin;
};
// LCOV_EXCL_STOP
// LCOV_EXCL_END

/**
 * Deserialize the application data of a CCSDS/PUS packet.
 *
 * The read8(), read16() and read32() functions read the number of bits
 * from the current location and move the data pointer forward
 * correspondingly. The peek8(), peek16() and peek32() read a value
 * n bytes in front of the current location and *don't* move the
 * data pointer.
 *
 * \author Fabian Greif
 */
class Deserialize
{
public:
    explicit inline
    Deserialize(const uint8_t* inputBuffer) :
            buffer(inputBuffer), begin(inputBuffer)
    {
    }

    /**
     * Reset the read pointer to the beginning of the
     * originating buffer.
     */
    inline void
    reset()
    {
        buffer = begin;
    }

    inline uint8_t
    read8()
    {
        uint8_t value;
        value = buffer[0];
        buffer += 1;

        return value;
    }

    inline uint8_t
    peek8(size_t n) const
    {
        return buffer[n];
    }

    inline uint16_t
    read16()
    {
        uint16_t value = 0;
        value |= static_cast<uint16_t>(buffer[0]) << 8;
        value |= static_cast<uint16_t>(buffer[1]) << 0;
        buffer += 2;

        return value;
    }

    inline uint16_t
    peek16(size_t n) const
    {
        uint16_t value = 0;
        value |= static_cast<uint16_t>(buffer[n + 0]) << 8;
        value |= static_cast<uint16_t>(buffer[n + 1]) << 0;

        return value;
    }

    inline uint32_t
    read24()
    {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(buffer[0]) << 16;
        value |= static_cast<uint32_t>(buffer[1]) << 8;
        value |= static_cast<uint32_t>(buffer[2]) << 0;
        buffer += 3;

        return value;
    }

    inline uint32_t
    peek24(size_t n) const
    {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(buffer[n + 0]) << 16;
        value |= static_cast<uint32_t>(buffer[n + 1]) << 8;
        value |= static_cast<uint32_t>(buffer[n + 2]) << 0;

        return value;
    }

    inline uint32_t
    read32()
    {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(buffer[0]) << 24;
        value |= static_cast<uint32_t>(buffer[1]) << 16;
        value |= static_cast<uint32_t>(buffer[2]) << 8;
        value |= static_cast<uint32_t>(buffer[3]) << 0;
        buffer += 4;

        return value;
    }

    inline uint32_t
    peek32(size_t n) const
    {
        uint32_t value = 0;
        value |= static_cast<uint32_t>(buffer[n + 0]) << 24;
        value |= static_cast<uint32_t>(buffer[n + 1]) << 16;
        value |= static_cast<uint32_t>(buffer[n + 2]) << 8;
        value |= static_cast<uint32_t>(buffer[n + 3]) << 0;

        return value;
    }

    inline uint64_t
    read64()
    {
        uint64_t value = 0;
        value |= static_cast<uint64_t>(buffer[0]) << 56;
        value |= static_cast<uint64_t>(buffer[1]) << 48;
        value |= static_cast<uint64_t>(buffer[2]) << 40;
        value |= static_cast<uint64_t>(buffer[3]) << 32;
        value |= static_cast<uint64_t>(buffer[4]) << 24;
        value |= static_cast<uint64_t>(buffer[5]) << 16;
        value |= static_cast<uint64_t>(buffer[6]) << 8;
        value |= static_cast<uint64_t>(buffer[7]) << 0;
        buffer += 8;

        return value;
    }

    inline uint64_t
    peek64(size_t n) const
    {
        uint64_t value = 0;
        value |= static_cast<uint64_t>(buffer[n + 0]) << 56;
        value |= static_cast<uint64_t>(buffer[n + 1]) << 48;
        value |= static_cast<uint64_t>(buffer[n + 2]) << 40;
        value |= static_cast<uint64_t>(buffer[n + 3]) << 32;
        value |= static_cast<uint64_t>(buffer[n + 4]) << 24;
        value |= static_cast<uint64_t>(buffer[n + 5]) << 16;
        value |= static_cast<uint64_t>(buffer[n + 6]) << 8;
        value |= static_cast<uint64_t>(buffer[n + 7]) << 0;

        return value;
    }

    inline float
    readFloat(void)
    {
        float f;
        const uint32_t value = read32();

        memcpy(&f, &value, sizeof(f));
        return f;
    }

    inline float
    peekFloat(size_t n) const
    {
        float f;
        const uint32_t value = peek32(n);

        memcpy(&f, &value, sizeof(f));
        return f;
    }

    inline double
    readDouble(void)
    {
        double d;
        const uint64_t value = read64();

        memcpy(&d, &value, sizeof(d));
        return d;
    }

    inline double
    peekDouble(size_t n) const
    {
        double d;
        const uint64_t value = peek64(n);

        memcpy(&d, &value, sizeof(d));
        return d;
    }

    /**
     * Skip forward the given number of bytes.
     *
     * \param bytes
     *      Number of byte to skip forward.
     */
    inline void
    skip(size_t bytes)
    {
        buffer += bytes;
    }

    inline Deserialize&
    operator>>(uint8_t& data)
    {
        data = read8();
        return *this;
    }

    inline Deserialize&
    operator>>(uint16_t& data)
    {
        data = read16();
        return *this;
    }

    inline Deserialize&
    operator>>(uint32_t& data)
    {
        data = read32();
        return *this;
    }

    inline Deserialize&
    operator>>(int8_t& data)
    {
        data = static_cast<int8_t>(read8());
        return *this;
    }

    inline Deserialize&
    operator>>(int16_t& data)
    {
        data = static_cast<int16_t>(read16());
        return *this;
    }

    inline Deserialize&
    operator>>(int32_t& data)
    {
        data = static_cast<int32_t>(read32());
        return *this;
    }

    inline Deserialize&
    operator>>(float& data)
    {
        data = readFloat();
        return *this;
    }

    inline Deserialize&
    operator>>(double& data)
    {
        data = readDouble();
        return *this;
    }


    /**
     * Get Pointer to the current location in the buffer.
     */
    inline const uint8_t *
    getPointer() const
    {
        return buffer;
    }

    inline ptrdiff_t
    getPosition() const
    {
        return (buffer - begin);
    }

private:
    const uint8_t* buffer;
    const uint8_t* const begin;
};
}

#endif // COBC_UTILS_SERIALIZE_H