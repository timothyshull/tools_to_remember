#include "testing_utility.h"

std::string testing_utility::rand_string(std::size_t size)
{
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<char> dis{0, std::numeric_limits<char>::max()};
    std::string r;
    for (auto i = 0; i < size; ++i) { r += dis(gen); }
    return r;
}
