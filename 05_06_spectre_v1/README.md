# Spectre V1

In this tutorial, we will learn how to exploit the CPU's branch prediction, i.e. the PHT, and mount a so-called Spectre attack.
We will trick the CPU into speculatively following a branch incorrectly and, thus, to leak sensitive data.

## What do we have to do?

We provided a skeleton code that compares the string that we are are recovering using the Spectre attack with the ground-truth secret.
Therefore, almost everything is setup and we are good to go.
The simple application contains the ``access_array`` function that expects a memory location and an index as a parameter.
This function checks if the passed index is in-bounds, and if so returns the value.
Additionally, if the index check passes, an offset of the passed memory location will be loaded into the cache depending on the value of the string defined by the passed index.

The skeleton already provides a loop to mount the attack for each out-of-bounds character we want to leak.
There, the first thing we want to do is to mistrain the branch predictor, such that the CPU thinks that the condition is satisfied and, thus, execute the memory access.
We can simply do this, by executing the function multiple times with values that are in-bounds, .e.g 0.
Then, we will call the ``access_array`` function once with our out-of-bounds index.
The CPU will speculatively follow the branch in the wrong direction and perform the memory access despite the condition of the branch is not fulfilled.
This will encode the out-of-bounds value into the cache, allowing us to decode it using Flush+Reload.

Every character that we successfully recovered, we store in the ``recovered`` array at the ``recovered_index`` position, e.g. `recovered[recovered_index] = 'X'`.
Due to the way the skeleton is build, the attack will be mounted on every offset until the recovered string matches the secret.

## Example output

If we have implemented everything successfully, the output should look something like this:

    [+] Flush+Reload Threshold: (34, 116)
    TOPSECRET
    Successful.
