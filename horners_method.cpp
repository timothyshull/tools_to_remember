#include <vector>
#include <cmath>
#include <random>
#include <limits>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

// assumes coefficients in order c0, c1, c2, ..., cn for polynomial cn*x^n + ... + c1*x + c0
template<typename Number_type>
Number_type horners_method(Number_type x, std::vector<Number_type>& coeff)
{
    auto result = Number_type{0};
    for (auto  i = static_cast<int>(coeff.size() - 1); i >= 0; --i) {
        result = result * x + coeff[i];
    }
    return result;
}


template<typename Number_type>
Number_type manual_polynomial_check(Number_type x, std::vector<Number_type>& coeff)
{
    Number_type result{0.0};
    for (auto i = 0; i < coeff.size(); ++i) { result += std::pow(x, i) * coeff[i]; }
    return result;
}



TEST(horners_method, one_1_x_1_float)
{
    std::vector<float> v{1.0};
    auto r = horners_method<float>(1.0, v);
    ASSERT_THAT(r, Eq(1.0));
}

TEST(horners_method, two_1s_x_1_float)
{
    std::vector<float> v{1.0, 1.0};
    auto r = horners_method<float>(1.0, v);
    ASSERT_THAT(r, Eq(2.0));
}

TEST(horners_method, one_2_x_1_float)
{
    std::vector<float> v{2.0};
    auto r = horners_method<float>(1.0, v);
    ASSERT_THAT(r, Eq(2.0));
}

TEST(horners_method, two_2s_x_1_float)
{
    std::vector<float> v{2.0, 2.0};
    auto r = horners_method<float>(1.0, v);
    ASSERT_THAT(r, Eq(4.0));
}

TEST(horners_method, two_1s_x_2_float)
{
    std::vector<float> v{1.0, 1.0};
    auto r = horners_method<float>(2.0, v);
    ASSERT_THAT(r, Eq(3.0));
}

TEST(horners_method, three_1s_x_2_float)
{
    std::vector<float> v{1.0, 1.0, 1.0};
    auto r = horners_method<float>(2.0, v);
    ASSERT_THAT(r, Eq(7.0));
}

TEST(horners_method, random_doubles)
{
    std::size_t num_elems{10000};
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0, std::numeric_limits<double>::max()};

    std::vector<double> v(num_elems);
    for (auto i = 0; i < num_elems; ++i) { v[i] = dis(gen); }
    auto x = dis(gen);

    auto r1 = horners_method(x, v);
    auto r2 = manual_polynomial_check(x, v);

    ASSERT_THAT(r1, Eq(r2));
}