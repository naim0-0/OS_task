# Operating Systems Lab C Programs

All example data is hardcoded. Change the arrays or constants near the top of
each source file to test a different case.

## CPU scheduling

- `fcfs.c`
- `sjf.c`
- `priority_non_preemptive.c`
- `srtf.c`
- `priority_preemptive.c`
- `round_robin.c`
- `rms.c` - Rate Monotonic Scheduling for periodic real-time tasks
- `edf.c` - Earliest Deadline First scheduling for periodic real-time tasks

Each scheduling program prints its execution sequence and completion order.
RMS and EDF simulate one hyperperiod and report any missed deadlines.

Compile example:

```bash
cc -Wall -Wextra fcfs.c -o fcfs
./fcfs
```

## Page replacement

- `fifo_page.c`
- `lru_page.c`
- `optimal_page.c`

## Processes, IPC, signals and threads

- `fork_exec.c`
- `pipe_ipc.c`
- `shared_memory.c`
- `sigint_thread.c`
- `dynamic_array_summation_via_workload_partitioning.c` - user-defined array and thread count with balanced workload partitioning

Thread example:

```bash
cc -Wall -Wextra dynamic_array_summation_via_workload_partitioning.c -o dynamic_array_summation_via_workload_partitioning -pthread
./dynamic_array_summation_via_workload_partitioning
```

## Synchronization and deadlock

- `philosophers_simulation.c` - hardcoded event simulation
- `dining_philosophers.c` - input-based simulation without threads
- `sleeping_ta.c`
- `pizza.c`
- `readers_writers.c`
- `jurassic_park.c`
- `bankers.c`

The synchronization examples above are simple input-driven simulations. They
use integer state variables to demonstrate semaphore rules without pthreads or
platform-specific semaphore functions.

`sigint_thread.c` keeps running until you press `Ctrl+C`.
