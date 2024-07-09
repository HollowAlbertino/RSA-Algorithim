#include <iostream>
#include <tuple>
#include <cmath>
#include <cassert>

using namespace std;

// Euclidean Algorithm to calculate the greatest common divisor
int EuclideanGCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm
tuple<int, int, int> ExtendedEuclideanGCD(int a, int b) {
    int x = 0, y = 1, u = 1, v = 0;
    while (a != 0) {
        int q = b / a;
        int r = b % a;
        int m = x - u * q;
        int n = y - v * q;
        b = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    return make_tuple(b, x, y);
}

// Modulo function
int mod(int a, int n) {
    return (a % n + n) % n;
}

// Function to find a number relatively prime to n
int RelativelyPrime(int n) {
    for (int i = 2; i < n; ++i) {
        if (EuclideanGCD(i, n) == 1) {
            return i;
        }
    }
    return 2; // If no number < n is found, return 2 by default (always prime relative to any n > 2)
}

// Function to find the modular inverse
int inverse(int a, int n) {
    int d, s, t;
    tie(d, s, t) = ExtendedEuclideanGCD(a, n);
    if (d == 1) {
        return mod(s, n);
    } else {
        cerr << "a and n are not relatively prime!" << endl;
        exit(EXIT_FAILURE);
    }
}

// Function to test if a number is prime
bool IsPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// RSA encode function
int Encode(int M, int e, int PQ) {
    long long result = 1;
    M = mod(M, PQ);
    while (e > 0) {
        if (e % 2 == 1)
            result = (result * M) % PQ;
        e = e >> 1;
        M = ((long long)M * M) % PQ;
    }
    return result;
}

// RSA decode function
int Decode(int C, int d, int PQ) {
    long long result = 1;
    C = mod(C, PQ);
    while (d > 0) {
        if (d % 2 == 1)
            result = (result * C) % PQ;
        d = d >> 1;
        C = ((long long)C * C) % PQ;
    }
    return result;
}

// Main function to demonstrate the RSA algorithm
int main() {
    // RSA setup
    const int P = 23;
    const int Q = 17;
    int PQ = P * Q;
    int phi = (P - 1) * (Q - 1);

    // Finding e that is relatively prime to (p-1)(q-1)
    int e = RelativelyPrime(phi);
    cout << "Chosen e: " << e << endl;

    // Calculating d, the modular inverse of e
    int d = inverse(e, phi);
    cout << "Calculated d: " << d << endl;

    // Testing the RSA algorithm
    int M;
    cout << "Enter an integer that is smaller than " << PQ << ": ";
    cin >> M;
    int C = Encode(M, e, PQ);
    int M1 = Decode(C, d, PQ);
    assert(M == M1);

    cout << "RSA algorithm works correctly." << endl;

    return 0;
}
