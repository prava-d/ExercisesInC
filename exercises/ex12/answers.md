## Answers to questions

### counter.c

2) Use the Makefile to compile `counter.c` and run it.  Draw a thread
diagram that shows the interactions of the parent thread and the children.
Is the final value of the counter correct?

The final value of the counter is correct except for a large number of children, as seen in question 3.
(** Upload thread diagram).

3) Increase the number of children, then compile and run the program again.
Do you see evidence that the threads are running concurrently?  Do any synchronization errors occur?

The threads are running concurrently, it seems, because running it produces approximately the same value each time. Synchronization errors are evident when the number of children are increased to a very large number - then the overall total is slightly off.

### counter_array.c

2) Use the Makefile to compile the program and run it.  Do any
syncronization errors occur?

Synchronization errors seem to occur - anywhere between 200 and 200,000 errors depending on the run (at least in my experience)

4) Synchronization takes some time.  Comment out the print statements
in `counter_array.c` and `counter_array_mutex.c`, then recompile and time them.

```
    time ./counter_array
    time ./counter_array_mutex
```

How much overhead does the synchronization impose?

```
	time ./counter_array

	real	0m0.076s
	user	0m0.116s
	sys		0m0.008s

```

```
	time ./counter_array_mutex

	real	0m0.192s
	user	0m0.212s
	sys		0m0.136s
```

Synchronization seems to provide significantly more overhead, as the times are all somewhat increased between counter_array and counter_array_mutex.