# Signal Handler

In this tutorial, we learn how to use a signal handler to continue program execution despite faulting memory accesses.

## What do we have to do?

We provided a skeleton code which accesses valid and invalid addresses in virtual memory. 
You have to setup a signal handler, which is called when a memory access faults. 
To continue program execution, you have to first save the program state (hint: `setjmp`) and restore the state in the signal handler (hint: `longjmp`). 

## Which additional functions are available?

Useful functions for this tutorial are:

  * `signal`: Registers a signal handler for a given signal (e.g., SIGSEGV)
  * `setjmp`: Saves various information about the caller, such as stack pointer and instruction pointer. 
  * `longjmp`: Restores the information stored by `setjmp`. 

## Example output

If you have implemented everything successfully, the output should look something like this:


    Accessible: &main:  1
    Accessible: NULL:   0
    Accessible: Kernel: 0

