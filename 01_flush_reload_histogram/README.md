# Cache Histogram

In this tutorial, we will learn how to observe different memory access times and, thus, if data is in the cache or has to be loaded from the main memory.

## What do we have to do?

We provided a skeleton code to print out and save a measured histogram into a file.
Therefore, everything is setup already and we only have to implement the neseccary functions that do the measurements:

  * ``void measure_access_time(void* address)``: The function that measures how long it takes to load the given address.
      * Parameter:
        * ``void* address``: The address that we access
      * Return:
        * Measured access time (size_t)
  * ``void measure_hits(void* address, size_t* histogram, size_t number_of_measurements)``: The function that performs ``n`` measurements if the data is cached.
      * Parameter:
        * ``void* address``: The address that we access
        * ``size_t* histogram``: The histogram in which we save the results
        * ``size_t number_of_measurements``: How often we perform the measurement
      * Return:
        * None
  * ``void measure_misses(void* address, size_t* histogram, size_t number_of_measurements)``: The function that performs ``n`` if the data is not in the cache.
      * Parameter:
        * ``void* address``: The address that we access
        * ``size_t* histogram``: The histogram in which we save the results
        * ``size_t number_of_measurements``: How often we perform the measurement
      * Return:
        * None

## Which additional functions are available?

To ease the implementation effort, we have the following functions available and ready to use:

  * ``uint64_t rdtsc(void)``: Returns the cycle counter
  * ``void flush(void* p)``: Flushes the address ``p`` from the cache.
  * ``void maccess(void* p)``: Performs a memory access to ``p`` with no additional effect.


## Example output

If we have implemented everything successfully, the output should look something like this:

       0:          0          0
       5:          0          0
      10:          0          0
      15:          0          0
      20:          0          0
      25:          0          0
      30:          0          0
      35:          0          0
      40:          0          0
      45:      13360          0
      50:      36548          0
      55:         67          0
      60:          0          0
      65:          0          0
      70:          0          0
      75:          0          0
      80:          0          0
      85:          0          0
      90:          1          0
      95:          0          0
     100:          0          0
     105:          0          0
     110:          0          0
     115:          0          0
     120:          0          0
     125:          0          0
     130:          4          0
     135:          2          0
     140:          0          0
     145:          1          0
     150:          0          0
     155:          0          0
     160:          0          0
     165:          0          0
     170:          0          0
     175:          0          0
     180:          0          0
     185:          1          1
     190:          1          1
     195:          0          0
     200:          0         25
     205:          2       4455
     210:          0       3854
     215:          0       1885
     220:          1       2483
     225:          1      23939
     230:          0       5956
     235:          0       1039
     240:          1        511
     245:          0        733
     250:          1        636
     255:          0        300
     260:          0        320
     265:          0        170
     270:          0        251
     275:          0        164
     280:          0        230
     285:          0        145
     290:          0        161
     295:          0        122
     300:          0        169
     305:          0        115
     310:          0        104
     315:          0         61
     320:          0        131
     325:          0         84
     330:          0        110
     335:          0         51
     340:          0         63
     345:          0         26
     350:          0         41
     355:          0         24
     360:          0         25
     365:          0         24
     370:          0         32
     375:          0         21
     380:          0         29
     385:          0         14
     390:          0         19
     395:          0          9
     400:          0         19
     405:          0          7
     410:          0         11
     415:          0         11
     420:          0          8
     425:          0          6
     430:          0          9
     435:          0          6
     440:          0         10
     445:          0          5
     450:          0         13
     455:          0          3
     460:          0         11
     465:          0          6
     470:          0         12
     475:          0          4
     480:          0          8
     485:          0          6
     490:          0          7
     495:          9       1305

### Plotting the output

In addition, we can use the ``plot.py`` file to plot the histogram in a more visual way:

    python plot.py

