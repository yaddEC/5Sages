# Dinner of the Sages

## Introduction


A lot of famous thimkers and philosophers such as Socrates or Plato gathered around a table to have a lunch and share their thought. However, there is only one chopstick per thinker, and you need two in order to eat.

### Objective

The goal was to create a program that emulate the sages states and hunger, and to make them choose their chopstick by using multithreading.



## Overview
![png](img/CAPTURE.png)

## States
-----------
Different states of the sages: <br>
- `S` means they are thinking for 1 to 3 seconds
- `M`  means they are eating for 1 to 3 seconds
- `C` means that the sage has no access to two chopstick, and is waiting to eat
- `F` means that the sage finished eating
- `1` means that the chopstick is available
- `0` means that the chopstick is not available

## Behavior
![png](img/how_sage_choose.png)

A sage can only take the chopstick in front of him, or next to him.

![png](img/how_sage_choose3.png)

The last sage can only take the first chopstick, or the one in front of him

![png](img/how_sage_choose2.png)

The color of the sages changes according to their hunger. If they are white, it means they are full.
A day passes once every sage is full, and the program is over once 7 days have passed.

![png](img/CAPTURE2.png)

You can change the number of sages in the program, with the minimum and maximum random time too.
