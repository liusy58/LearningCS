# Traces

This directory contains traces of allocate and free requests that are
used by the test harness to evaluate the student malloc packages.

## 1. Files

* `.rep` Original traces
* `-bal.rep` Balanced versions of the original traces

Note: A "balanced" trace has a matching free request for each allocate
request.

## 2. Trace file format

A trace file is an ASCII file. It begins with a 4-line header:

```
<sugg_heapsize>   /* suggested heap size (unused) */
<num_ids>         /* number of request id's */
<num_ops>         /* number of requests (operations) */
<weight>          /* weight for this trace (unused) */
```

The header is followed by `num_ops` text lines. Each line denotes either
an allocate [a], reallocate [r], or free [f] request. The `<alloc_id>`
is an integer that uniquely identifies an allocate or reallocate
request.

```
a <id> <bytes>  /* ptr_<id> = malloc(<bytes>) */
r <id> <bytes>  /* realloc(ptr_<id>, <bytes>) */
f <id>          /* free(ptr_<id>) */
```

For example, the following trace file:

```
<beginning of file>
20000
3
8
1
a 0 512
a 1 128
r 0 640
a 2 128
f 1
r 0 768
f 0
f 2
<end of file>
```

is balanced. It has a recommended heap size of 20000 bytes (ignored),
three distinct request ids (0, 1, and 2), eight different requests
(one per line), and a weight of 1 (ignored).
