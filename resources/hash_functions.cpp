#include <cstddef>
#include <functional>
#include <iostream>
#include <cassert>


// #include <memory>
// std::__murmur2_or_cityhash<>


// refer to <functional> for hash types
// refer to <cfloat> for float value macros including FLT_MANT_DIG
// all check for 0 and return 0 to avoid 0 vs -0
// resort to Murmur2 hash function and CityHash hash functions (now a Murmur3)

// floating point numbers -> sign, exponent, mantissa
// sign_bits = std::numeric_limits<type>::is_signed
// exponent_size = sizeof(type) * CHAR_BIT - std::numeric_limits<type>::is_signed - std::numeric_limits<type>::digits
template<typename Float_type>
std::size_t hash(Float_type value)
{
    union {
        Float_type f;
        std::size_t s;
    } u;
    u.f = value;
    // auto mask = ~(~0UL << std::numeric_limits<Float_type>::digits);
    return u.s ^ (u.s >> 32);
}

// TODO: better to use reinterpret_cast than union
void tmp()
{
    auto val = 0;
    assert(sizeof(float) == sizeof val);
    auto t = reinterpret_cast<float&>(val);

    assert(sizeof(float) == sizeof val);
    auto t2 = *reinterpret_cast<float*>(&val);

    auto f = 0.0;
    // can also use memcpy
    assert(sizeof f == sizeof val);
    memcpy(&f, &val, sizeof f);
}


// Java Double hash function
//public static int hashCode(double value) {
//    long bits = doubleToLongBits(value);
//    return (int)(bits ^ (bits >>> 32));
//}

// convert hash code to array index
// distributes between 0 and modulo_divisor - 1
template<typename Type>
std::size_t hash(Type x, std::size_t modulo_divisor)
{
    return (hash(x) & 0x7FFFFFFF) % modulo_divisor;
}

struct Hash_example {
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
};

// Java style
template<>
std::size_t hash<Hash_example>(Hash_example obj)
{
    auto h = static_cast<std::size_t>(17);
    h = 31 * h + std::hash<char>{}(obj.c);
    h = 31 * h + std::hash<short>{}(obj.s);
    h = 31 * h + std::hash<int>{}(obj.i);
    h = 31 * h + std::hash<long>{}(obj.l);
    h = 31 * h + std::hash<float>{}(obj.f);
    h = 31 * h + std::hash<double>{}(obj.d);
    return h;
}

template<>
std::size_t hash<std::string>(std::string s, std::size_t modulo_divisor)
{
    auto h = static_cast<std::size_t>(0);
    auto r = static_cast<std::size_t>(
            std::numeric_limits<std::string::value_type>::max() - std::numeric_limits<std::string::value_type>::min()
    );
    for (auto c : s) { h = (r * h + c) % modulo_divisor; };
    return h;
}

template<typename Type>
inline constexpr auto radix() -> decltype(std::numeric_limits<Type>::max() - std::numeric_limits<Type>::min() + 1)
{
    return std::numeric_limits<Type>::max() - std::numeric_limits<Type>::min() + 1;
}

// floating point numbers -> sign, exponent, mantissa
// sign_bits = std::numeric_limits<type>::is_signed
// exponent_size = sizeof(type) * CHAR_BIT - std::numeric_limits<type>::is_signed - std::numeric_limits<float>::digits
template<typename Float_type>
std::size_t hash(Float_type value)
{
    union {
        Float_type f;
        std::size_t s;
    } u;
    u.f = value;
    // return bits ^ (bits >> 32);
    return u.s & ~(~0 >> std::numeric_limits<Float_type>::digits);
}

//public static int hashCode(double value) {
//    long bits = doubleToLongBits(value);
//    return (int)(bits ^ (bits >>> 32));
//}

