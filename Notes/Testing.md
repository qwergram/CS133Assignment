# C++ Testing
Since I always seem to forget what settings in VS2015 to change whenever creating UnitTests, I'll just quickly write a guide here.
There are two testing frameworks I've enjoyed working with over the last few months, one being the aforementioned unit tests and the other 
being [catch.hpp](https://github.com/philsquared/Catch).

# C++ Testing with Catch.hpp

This guide is mainly used for a quick set up for me in case I forget. By no means is this the definite guide on how to
set up catch.hpp for your project.

## Step 0: Download catch.hpp into project directory

Download the latest release version of [catch.hpp](https://github.com/philsquared/Catch/blob/master/README.md) and save it to your project
directory.

![](http://imgur.com/0vk1qnJ.png)

## Step 1: Create a new `cpp` file
In the image above, I named it `avlTests.cpp`. You are free to name it whatever you like. In it, paste the following code:

```cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "project_you_are_testing.h"

// ... your tests here ...
```

## Step 2: Running your tests
The problem with catch, is that the window goes away before you can actually see your results. While you could step
through your program, an easier solution is to write the following and paste it into a batch file:

**x86 Programs:**

```
@echo off
.\Debug\NameOfProject.exe
pause
```

**64x Programs:**

```
@echo off
.\x64\Debug\NameOfProject.exe
pause
```

Paste this in the same directory as your `.sln` file.

# C++ Testing with MS Native Unit Tests

## Step 0: Create a new Testing Project

![](http://imgur.com/7hudvbR.png)

## Step 1: Go to Project Properties

![](http://imgur.com/fJm8BvZ.png)

## Step 2: Paste in Location of all `OBJ` objects

Find the location of all project `.obj` files of project you're trying to test.

Paste file path of *EACH `.OBJ` FILE* of that in `Additional Dependencies` window. Save and Exit.

![](http://imgur.com/ECRRZjL.png)

## Step 3: Switching between `x64` and `win32`

If you run your tests and they all fail and you see this error message:

![](http://imgur.com/7Axih6Z.png)

It means you need to switch from `x64` to `win32`. To do this, open up the properties of the test project.

![](http://imgur.com/h6DV9QX.png)

Open up "Configuration Manager" and change to `x86`/`win32` (Just not `x64`)

![](http://imgur.com/70r6baE.png)

![](http://imgur.com/0Fq9hYh.png)

Save and close the window. Once back on the properties window again, make sure it says `Active(Win32)`.

![](http://imgur.com/q8nW7wt.png)

Close the window and build your entire project again (`CTRL+SHIFT+B`).
When succesfully built, open up the test properties again and go to the input linking tab again that you went to in Step 1.

Locate the new location of your `x86` build and paste the `.obj` file paths into your linker input settins like you did in Step 2.

![](http://imgur.com/dXEFVoC.png)

## Step 4: C++ Template Class

Interestingly, if you're using C++ template classes, and followed all the steps listed above and you still get linking errors like these:

![](http://imgur.com/wm6ee0v.png)

You need to include the following include in your testing file:
```cpp
#include "..\project_to_test_name\thing_to_test.h"
#include "..\project_to_test_name\thing_to_test.cpp"
```

Otherwise, any of the definitions defined in the `.cpp` file will not register with the unit tester.

# References
- [UW's Mark Schofield 2/16/2011](https://courses.cs.washington.edu/courses/cse403/11wi/lectures/UnitTestinginWindows.pdf)

