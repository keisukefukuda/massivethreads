# MassiveThreads - a Lightweight Thread Library for High Productivity Languages

# API reference

 * http://www.eidos.ic.i.u-tokyo.ac.jp/massivethreads/massivethreads/docs/reference/

# System Requirements

Massivethreads is mainly developed and tested on the following environment:

CPU              : x86_64
Operating system : Linux (>=2.6)
C compiler       : GCC (>=4.4.1)

It can also work on x86, SPARC64IXfx, and XeonPhi, but not tested well.

# How to compile

MassiveThreads can be compiled and installed like many other UNIX programs using the following 3-steps:

$ export PREFIX=[directory to install]
$ ./configure --prefix=$PREFIX
$ make
$ make install

More details about system requirements and installation can be found at docs/install.txt .

# How to use

MassiveThreads provides 3 APIs to use, native intefrace, pthread-compatible interface, and TBB-like interface.

## Native interface

 Native interface provide full access to MassiveThreads functionalities.
To use native interface, please include myth.h and specify include path, library path, and shared library like this:

```
$ gcc -o foo foo.c -I${PREFIX}/include -L${PREFIX}/lib -lmyth (or -lmyth-native)
```

libmyth.so provides both native and pthread-compatible interface. so If you want to use OS-level pthreads together with MassiveThreads, please use libmyth-native.so, that does not export pthread-compatible functions.

When using libmyth.so, initialization and termination by myth_init() and myth_fini() are not required, because it is automatically done for pthread-compatibility.

In using libmyth-native.so, they are required. You can control the number of worker threads and default stack size from application using myth_init_withparam() instead of myth_init().

## Pthread-compatible interface

Pthread-compatible interface provide the same API with pthreads at binary level.
To use this interface, please write your program as using pthreads, and compile with libmyth-compat.so or libmyth.so(if you want to use native interface at the same time).

Using environmental variables such as LD_PRELOAD, existing binaries using pthreads can be executed on MassiveThreads like this:

```
$ LD_PRELOAD=${PREFIX}/lib/libmyth.so ./a.out
```

Caution: Executing programs that depend on unsupported pthreads feature (preemption, signal, thread-local storage[__thread], etc...) is not guaranteed. Calling unimplemented functions may also lead to unexpected behavior. To confirm implemented functions, see myth_if_pthread.c .

## TBB-like interface

 TBB-like interface provides an API compatible with task_group of Intel Threading Building Block.
For more information, please see docs/mtbb_api.txt .

# Runtime configuration

## Setting the number of worker threads
MassiveThreads creates worker thraeds based on the process affinity. Thus you can control the number of worker threads and CPU cores used by 'taskset' command.
Environmental variable MYTH_WORKER_NUM can also be used to change the number of worker threads (= # of CPU cores used).
By default, MassiveThreads uses all the CPU cores in the machine.

## Setting the default stack size
Setting environmental variable MYTH_DEF_STKSIZE (in bytes), you can change the default stack size. By default, MassiveThreads uses 16KB as a default stack size.

# Contact

If you have any question, please ask the following address.

   massivethreads-github@eidos.ic.i.u-tokyo.ac.jp

# License

MassiveThreads is distributed under 2-clause BSD license. See COPYRIGHT for details.

# About API names

"myth" is the initial codename of MassiveThreads and no more special meaning than it.

