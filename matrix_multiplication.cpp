#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <random>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

namespace Matrix_multiplication {
    template<typename Item_type>
    void show(std::vector<std::vector<Item_type>>& a)
    {
        auto n = a.size();
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) { std::cout << std::setprecision(4) << a[i][j] << " "; }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }

    template<typename Item_type>
    void profile_matrix_mult(
            std::vector<std::vector<Item_type>>& a,
            std::vector<std::vector<Item_type>>& b,
            void(* func)(const std::vector<std::vector<Item_type>>&, const std::vector<std::vector<Item_type>>&, std::vector<std::vector<Item_type>>&)
    )
    {
        auto n = a.size();
        std::vector<std::vector<Item_type>> c(n, std::vector<Item_type>(n));
        auto start = std::chrono::high_resolution_clock::now();
        func(a, b, c);
        auto stop = std::chrono::high_resolution_clock::now();
        auto elapsed = stop - start;
        // elapsed = (stop - start) / 1000.0;
        std::cout << elapsed.count() << "\n\n";
        // if (n < 10) { show(c); }
        // show(c);
    }

    // order 1: ijk = dot product version
    template<typename Item_type>
    void matrix_mult_order_1(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                for (auto k = 0; k < n; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 2: ikj
    template<typename Item_type>
    void matrix_mult_order_2(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        for (auto i = 0; i < n; ++i) {
            for (auto k = 0; k < n; ++k) {
                for (auto j = 0; j < n; ++j) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 3: jik
    template<typename Item_type>
    void matrix_mult_order_3(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        for (auto j = 0; j < n; ++j) {
            for (auto i = 0; i < n; ++i) {
                for (auto k = 0; k < n; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 4: jki = GAXPY version
    template<typename Item_type>
    void matrix_mult_order_4(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        for (auto j = 0; j < n; ++j) {
            for (auto k = 0; k < n; ++k) {
                for (auto i = 0; i < n; ++i) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 5: kij
    template<typename Item_type>
    void matrix_mult_order_5(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {

        auto n = a.size();
        for (auto k = 0; k < n; ++k) {
            for (auto i = 0; i < n; ++i) {
                for (auto j = 0; j < n; ++j) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 6: kji = outer product version
    template<typename Item_type>
    void matrix_mult_order_6(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        for (auto k = 0; k < n; ++k) {
            for (auto j = 0; j < n; ++j) {
                for (auto i = 0; i < n; ++i) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }

    // order 7: jik optimized ala JAMA
    template<typename Item_type>
    void matrix_mult_order_7(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();
        std::vector<Item_type> bcolj(n);
        Item_type sum;
        for (auto j = 0; j < n; ++j) {
            for (auto k = 0; k < n; ++k) { bcolj[k] = b[k][j]; }
            for (auto i = 0; i < n; ++i) {
                std::vector<Item_type> arowi{a[i]};
                sum = 0;
                for (auto k = 0; k < n; ++k) { sum += arowi[k] * bcolj[k]; }
                c[i][j] = sum;
            }
        }
    }

    // order 8: ikj pure row
    template<typename Item_type>
    void matrix_mult_order_8(
            const std::vector<std::vector<Item_type>>& a,
            const std::vector<std::vector<Item_type>>& b,
            std::vector<std::vector<Item_type>>& c
    )
    {
        auto n = a.size();

        std::vector<Item_type> arowi;
        std::vector<Item_type> crowi;
        std::vector<Item_type> browk;
        Item_type aik;
        for (auto i = 0; i < n; ++i) {
            arowi = a[i];
            crowi = c[i];
            for (auto k = 0; k < n; ++k) {
                browk = b[k];
                aik = arowi[k];
                for (auto j = 0; j < n; ++j) { crowi[j] += aik * browk[j]; }
            }
            // bug from Sedgewick -> missing this line
            c[i] = crowi;
        }
    }

    // only consistent profiling is that last two elements are the slowest
    // 5 ran faster for large matrices
    void profile_all(std::size_t n)
    {
        std::vector<std::vector<double>> a(n, std::vector<double>(n));
        std::vector<std::vector<double>> b(n, std::vector<double>(n));
        std::vector<std::vector<double>> c(n, std::vector<double>(n));

        std::random_device rd;
        std::default_random_engine gen{rd()};
        std::uniform_real_distribution<double> dis{0.0, 1.0};

        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                a[i][j] = dis(gen);
                b[i][j] = dis(gen);
            }
        }

        profile_matrix_mult<double>(a, b, matrix_mult_order_1);
        profile_matrix_mult<double>(a, b, matrix_mult_order_2);
        profile_matrix_mult<double>(a, b, matrix_mult_order_3);
        profile_matrix_mult<double>(a, b, matrix_mult_order_4);
        profile_matrix_mult<double>(a, b, matrix_mult_order_5);
        profile_matrix_mult<double>(a, b, matrix_mult_order_6);
        profile_matrix_mult<double>(a, b, matrix_mult_order_7);
        profile_matrix_mult<double>(a, b, matrix_mult_order_8);
    }

};

TEST(matrix_multiplication, compare_random_1_2)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_2(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_3)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_3(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_4)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_4(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_5)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_5(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_6)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_6(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_7)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_7(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

TEST(matrix_multiplication, compare_random_1_8)
{
    std::size_t n{100};
    std::vector<std::vector<double>> a(n, std::vector<double>(n));
    std::vector<std::vector<double>> b(n, std::vector<double>(n));

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_real_distribution<double> dis{0.0, 1.0};

    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = dis(gen);
            b[i][j] = dis(gen);
        }
    }

    std::vector<std::vector<double>> c(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_1(a, b, c);
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    Matrix_multiplication::matrix_mult_order_8(a, b, d);

    ASSERT_THAT(c, Eq(d));
}

