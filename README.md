# Operating_Systems_Programming_Problems

This repository contains five programming assignments completed as part of the **Operating Systems (ECS 408/608)** course taught by **Dr. Sukarn Agarwal** at **IISER Bhopal**. The assignments cover fundamental operating system concepts through practical programming exercises in C on a Linux environment. Topics include Linux system utilities, process management, inter-process communication (IPC), multithreading, and process synchronization.

Each assignment includes source code, reports, outputs, and supporting files that demonstrate the implementation of key operating system concepts.

---

## Assignments

### Assignment 1 - Introduction to Linux Tools

This assignment focuses on Linux commands, development tools, and system resource analysis.

**Topics Covered**
- Linux command-line utilities
- CPU utilization analysis
- Memory allocation and access patterns
- Disk I/O operations
- Shell scripting and file management

**Programs Implemented**
- CPU-intensive process generation
- Memory allocation experiments
- Disk read operation analysis
- Automated file generation using shell scripts

---

### Assignment 2 - Process Operations

This assignment explores process creation and management using Linux system calls.

**Topics Covered**
- Process creation using `fork()`
- Parent-child process relationships
- Orphan processes
- Process hierarchy and process trees
- Concurrent process execution

**Programs Implemented**
- Parent-child process creation
- Merge sort and quick sort using multiple processes
- Orphan process demonstration with factorial and Fibonacci computations
- Process tree generation and visualization

---

### Assignment 3 - Inter-Process Communication (IPC)

This assignment demonstrates communication between processes using shared memory.

**Topics Covered**
- Shared memory management
- Producer-consumer communication
- Data sharing between processes
- Multi-consumer processing

**Programs Implemented**
- Shared memory producer-consumer system for integer and string communication
- Random number generation and summation using shared memory
- Multiple consumer processes performing factorial computations on shared data

---

### Assignment 4 - Multithreading

This assignment introduces concurrent programming using POSIX Threads (Pthreads).

**Topics Covered**
- Thread creation and management
- Concurrent execution
- Thread synchronization
- Thread cancellation

**Programs Implemented**
- Thread-based addition of two numbers
- File creation and writing using multiple threads
- Parallel processing of a 10,000-element array
- Thread cancellation and termination

---

### Assignment 5 - Process Synchronization

This assignment focuses on synchronization mechanisms and critical section problems.

**Topics Covered**
- Race conditions
- Critical section problem
- Semaphores
- Shared memory synchronization
- Producer-consumer synchronization

**Programs Implemented**
- Race condition simulation using shared memory
- Semaphore-based mutual exclusion
- Multi-producer multi-consumer bounded buffer implementation
- Circular buffer synchronization using shared memory and semaphores

---

## Technologies Used

- C Programming
- Linux Operating System
- GCC Compiler
- POSIX Threads (Pthreads)
- System V Shared Memory
- System V Semaphores
- Linux System Calls
- Shell Scripting

---

## Learning Outcomes

Through these assignments, the following operating system concepts were explored and implemented:

- Linux command-line tools and utilities
- Process creation and management
- Inter-process communication (IPC)
- Shared memory programming
- Multithreaded programming
- Race condition analysis
- Critical section problem solutions
- Semaphore-based synchronization
- Producer-consumer synchronization
- Concurrent and parallel execution models
