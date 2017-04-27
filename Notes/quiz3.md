# CS 133 Quiz 3 Spring 2017
## Directions:
Using the `STL list` class and `iterator`s 
(but not using any `string` class methods or operators <besides a constructor, =, `begin`, `end`
or `pushback`> or any c-style `string`s, `stringstream`s or any other non-string, 
non-iterator or non-list structures) write the definition for the function: 
`list<string> split(const string& phrase, char delimiter = ' ');`
which should take in a `string` phrase (and possibly a different `delimiter`) and return a 
`list<string>` containing, in order, all of the words in the original phrase. A word here is 
considered to be contiguous collections of characters bordered by the delimiter or the beginning 
or end of the string.

By way of example, the call:
```cpp
string s(" one, two, three");
list<string> words = split(s);
```

`words` should be a list containing:
- "one,"
- "two,"
- "three"

```cpp
string s("   one, two,   three");
list<string> words = split(s, ',');
```

`words` should be a list containing:
- " one"
- " two"
- " three"

Don’t forget to test your code. You may use the compiler, your browser and any written material you wish. You may not utilize other people, electronically or in-person.
When you are done, submit the single `.cpp` file that includes your main for testing (with your name in the header) to Canvas/Quiz 3.