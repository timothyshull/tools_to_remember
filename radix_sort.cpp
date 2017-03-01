#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

auto radix = static_cast<std::size_t>(1 << (sizeof(char) * CHAR_BIT));

template<typename Item_type>
std::size_t get_word(const Item_type& a, int d)
{
    auto shift = (CHAR_BIT * (sizeof(Item_type) - d - 1)) % (sizeof(Item_type) * CHAR_BIT); // avoid undefined behavior
    return static_cast<std::size_t>((a >> shift) & 0xFF);
}

template<typename Item_type>
void lsd_radix_sort(std::vector<Item_type>& a)
{
    auto w = sizeof(Item_type);
    std::vector<Item_type> aux(a.size());
    for (int d = w - 1; d >= 0; --d) {
        std::vector<std::size_t> count(radix + 1, 0);
        for (auto e : a) { ++count[get_word(e, d) + 1]; }
        for (auto i = 1; i < count.size(); ++i) { count[i] += count[i - 1]; }
        for (auto e : a) { aux[count[get_word(e, d)]++] = e; }
        a = aux;
    }
}

template<>
void lsd_radix_sort<std::string>(std::vector<std::string>& a)
{
    auto radix = static_cast<std::size_t>(std::pow(2.0, sizeof(char) * CHAR_BIT));
    auto w = a[0].size();

    std::vector<std::string> aux(a.size());
    for (int d = static_cast<int>(w - 1); d >= 0; --d) {
        std::vector<std::size_t> count(radix + 1, 0);
        for (auto e : a) { ++count[e[d] + 1]; }
        for (auto i = 1; i < count.size(); ++i) { count[i] += count[i - 1]; }
        for (auto e : a) { aux[count[e[d]]++] = e; }
        a = aux;
    }
}

//template<typename Item_type>
//void msd_radix_sort(std::vector<Item_type>& a, std::vector<Item_type>& aux, std::vector<std::size_t> count, int lo, int hi, int d)
//{
//    if (hi <= lo + 1) { return; }
//    for (auto& e : count) { e = 0; }
//    for (auto e : a) { ++count[get_word(e, d) + 1]; }
//    for (auto i = 1; i < count.size(); ++i) { count[i] += count[i - 1]; }
//    for (auto e : a) { aux[count[get_word(e, d)]++] = e; }
//    a = aux;
//    for (auto i = 1; i < radix - 1; ++i) {
//        msd_radix_sort(a, aux, count, lo + count[i], lo + count[i + 1], d + 1);
//    }
//}
//
//template<typename Item_type>
//void msd_radix_sort(std::vector<Item_type>& a)
//{
//    std::vector<Item_type> aux(a.size());
//    std::vector<std::size_t> count(radix + 1);
//    msd_radix_sort(a, aux, count, 0, static_cast<int>(a.size()), 0);
//}

// begin tests

TEST(lsd_radix_sort, get_word_1)
{
    ASSERT_THAT(get_word(1, 0), Eq(0));
}

TEST(lsd_radix_sort, get_word_1_3)
{
    ASSERT_THAT(get_word(1, 3), Eq(1));
}

TEST(lsd_radix_sort, get_word_2_0)
{
    ASSERT_THAT(get_word(2, 0), Eq(0));
}

TEST(lsd_radix_sort, get_word_2_3)
{
    ASSERT_THAT(get_word(2, 3), Eq(2));
}

TEST(lsd_radix_sort, get_word_1_2)
{
    ASSERT_THAT(get_word(1, 2), Eq(0));
}

TEST(lsd_radix_sort, get_word_all_1s)
{
    ASSERT_THAT(get_word(~0, 3), Eq(0xFF));
}

TEST(lsd_radix_sort, get_word_max)
{
    ASSERT_THAT(get_word(std::numeric_limits<int>::max(), 0), Eq(0x7F));
}

TEST(lsd_radix_sort, sort)
{
    std::vector<int> v{2, 1, 3, 5, 6, 4};
    lsd_radix_sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(lsd_radix_sort, sort_1000_rand)
{
    std::size_t num_elems{1000};
    std::vector<int> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }

    auto tmp = v;
    lsd_radix_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

TEST(lsd_radix_sort, sort_1000_rand_strings)
{
    std::size_t num_elems = 1000;
    std::size_t string_size = 10;
    std::vector<std::string> v(num_elems);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<char> dis{0, std::numeric_limits<char>::max()};

    for (auto i = 0; i < num_elems; ++i) {
        std::string tmp;
        for (auto j = 0; j < string_size; ++j) { tmp += dis(gen); }
        v[i] = tmp;
    }

    auto tmp = v;
    lsd_radix_sort(v);
    std::sort(tmp.begin(), tmp.end());
    ASSERT_THAT(v, Eq(tmp));
}

//TEST(msd_radix_sort, sort_1000_rand)
//{
//    std::size_t num_elems{10};
//    std::vector<int> v(num_elems);
//
//    std::random_device rd;
//    std::default_random_engine gen{rd()};
//    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};
//
//    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }
//
//    auto tmp = v;
//    msd_radix_sort(v);
//    std::sort(tmp.begin(), tmp.end());
//    ASSERT_THAT(v, Eq(tmp));
//}

