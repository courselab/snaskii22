# Snaskii

Snaskii  is a very simple ASCII snake game tributed to the classic
arcades of the 80s. It was meant to be developed as a collaborative
programming exercise in a course on Open Source Systems taught to
undergraduate CS students.

## Quick start

### Dependencies
Before running the scripts, make sure you have the necessary dependencies installed.
- GNU Build System (Autotools)
- libncurses
- Support for POSIX thread

#### Debian/Ubuntu
```
$ sudo apt install automake autoconf libtool libncurses5-dev
```
#### Arch
```
$ sudo pacman -S automake autoconf libtool ncurses ncurses5-compat-libs
```
 
### Installing
 If you have obtained the project source from the __version control repository__,

 execute the script 

 ```
 $ ./bootstrap.sh
 ```

to boostrap the build configuration script `configure`. 

On the other hand, if you have obtained the software form a __distribution 
repository__, usually as a tarball, you should already have the  script `configure`.

Either way, locate the file in the root of source directory and execute it

```
 $ ./configure
```

This script shall perform a series of tests to collect data about the build 
platform. If it complains about missing pieces of software, install them 
as needed.

Finally, build the software and install it with

```
 $ make
 $ make install
```

This should install the program under the system path. Usually the binary
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

 For more detailed instructions, please, refer to file `INSTALL`

## EXECUTION

```
 Usage:  snaski [options]

         Options
         
	 -h              Displays this information message
	 -d <path>       Selects custom data path
```

 ## The game
 
 The game takes place on a rectangular areana where a snake continuously
 move in one of the four directions: left, right, up and down --- it never 
 stops. As the snake moves it looses energy and if all of it is exausted, the
 snake dies. To recover energy, the snake needs to eat pieces of food which
 are constantly replaced at random positions. 

Be careful, though. The arena borders are electrified and would kill the snake
if touched. Morover, mind that the snake is poisonous and it would also die if 
it accidently bites itself, i.e. if the snake's head crosses its own body (yes, 
this is weird for snakes, but this is a Tron Snake).

The game score is the count of eaten blocks until the game is over.

 ### Controls:
	WASD to control the snake
	+ decreases the game speed
	- increases the game speed 
	q quits
	r at anytime to restart the game

## Contribute to this project

The game is incomplete and completing its implementation consists in the
programming exercise you are invited to carry out.

If you accept the challenge please, __do__ read the file

```
docs/CONTRIBUTING.md
```

which contains important information.

