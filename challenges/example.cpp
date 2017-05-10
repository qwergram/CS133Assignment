#include <string>
#include <math.h>

class DigPow
{
public:
  static int digPow(int n, int p);
};

int DigPow::digPow(int n, int p) {
  std::string n_string = std::to_string(n);
  long sum = 0;
  for (char number : n_string) {
    sum += pow(number, p++);
  }
  if (sum % n == 0) 
    return sum / n;
  return -1;
}