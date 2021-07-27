# ZombieLoad

In this tutorial, we will learn how to mount the ZombieLoad attack to leak data from different buffers of the CPU, e.g. the line-fill buffer.

## What do we have to do?

This tutorial comes with two applications: The ``victim`` application that constantly loads secret data and the ``zombieload`` application that mounts the attack to leak said data.

First, we get a valid page and further obtain the identity mapped address of it.
To mount the attack, we first flush the user accessible address and then try to read from the identity address (similar as with Meltdown).
We encode the read value into the cache and catch the fault.
Then, we decode the value from the cache and print out the leaked secret.

## Example output

    taskset -c 3 ./victim A                                     
    Loading secret value 'A'...

If we have implemented everything successfully, the output should look something like this:

    taskset -c 7 ./zombieload

    A: (  64) ############################################################
    B: (   0) 
    C: (   0) 
    D: (   0) 
    E: (   0) 
    F: (   0) 
    G: (   0) 
    H: (   0) 
    I: (   0) 
    J: (   0) 
    K: (   0) 
    L: (   0) 
    M: (   0) 
    N: (   0) 
    O: (   0) 
    P: (   0) 
    Q: (   0) 
    R: (   0) 
    S: (   0) 
    T: (   0) 
    U: (   1) 
    V: (   0) 
    W: (   0) 
    X: (   0) 
    Y: (   0) 
    Z: (   0) 
