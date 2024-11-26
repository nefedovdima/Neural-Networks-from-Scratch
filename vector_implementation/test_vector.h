#pragma once

#include <iostream>
#include "vector.h"

void test_push_back() {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    if (v.get_size() != 3) {
        std::cerr << "Test push_back failed: wrong size\n";
        return;
    }
    if (v[0] != 10 || v[1] != 20 || v[2] != 30) {
        std::cerr << "Test push_back failed: wrong values\n";
        return;
    }
    std::cout << "Test push_back passed\n";
}

void test_pop_back() {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.pop_back();

    if (v.get_size() != 1 || v[0] != 10) {
        std::cerr << "Test pop_back failed\n";
        return;
    }
    try {
        v.pop_back();
        v.pop_back();
        std::cerr << "Test pop_back failed: exception not thrown\n";
    } catch (const std::out_of_range&) {
        std::cout << "Test pop_back passed\n";
    }
}

void test_operator_brackets() {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v[0] = 100;

    if (v[0] != 100 || v[1] != 20) {
        std::cerr << "Test operator[] failed\n";
        return;
    }

    try {
        v[10] = 50;
        std::cerr << "Test operator[] failed: exception not thrown\n";
    } catch (const std::out_of_range&) {
        std::cout << "Test operator[] passed\n";
    }
}

void test_iterators() {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        sum += *it;
    }

    if (sum != 6) {
        std::cerr << "Test iterators failed\n";
        return;
    }
    std::cout << "Test iterators passed\n";
}

void test_clear() {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.clear();

    if (!v.is_empty() || v.get_size() != 0) {
        std::cerr << "Test clear failed\n";
        return;
    }
    std::cout << "Test clear passed\n";
}

void test_copy_assignment() {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    Vector<int> v2 = v1;

    if (v2.get_size() != 2 || v2[0] != 1 || v2[1] != 2) {
        std::cerr << "Test copy assignment failed\n";
        return;
    }

    v1[0] = 100;
    if (v2[0] == 100) {
        std::cerr << "Test copy assignment failed: shallow copy\n";
        return;
    }

    std::cout << "Test copy assignment passed\n";
}

void test_move_assignment() {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);

    Vector<int> v2 = std::move(v1);

    if (v2.get_size() != 2 || v2[0] != 1 || v2[1] != 2 || v1.get_size() != 0) {
        std::cerr << "Test move assignment failed\n";
        return;
    }

    std::cout << "Test move assignment passed\n";
}

void run_all_tests() {
    test_push_back();
    test_pop_back();
    test_operator_brackets();
    test_iterators();
    test_clear();
    test_copy_assignment();
    test_move_assignment();
}
