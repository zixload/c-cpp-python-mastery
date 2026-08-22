/* Solution for LeetCode problem 3622 
You are given a positive integer n. Determine whether n is divisible by the sum of the following two values:
The digit sum of n (the sum of its digits).
The digit product of n (the product of its digits).
Return true if n is divisible by this sum; otherwise, return false.*/

int main() {
    int n = 123; // Example input
    int digitSum = 0;
    int digitProduct = 1;
    while (n > 0) {
        int chiffre = n % 10;

        digitSum += chiffre;
        digitProduct *= chiffre;

        n = n / 10;
    }
    // Check if n is divisible by the sum of digitSum and digitProduct
    if (digitSum + digitProduct != 0 && n % (digitSum + digitProduct) == 0) {
        return 1; // true
    } else {
        return 0; // false
    }
}