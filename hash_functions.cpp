// #include
#include <limits>
#include <iostream>

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
    std::size_t h{17};
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
    std::size_t h{0};
    std::size_t r{static_cast<std::size_t>(std::numeric_limits<std::string::value_type>::max() - std::numeric_limits<std::string::value_type>::min())};
    for (auto c : s) { h = (r * h + c) % modulo_divisor; };
    return h;
}

int main()
{
    std::cout << std::numeric_limits<std::string::value_type>::max() - std::numeric_limits<std::string::value_type>::min() + 1 << "\n";
    return 0;
}
