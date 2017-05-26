# CSS133 - C++ III at EDCC
CS133 assignments at EDCC/UW Student: [Norton Pengra](http://linkedin.com/in/nortonpengra)

Professor: Paul Bladek of EDCC

All the things I've learned in the realm of C++ and whatnot.

# Contributing

Hello Team 4, welcome to github.
Github is a tool that makes software collaboration easier. Here are
some of it's strengths that will benefit us:

- Easy rollback (if bad code is written, it's easy to go back to an early version)
- Automatic testing frameworks (with good tests, it's really hard to push bad code)

Here's how you can get started with github and git.

## 1. Downloading Git
First, install git from their [website](https://git-scm.com/downloads).
Once installed, open up a terminal of your choice (such as command prompt [`windows key + R` -> type in `cmd` -> hit `enter`] or powershell [`windows key + R` -> type in `powershell` -> hit `enter`]) and type `git`.

The output should look like this:
```
usage: git [--version] [--help] [-C <path>] [-c name=value]
           [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
           [-p | --paginate | --no-pager] [--no-replace-objects] [--bare]
           [--git-dir=<path>] [--work-tree=<path>] [--namespace=<name>]
           <command> [<args>]

... more lines below
```
If you see this, congrats! you've installed git correctly.

## 2. Cloning this project
The first step to contributing is to change to a directory you want
to work from. In this guideline, we'll assume the directory `C:\temp\`.
To clone this project, enter the following commands:
```
cd C:\temp\
git clone https://github.com/qwergram/CS133Assignment.git
```
This will create a directory named `CS133Assignment`. Go into it with:
```
cd CS133Assignment
```
Congrats! You've cloned this project.

## 3. Figuring out what you need to do
For this project, work to be done, doing and done will be recorded
in a kanban style board. [click here for the kanban board](https://github.com/qwergram/CS133Assignment/projects/1).
We will work in 2 day sprints. Everyone will pick a feature they presume
will take 2 days, and build it. Tag your card with your name so everyone
is aware of who is doing what. I will create the sprints and tasks
in class.

If you run into issues or have questions, don't email me. Put your issues in the issues board. [click here to see the issues board](https://github.com/qwergram/CS133Assignment/issues).
Either a team member or I will take a look at it and answer it.

## 4. Setting up your sprint
Your feature will be completed in your own branch. A branch is a way
for developers to work on a set of files without messing up the work
of other developers. When both developers are ready to combine work,
they merge the branches together. (Git's philosophy is code is like a
river. Think of your branches as branches of a river that split and
then merge back together again.) 

Say I'm working on the adding feature for a calculator. I would then create a branch called `norton-add-feature`.

I'll first show you the commands to type in and explain what each one does later.

```
git checkout master
git pull origin master
git checkout -b norton-add-feature
git push origin norton-add-feature
```

Line 1 and 2 ensures you have the most up-to-date code that everyone is working on. Line 3 actually creates your new `norton-add-feature` branch, and line 4 publishes it to the server so everyone can see your work.

If you've done everything correctly, the following command:
```
git status
```
will result in:
```
Your branch is up-to-date with 'origin/norton-add-feature'
```
Congrats! Now you can start churning out work.

## 5. Doing your sprint

As a good rule of thumb, everytime you make a small change and save your files (which should be often), it's a good place to "commit" your changes. In other words, document what you've done. It's important to make many "commits", so if you make a mistake, you can roll back to the last commmit you have. The more commits you have, the more options you have.

Here are the commands with the explanations to follow:
```
git add .
git commit -m "description of what you did"
```

Line 1 is a way to tell Git: "Hey, I did something, record it please". Line 2 is the actual commit. In the quotes, you describe to git (and your teammates) what you just did. Keep in mind that "updated file" is a useless description. Try something like "created declarations for adder method". (Descriptions should be no more than a sentence.)

## 6. Publishing your work
Once you have a sizeable amount of work done (maybe like 10 - 15 commits), it's worth "pushing" your work to the server for everyone to
see what you're doing. 

**If you have *NOT* "pushed" your work before run this command:**
```
git push -u origin norton-add-feature
```

**If you *HAVE* "pushed" your work before run this command:**
```
git push
```

## 7. Combining work

Once we have completed a feature (e.g. our adder feature), we will want to "merge" our work back in to the `master` branch. (we will turn in the `master` branch to Bladek, so make sure your code can merge!)

# Assignments

<table>
<tr>
  <td><b>Name</b></td>
  <td><b>Readme</b></td>
  <td><b>Source</b></td>
</tr>
<tr>
  <td>DateTime Inheritance</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Notes/Project1.md">Readme</a></td>
  <td><a href="https://github.com/qwergram/CS133Assignment/tree/master/CS133Assignment1">Source</a></td>
</tr>
<tr>
  <td>Quiz 2</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Notes/quiz2.md">Readme</a></td>
  <td><a href="https://github.com/qwergram/CS133Assignment/tree/master/Quiz2">Source</a></td>
</tr>
<tr>
  <td>Quiz 3</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Notes/quiz3.md">Readme</a></td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Quiz3/main.cpp">Source</a></td>
</tr>
<tr>
  <td>Circularly Doubly Linked List</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Notes/project2.md">Readme</a></td>
  <td><a href="https://github.com/qwergram/CS133Assignment/tree/master/Project2">Source</a></td>
</tr>
<tr>
  <td>Midterm Corrections</td>
  <td>Readme</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/MidTerm/midterm.cpp">Source</a></td>
</tr>
<tr>
  <td>RPN Calculator</td>
  <td><a href="https://github.com/qwergram/CS133Assignment/blob/master/Notes/project4.md">Readme</a></td>
  <td><a href="https://github.com/qwergram/CS133Assignment/tree/master/RPNCalculator">Source</a>
</tr>
</table>

# Notes
[x] = completed
- [x] [C++ Tests](https://github.com/qwergram/CS133Assignment/blob/master/Notes/Testing.md)
- [ ] [Function Pointers](https://github.com/qwergram/CS133Assignment/blob/master/Notes/FunctionAddressExample.md)
- [ ] [Virtual Inheritence](https://github.com/qwergram/CS133Assignment/blob/master/Notes/VirtualInheritance.md)
- [ ] [Casting](https://github.com/qwergram/CS133Assignment/blob/master/Notes/reinterpretcast.md)
- [x] [Iterators](https://github.com/qwergram/CS133Assignment/blob/master/Notes/Iterators.md)
- [ ] [BST](https://github.com/qwergram/CS133Assignment/blob/master/Notes/BSTLecture.md)
