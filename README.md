# NBody

Implementation in C of the Barnes-Hut solution to the N-Body problem.

Time comparison in graphe.pdf

Result example as a gif in anim.gif

Example to run the program during 100s with 0.1s between each physics update.
First compile:
```
make all
```
Then run:

`./nbodysimul file galaxy3.txt bht 100 0.1 gif` From the galaxy3.txt file

`./nbodysimul random 5000 bht 100 0.1 gif` Random with 5k particles

`./nbodysimul random 1000 naive 100 0.1 gif` Random with 1K particles and brute force
