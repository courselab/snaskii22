# Snaskii

Snaskii  is a very simple ASCII snake game tributed to the classic
arcades of the 80s. It was meant to be developed as a collaborative
programming exercise in a course on Open Source Systems taught to
undergraduate CS students.




## Quick start

 If you have nix installed, you can just:

 ```bash
 $ nix run github:courselab/snaskii22
 ```

 If you have obtained the project source from the __version control repository__,

 execute the script 

 ```
 $ ./bootstrap.sh
 ```

to boostrap the build configuration script `configure`. To that end, you'll 
need to have GNU Build System (Autotools) installed. In debian/ubuntu based 
platforms,  you may install the required software with

```
$ sudo apt install automake autoconf libtool
```

On the other hand, if you have obtained the software from a __distribution 
repository__, usually as a tarball, you should already have the script `configure`.

Either way, locate the file in the root of the source directory and execute it

```
 $ ./configure
```

This script shall perform a series of tests to collect data about the build 
platform. If it complains about missing pieces of software, install them 
as needed.

For instance, you'll need `libncurses`, which in debian/ubuntu may be
installed with

```
sudo apt install libncurses5-dev
```

Support for POSIX thread is also required.

Finally, build the software and install it with

```
 $ make
 $ make install
```

This should install the program under the system path. Usually, the binary
will be placed in `/usr/bin`, and data files in `/usr/share`. Administrative
privileges (sudo) are required to write in those locations.



Optionally, if you wish to install the software under a different location,
 for instance, in `/tmp/foo`, execute

```
 $ ./configure --prefix=/tmp/foo
 $ make
 $ make install
```

This shall install the software locally, in this case in `/tmp/foo/bin`
and the data files in `/tmp/share`. 

 For more detailed instructions, please, refer to the file `INSTALL`

## EXECUTION

```
 Usage:  snaskii [options]

         Options
         
	 -h              Displays this information message
	 -d <path>       Selects custom data path
```

 ## The game
 
The game takes place in a rectangular arena where a snake continuously
moves in one of four directions: left, right, up, and down --- it never 
stops. As the snake moves, it loses energy and if all of it is exhausted, the 
snake dies. To recover energy, the snake needs to eat pieces of food that are 
constantly replaced at random positions.

Be careful, though. The arena borders are electrified and would kill the snake 
if touched. Moreover, mind that the snake is poisonous and it would also die if 
it accidentally bites itself, i.e. if the snake's head crosses its own body (yes, 
this is weird for snakes, but this is a Tron Snake).

The game score is the count of eaten blocks until the game is over.

 ### Controls:
	WASD to control the snake
	+ decreases the game speed
	- increases the game speed 
	space skips animation intro
	q quits
	r at anytime to restart the game
	space skips the introduction

## Contribute to this project

The game is incomplete and completing its implementation consists of the
programming exercise you are invited to carry out.

If you accept the challenge please, __do__ read the file

```
docs/CONTRIBUTING.md
```

which contains important information.

