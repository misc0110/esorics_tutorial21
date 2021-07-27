# Character Encoding Covert Channel

In this tutorial, we learn how to send characters from one application to a different application through the cache.
 
## What do we have to do?

We provide a skeleton code for the sender and the receiver. 
The sender lets the user input characters which should be sent to the receiver by accessing a shared memory page corresponding to the entered character. 
The receiver should recover the sent character by iterating over the shared memory pages and checking which page is cached (using Flush+Reload). 
 
## Which additional functions are available?

To reudce the implementation effort for this tutorial, we extended the "cacheutils.h" with a few functions:

  * `calibrate_flush_reload`: Builds the histogram from the last exercise and calculates the threshold.
  * `flush_reload`: Returns the access time to a given address and flushes the address afterwards.

## Example output

If you have implemented everything successfully, the output should look something like this:

Sender
```
Enter character to send: X           
```

Receiver
```
Cache hit: 128
X
```
