1. Due to the c++ compiler issue, c++ might cannot handle the operation of
raising an integer to a large power. Here is an instance of p and q that can work:
p=3, q=7 → pq = 21, (p-1)(q-1) = 12, pick e = 5, then d = 5 (5*5 mod 12 = 1, so 5 is
the inverse of 5 mod 12)
2. If we want to randomly generate two initial prime numbers, then we need a
function to test primality.
Use the definition of prime number to guide your implementation of the following
function.
For any positive integers n, r, s, if n=rs, then r<=sqrt(n) or s<=sqrt(n)
/* return true if n is prime
return false if n is not prime
Precondition: n>1
*/
bool IsPrime (int n)
