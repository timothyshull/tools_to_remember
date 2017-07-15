#include <cstddef>
#include <functional>
#include <iostream>
#include <cassert>


// #include <memory>
// std::__murmur2_or_cityhash<>


// refer to <functional> for hash types
// refer to <cfloat> for float value macros including FLT_MANT_DIG
// all check for 0 and return 0 to avoid 0 vs -0
// resort to Murmur2 hash function and CityHash hash functions (now Murmur3)

// floating point numbers -> sign, exponent, mantissa
// sign_bits = std::numeric_limits<type>::is_signed
// exponent_size = sizeof(type) * std::numeric_limits<unsigned char>::digits - std::numeric_limits<type>::is_signed - std::numeric_limits<float>::digits
// TODO: better to use reinterpret_cast than union
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

template<typename Float_type>
std::size_t hash2(Float_type value)
{
    union {
        Float_type f;
        std::size_t s;
    } u;
    u.f = value;
    // return bits ^ (bits >> 32);
    return u.s & ~(~0 >> std::numeric_limits<Float_type>::digits);
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
    // return (hash(x) & 0x7FFFFFFF) % modulo_divisor;
    // return (hash(x) & (~(0UL) >> 1) % modulo_divisor;
    return hash(x) % modulo_divisor; // since it is size_t
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
    auto hash_val = std::size_t{17};
    hash_val = 31 * hash_val + std::hash<char>{}(obj.c);
    hash_val = 31 * hash_val + std::hash<short>{}(obj.s);
    hash_val = 31 * hash_val + std::hash<int>{}(obj.i);
    hash_val = 31 * hash_val + std::hash<long>{}(obj.l);
    hash_val = 31 * hash_val + std::hash<float>{}(obj.f);
    hash_val = 31 * hash_val + std::hash<double>{}(obj.d);
    return hash_val;
}

template<>
std::size_t hash<std::string>(const std::string& str, std::size_t modulo_divisor)
{
    using Char_type = std::string::value_type;
    auto range = std::numeric_limits<Char_type>::max() - std::numeric_limits<Char_type>::min();
    auto hash_val = std::size_t{0};
    auto radix = static_cast<std::size_t>(range);
    for (auto c : str) {
        hash_val = (radix * hash_val + c) % modulo_divisor;
    };
    return hash_val;
}

template<typename Type>
inline constexpr auto radix() -> decltype(std::numeric_limits<Type>::max() - std::numeric_limits<Type>::min() + 1)
{
    return std::numeric_limits<Type>::max() - std::numeric_limits<Type>::min() + 1;
}


