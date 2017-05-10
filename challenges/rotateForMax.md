# Rotate for a Max

Take a number: `56789`. Rotate left, you get `67895`.

Keep the first digit in place and rotate left the other digits: `68957`.

Keep the first two digits in place and rotate the other ones: `68579`.

Keep the first three digits and rotate left the rest: `68597`. Now it is over since keeping the first four it remains only one digit which rotated is itself.

You have the following sequence of numbers:

`56789` -> `67895` -> `68957` -> `68579` -> `68597`

and you must return the greatest: 68957.

Calling this function `maxRot`
`maxRot(56789)` should return `68957`

[Source](https://www.codewars.com/kata/rotate-for-a-max/train/cpp)

# Solution

```cpp
#include <algorithm>
#include <string>

class MaxRotate
{
public:
  static long long maxRot(long long n);
};

long long MaxRotate::maxRot(long long n) 
{
    // Convert it to a string for easier rotation
    std::string n_string = std::to_string(n);
    // Move the rotation start point forward by one each round
    for (int i = 0; i < n_string.length() - 1; i++) {
        // Rotate the string at point i
        std::rotate(n_string.begin() + i, n_string.begin() + 1 + i, n_string.end());
        // find the max between this rotation and last max
        n = std::max(std::stoll(n_string), n);
    }    
    return n;
}
```

# Notes

Can't help but feels there's a more mathematical way to shift numbers.

Learned about `std::rotate` and `std::to_string`.
