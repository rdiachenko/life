# Life

The project represents different variations of [Conway's Game of Life](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

## C++ Life

Youtube video is [here](https://youtu.be/kSKe7BtLS28) and [here (with interesting effect](https://youtu.be/Yq74FPuz4P0)

![](https://raw.githubusercontent.com/rdiachenko/life/master/cpp-life/screenshots/cpp-life2.png)

![](https://raw.githubusercontent.com/rdiachenko/life/master/cpp-life/screenshots/cpp-life.png)

### How to run

```
# install SDL and its dependencies
$ sudo yum install SDL*

$ cd cpp-life
$ make

# see help
$ ./life -h
Usage: 
<MOUSE_LEFT_CLICK> - turn cell on
<MOUSE_RIGHT_CLICK> - turn cell off
<SPACE> - pause/resume
<ESC> - clear field

$ ./life
```
To play with the game parameters go to [cpp-life/Constants.h](https://github.com/rdiachenko/life/blob/master/cpp-life/Constants.h).

## Scala-Life

![](https://raw.githubusercontent.com/rdiachenko/life/master/scala-life/screenshots/scala-life.png)

### How to run

```
# install sbt and its dependencies
$ sudo yum install sbt

# compile and run the Game of Life
$ cd scala-life
$ sbt clean compile run
```

