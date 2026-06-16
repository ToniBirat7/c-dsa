#include <iostream>
using namespace std;

int factorial(int n) {

  // Time Complexity -> O(n) because as the input size grows, for input n total recursive calls are (n + 1)
  // Space Complexity -> O(n) because for each recursive call all the variables are created fresh in the stack frame
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