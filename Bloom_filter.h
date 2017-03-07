#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <vector>
#include <array>
#include <functional>

template<class Key, class Hash = std::hash<Key> >
struct Bloom_filter {
private:
    short _num_hashes;
    std::vector<bool> _bits;

public:

    Bloom_filter::Bloom_filter(std::size_t size, short num_hashes) : _bits(size), _num_hashes{num_hashes} {}

    ~Bloom_filter() = default;

    std::array<uint64_t, 2> hash(const std::vector<short>& vals, std::size_t len) const
    {
        std::array<std::size_t, 2> hash_value;
        MurmurHash3_x64_128(vals.data(), len, 0, hash_value.data());
        return hash_value;
    }

    inline std::size_t nth_hash(short n, std::size_t hash_a, std::size_t hash_b) const { return (hash_a + n * hash_b) % _bits.size(); }

    void add(const std::vector<short>& vals, std::size_t len)
    {
        auto hash_values = hash(vals, len);
        for (short n = 0; n < _num_hashes; ++n) { _bits[nth_hash(n, hash_values[0], hash_values[1])] = true; }
    }

    bool possibly_contains(const std::vector<short>& vals, std::size_t len) const
    {
        auto hash_values = hash(vals, len);
        for (short n = 0; n < _num_hashes; ++n) {
            if (!_bits[nth_hash(n, hash_values[0], hash_values[1])]) { return false; }
        }
        return true;
    }
};

#endif // BLOOM_FILTER_H
