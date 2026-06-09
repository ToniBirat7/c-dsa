#include <iostream>
using namespace std;

int factorial(int n) {

  // Time Complexity -> O(n) because as the input size grows, for 2 - 2 calls, 3 -> 3 calls and so on
  // Space Complexity -> O(n) because for each recursive call all the variables are created fresh in the memory
  if (n == 1) {
    return 1;
  }

  return n * factorial(n-1);
}

int main()
{
  int fact = factorial(4);
  printf("The Factorial is : %d", fact);
}