//template<typename Size_type>
//inline Size_type loadword(const void* p)
//{
//    Size_type r;
//    std::memcpy(&r, p, sizeof(r));
//    return r;
//}
//
//template<typename Type, size_t = sizeof(Type) / sizeof(size_t)>
//struct scalar_hash;
//
//template<typename Type>
//struct scalar_hash<Type, 0> : public std::unary_function<Type, size_t> {
//    inline virtual size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            size_t a;
//        } u;
//        u.a = 0;
//        u.t = v;
//        return u.a;
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 1> : public std::unary_function<Type, size_t> {
//    inline virtual size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            size_t a;
//        } u;
//        u.t = v;
//        return u.a;
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 2> : public std::unary_function<Type, size_t> {
//    inline virtual size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 3> : public std::unary_function<Type, size_t> {
//    inline virtual size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//                size_t c;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 4> : public std::unary_function<Type, size_t> {
//    inline virtual size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//                size_t c;
//                size_t d;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//template<>
//struct hash<float> : public scalar_hash<float> {
//    inline
//    size_t operator()(float v) const noexcept
//    {
//        // -0.0 and 0.0 should return same hash
//        if (v == 0) { return 0; }
//        return scalar_hash<float>::operator()(v);
//    }
//};
//
//template<>
//struct hash<double>
//        : public scalar_hash<double> {
//    inline
//    size_t operator()(double v) const noexcept
//    {
//        // -0.0 and 0.0 should return same hash
//        if (v == 0) {
//            return 0;
//        }
//        return scalar_hash<double>::operator()(v);
//    }
//};
//
//template<>
//struct hash<long double> : public scalar_hash<long double> {
//    inline size_t operator()(long double v) const noexcept
//    {
//        // -0.0 and 0.0 should return same hash
//        if (v == 0) {
//            return 0;
//        }
//#if defined(i386)
//        // Zero out padding bits
//        union
//        {
//            long double t;
//            struct
//            {
//                size_t a;
//                size_t b;
//                size_t c;
//                size_t d;
//            } s;
//        } u;
//        u.s.a = 0;
//        u.s.b = 0;
//        u.s.c = 0;
//        u.s.d = 0;
//        u.t = v;
//        return u.s.a ^ u.s.b ^ u.s.c ^ u.s.d;
//#elif defined(x86_64)
//        // Zero out padding bits
//        union {
//            long double t;
//            struct {
//                size_t a;
//                size_t b;
//            } s;
//        } u;
//        u.s.a = 0;
//        u.s.b = 0;
//        u.t = v;
//        return u.s.a ^ u.s.b;
//#else
//        return scalar_hash<long double>::operator()(v);
//#endif
//    }
//};
//
//// cityhash64
//template<typename Size_type>
//Size_type murmur2_or_cityhash<Size_type, 64>::operator()(const void* key, Size_type len)
//{
//    const char* s = static_cast<const char*>(key);
//    if (len <= 32) {
//        if (len <= 16) {
//            return hash_len_0_to_16(s, len);
//        } else {
//            return hash_len_17_to_32(s, len);
//        }
//    } else if (len <= 64) {
//        return hash_len_33_to_64(s, len);
//    }
//
//    // For strings over 64 bytes we hash the end first, and then as we
//    // loop we keep 56 bytes of state: v, w, x, y, and z.
//    Size_type x = loadword<Size_type>(s + len - 40);
//    Size_type y = loadword<Size_type>(s + len - 16) +
//                  loadword<Size_type>(s + len - 56);
//    Size_type z = hash_len_16(loadword<Size_type>(s + len - 48) + len,
//                              loadword<Size_type>(s + len - 24));
//    std::pair<Size_type, Size_type> v = weak_hash_len_32_with_seeds(s + len - 64, len, z);
//    std::pair<Size_type, Size_type> w = weak_hash_len_32_with_seeds(s + len - 32, y + k1, x);
//    x = x * k1 + loadword<Size_type>(s);
//
//    // Decrease len to the nearest multiple of 64, and operate on 64-byte chunks.
//    len = (len - 1) & ~static_cast<Size_type>(63);
//    do {
//        x = rotate(x + y + v.first + loadword<Size_type>(s + 8), 37) * k1;
//        y = rotate(y + v.second + loadword<Size_type>(s + 48), 42) * k1;
//        x ^= w.second;
//        y += v.first + loadword<Size_type>(s + 40);
//        z = rotate(z + w.first, 33) * k1;
//        v = weak_hash_len_32_with_seeds(s, v.second * k1, x + w.first);
//        w = weak_hash_len_32_with_seeds(s + 32, z + w.second,
//                                        y + loadword<Size_type>(s + 16));
//        std::swap(z, x);
//        s += 64;
//        len -= 64;
//    } while (len != 0);
//    return hash_len_16(
//            hash_len_16(v.first, w.first) + shift_mix(y) * k1 + z,
//            hash_len_16(v.second, w.second) + x);
//}
//
//template<typename Type, size_t = sizeof(Type) / sizeof(size_t)>
//struct scalar_hash;
//
//template<typename Type>
//struct scalar_hash<Type, 0>
//        : public std::unary_function<Type, size_t> {
//    inline
//    size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            size_t a;
//        } u;
//        u.a = 0;
//        u.t = v;
//        return u.a;
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 1>
//        : public std::unary_function<Type, size_t> {
//    inline
//    size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            size_t a;
//        } u;
//        u.t = v;
//        return u.a;
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 2>
//        : public std::unary_function<Type, size_t> {
//    inline
//    size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 3>
//        : public std::unary_function<Type, size_t> {
//    inline
//    size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//                size_t c;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//template<typename Type>
//struct scalar_hash<Type, 4>
//        : public std::unary_function<Type, size_t> {
//    inline
//    size_t operator()(Type v) const noexcept
//    {
//        union {
//            Type t;
//            struct {
//                size_t a;
//                size_t b;
//                size_t c;
//                size_t d;
//            } s;
//        } u;
//        u.t = v;
//        return murmur2_or_cityhash<size_t>()(&u, sizeof(u));
//    }
//};
//
//// murmur2
//template<typename Size_type>
//Size_type
//murmur2_or_cityhash<Size_type, 32>::operator()(const void* key, Size_type len)
//{
//    const Size_type m = 0x5bd1e995;
//    const Size_type r = 24;
//    Size_type h = len;
//    const unsigned char* data = static_cast<const unsigned char*>(key);
//    for (; len >= 4; data += 4, len -= 4) {
//        Size_type k = loadword<Size_type>(data);
//        k *= m;
//        k ^= k >> r;
//        k *= m;
//        h *= m;
//        h ^= k;
//    }
//    switch (len) {
//        case 3:
//            h ^= data[2] << 16;
//        case 2:
//            h ^= data[1] << 8;
//        case 1:
//            h ^= data[0];
//            h *= m;
//    }
//    h ^= h >> 13;
//    h *= m;
//    h ^= h >> 15;
//    return h;
//}
//
//template<typename Size_type>
//struct murmur2_or_cityhash<Size_type, 64> {
//    Size_type operator()(const void* key, Size_type len);
//
//private:
//    // Some primes between 2^63 and 2^64.
//    static const Size_type k0 = 0xc3a5c85c97cb3127ULL;
//    static const Size_type k1 = 0xb492b66fbe98f273ULL;
//    static const Size_type k2 = 0x9ae16a3b2f90404fULL;
//    static const Size_type k3 = 0xc949d7c7509e6557ULL;
//
//    static Size_type rotate(Size_type val, int shift)
//    {
//        return shift == 0 ? val : ((val >> shift) | (val << (64 - shift)));
//    }
//
//    static Size_type rotate_by_at_least_1(Size_type val, int shift)
//    {
//        return (val >> shift) | (val << (64 - shift));
//    }
//
//    static Size_type shift_mix(Size_type val)
//    {
//        return val ^ (val >> 47);
//    }
//
//    static Size_type hash_len_16(Size_type u, Size_type v)
//    {
//        const Size_type mul = 0x9ddfea08eb382d69ULL;
//        Size_type a = (u ^ v) * mul;
//        a ^= (a >> 47);
//        Size_type b = (v ^ a) * mul;
//        b ^= (b >> 47);
//        b *= mul;
//        return b;
//    }
//
//    static Size_type hash_len_0_to_16(const char* s, Size_type len)
//    {
//        if (len > 8) {
//            const Size_type a = loadword<Size_type>(s);
//            const Size_type b = loadword<Size_type>(s + len - 8);
//            return hash_len_16(a, rotate_by_at_least_1(b + len, len)) ^ b;
//        }
//        if (len >= 4) {
//            const uint32_t a = loadword<uint32_t>(s);
//            const uint32_t b = loadword<uint32_t>(s + len - 4);
//            return hash_len_16(len + (a << 3), b);
//        }
//        if (len > 0) {
//            const unsigned char a = s[0];
//            const unsigned char b = s[len >> 1];
//            const unsigned char c = s[len - 1];
//            const uint32_t y = static_cast<uint32_t>(a) +
//                               (static_cast<uint32_t>(b) << 8);
//            const uint32_t z = len + (static_cast<uint32_t>(c) << 2);
//            return shift_mix(y * k2 ^ z * k3) * k2;
//        }
//        return k2;
//    }
//
//    static Size_type hash_len_17_to_32(const char* s, Size_type len)
//    {
//        const Size_type a = loadword<Size_type>(s) * k1;
//        const Size_type b = loadword<Size_type>(s + 8);
//        const Size_type c = loadword<Size_type>(s + len - 8) * k2;
//        const Size_type d = loadword<Size_type>(s + len - 16) * k0;
//        return hash_len_16(rotate(a - b, 43) + rotate(c, 30) + d,
//                           a + rotate(b ^ k3, 20) - c + len);
//    }
//
//    // Return a 16-byte hash for 48 bytes.  Quick and dirty.
//    // Callers do best to use "random-looking" values for a and b.
//    static std::pair<Size_type, Size_type> weak_hash_len_32_with_seeds(
//            Size_type w, Size_type x, Size_type y, Size_type z, Size_type a, Size_type b)
//    {
//        a += w;
//        b = rotate(b + a + z, 21);
//        const Size_type c = a;
//        a += x;
//        a += y;
//        b += rotate(a, 44);
//        return std::pair<Size_type, Size_type>(a + z, b + c);
//    }
//
//    // Return a 16-byte hash for s[0] ... s[31], a, and b.  Quick and dirty.
//    static std::pair<Size_type, Size_type> weak_hash_len_32_with_seeds(
//            const char* s, Size_type a, Size_type b)
//    {
//        return weak_hash_len_32_with_seeds(loadword<Size_type>(s),
//                                           loadword<Size_type>(s + 8),
//                                           loadword<Size_type>(s + 16),
//                                           loadword<Size_type>(s + 24),
//                                           a,
//                                           b);
//    }
//
//    // Return an 8-byte hash for 33 to 64 bytes.
//    static Size_type hash_len_33_to_64(const char* s, size_t len)
//    {
//        Size_type z = loadword<Size_type>(s + 24);
//        Size_type a = loadword<Size_type>(s) +
//                      (len + loadword<Size_type>(s + len - 16)) * k0;
//        Size_type b = rotate(a + z, 52);
//        Size_type c = rotate(a, 37);
//        a += loadword<Size_type>(s + 8);
//        c += rotate(a, 7);
//        a += loadword<Size_type>(s + 16);
//        Size_type vf = a + z;
//        Size_type vs = b + rotate(a, 31) + c;
//        a = loadword<Size_type>(s + 16) + loadword<Size_type>(s + len - 32);
//        z += loadword<Size_type>(s + len - 8);
//        b = rotate(a + z, 52);
//        c = rotate(a, 37);
//        a += loadword<Size_type>(s + len - 24);
//        c += rotate(a, 7);
//        a += loadword<Size_type>(s + len - 16);
//        Size_type wf = a + z;
//        Size_type ws = b + rotate(a, 31) + c;
//        Size_type r = shift_mix((vf + ws) * k2 + (wf + vs) * k0);
//        return shift_mix(r * k0 + vs) * k2;
//    }
//};

int dynamic_knapsack()
{
    std::cout << std::numeric_limits<float>::digits << "\n";
    std::cout << std::numeric_limits<float>::max_exponent << "\n";
    std::cout << std::numeric_limits<float>::min_exponent << "\n";
    std::cout << sizeof(float) * CHAR_BIT << "\n";
    std::cout << std::numeric_limits<float>::is_signed << "\n";
    std::cout << sizeof(float) * CHAR_BIT - std::numeric_limits<float>::is_signed - std::numeric_limits<float>::digits << "\n";
    std::cout << sizeof(std::size_t) << "\n";
    std::cout << std::numeric_limits<long double>::digits << "\n";
    return 0;
}
