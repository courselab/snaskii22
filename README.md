# Snaskii

## Readme Available Languages

- ENG version available [here](#eng-version).
- Versão PT-BR disponível [aqui](#pt-br).

# ENG version
## Introduction
Snaskii  is a very simple ASCII snake game tributed to the classic
arcades of the 80s. It was meant to be developed as a collaborative
programming exercise in a course on Open Source Systems taught to
undergraduate CS students.

## Quick start
 If you have obtained the project source from the __version control repository__,

 execute the script 

 ```
 $ ./bootstrap.sh
 ```

to boostrap the build configuration script `configure`. To that end, you'll 
need to have GNU Build System (Autotools) installed. In debian/ubuntu based 
platforms,  you may install required software with

```
$ sudo apt install automake autoconf libtool
```

On the other hand, if you have obtained the software form a __distribution 
repository__, usually as a tarball, you should already have the  script `configure`.

Either way, locate the file in the root of source directory and execute it

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



# PT-BR
## Introdução
Snaskii é um jogo de cobra ASCII muito simples, uma homenagem ao clássico
fliperamas dos anos 80. Foi concebido para ser desenvolvido como um exercício de colaboração
de programação no curso sobre Sistemas de Código Aberto lecionado a
alunos de graduação em Ciências de Computação.


## Começo rápido
Se você obteve a fonte do projeto do __version control repository__,
execute o scrpit a seguir:

 ```
 $ ./bootstrap.sh
 ```

para impulsionar o script de configuração de compilação `configure`. Para isso, você
precisa ter GNU Build System (Autotools) instalado. Plataformas baseadas em debian/ubuntu, 
você pode instalar os softwares necessários com:

```
$ sudo apt install automake autoconf libtool
```

Por outro lado, se você obteu o software de __distribution repository__, geralmente como tarball,
você já deve ter o script `configure`.

De qualquer forma, encontre o arquivo na pasta raíz do diretório fonte e o execute:

```
 $ ./configure
```

Este script deve realizar uma série de testes para coletar dados sobre a plataforma build. Se surgirem avisos sobre a falta de alguns softwares, instale-os conforme necessário.

Por exemplo, você precisará de `libncurses`, que no debian/ubuntu pode ser
instalado com:

```
sudo apt install libncurses5-dev
```

O suporte para thread POSIX também é necessário.

Por fim, construa o software e instale-o com:

```
 $ make
 $ make install
```

Isso deve instalar o programa no caminho do sistema. Normalmente os arquivos binários
serão colocados em `/usr/bin`, e os arquivos de dados em `/usr/share`. Privilégios de administrador (sudo) são necessários para escrever nestes locais.

Opcionalmente, se desejar instalar o software em um local diferente,
por exemplo, em `/tmp/foo`, execute:

```
 $ ./configure --prefix=/tmp/foo
 $ make
 $ make install
```

Isso deve instalar o software localmente, neste caso em `/tmp/foo/bin`
e os arquivos de dados em `/tmp/share`.

Para obter instruções mais detalhadas, consulte o arquivo `INSTALL`


## EXECUÇÃO
```
 Usage:  snaski [options]

         Options
         
	 -h              Displays this information message
	 -d <path>       Selects custom data path
```

## O Jogo
 
O jogo se passa em uma área retangular onde uma cobra continuamente
se move em uma das quatro direções: esquerda, direita, para cima e para baixo --- ela nunca
para de se mover. Conforme a cobra se move ela perde energia e, se toda sua energia se esgotar, a
cobra morre. Para recuperar energia, a cobra precisa comer pedaços de comida que
são constantemente substituídos em posições aleatórias.

Tenha cuidado, no entanto. As bordas da arena são eletrificadas e matariam a cobrinha se forem tocadas. Além disso, lembre-se que a cobra é venenosa e também morreria se
ela se morder acidentalmente, ou seja, se a cabeça da cobra cruzar seu próprio corpo (sim,
isso é estranho para cobras, mas esta é uma Tron Snake).

A pontuação do jogo é definida pela contagem de blocos comidos até que o jogo termine.

### Controles:
	WASD controlam a cobrinha
	+ diminui a velocidade do jogo 
	- aumenta a velocidade do jogo 
	q finaliza o jogo
	r recomeça o jogo


## Contribua para este projeto
O jogo está incompleto e completar a sua implementação consiste no
exercício de programação que você está convidado a realizar.

Se você aceitar o desafio, por favor, __faça__ a leitura do arquivo
```
docs/CONTRIBUTING.md
```
que contem mais informações importantes!
