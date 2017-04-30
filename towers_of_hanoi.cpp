#include <array>
#include <cassert>
#include <iostream>
#include <random>
#include <stack>

// prints instructions
void sedgewick_hanoi(int n, bool left)
{
    if (n == 0) { return; }
    sedgewick_hanoi(n - 1, !left);
    if (left) { std::cout << n << " left\n"; }
    else { std::cout << n << " right\n"; }
    sedgewick_hanoi(n - 1, !left);
}

void count_hanoi_steps(
        int num_steps,
        int num_rings_to_move, std::array<std::stack<int>, 3>& pegs, int from_peg, int to_peg, int use_peg)
{
    if (num_rings_to_move > 0) {
        count_hanoi_steps(num_steps, num_rings_to_move - 1, pegs, from_peg, use_peg, to_peg);
        auto top = pegs[from_peg].top();
        pegs[to_peg].push(top);
        pegs[from_peg].pop();
        std::cout << "Move from peg " << from_peg << " to peg " << to_peg << "\n";
        // ++num_steps;
        count_hanoi_steps(num_steps + 1, num_rings_to_move - 1, pegs, use_peg, to_peg, from_peg);
    }
}

int compute_hanoi(int num_rings)
{
    const static int num_pegs = 3;
    int num_steps = 0;
    std::array<std::stack<int>, num_pegs> pegs;
    for (auto i = num_rings; i >= 1; --i) {
        pegs[0].push(i);
    }
    count_hanoi_steps(num_steps, num_rings, pegs, 0, 1, 2);
    return num_steps;
}


int main(int argc, char* argv[])
{
    int n;
    if (argc == 2) {
        n = std::atoi(argv[1]);
    } else {
        std::random_device rd;
        std::default_random_engine gen{rd()};
        std::uniform_int_distribution<int> dis{1, 10};
        n = dis(gen);
    }
    std::cout << "n = " << n << "\n";
    compute_hanoi(n);

    auto num_steps = compute_hanoi(4);
    assert(15 == num_steps);

    num_steps = compute_hanoi(1);
    assert(1 == num_steps);

    num_steps = compute_hanoi(0);
    assert(0 == num_steps);

    num_steps = compute_hanoi(10);
    assert(1023 == num_steps);

    return 0;
}
