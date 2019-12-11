# NBody

Implementation in C of the Barnes-Hut solution to the N-Body problem.

Time comparison in graphe.pdf

Result example as a gif in anim.gif

Example to run the program during 100s with 0.1s between each physics update:
```
make all
./nbodysimul file galaxy3.txt bht 100 0.1 # From the galaxy3.txt file
./nbodysimul random 10000 bht 100 0.1 # Random with 5k particles
./nbodysimul file galaxy3.txt naive 100 0.1 # Random with 1K particles and brute force
```