# Philosophers - 42 project

<p align="center">
    <a href="https://projects.intra.42.fr/projects/42cursus-philosophers/projects_users/2935014" alt="absalhi's philosophers">
        <img src="https://user-images.githubusercontent.com/65598953/214819826-47467fd2-209e-43e1-a48a-f590ef26ef3c.png" alt="philosophers" />
    </a>
    <br />
    <a href="https://projects.intra.42.fr/projects/42cursus-philosophers/projects_users/2935014">
        <img src="https://badge42.vercel.app/api/v2/cl9iseqxd00640gl9mg4g0mxp/project/2935014" alt="absalhi's 42 philosophers Score" />
    </a>
</p>

---

<p align="center">
	<a href="https://www.onverticality.com/blog/raphael-school-of-athens" alt="School of Athens">
		<img src="https://user-images.githubusercontent.com/65598953/214820503-5997179d-152a-4aa1-91d3-7fd1f9569f93.png" width="500"/>
	</a>
	<br />
	<i><b>School of Athens</b> by Raphael</i>
</p>

## Table of Contents

- [Philosophers - 42 project](#philosophers---42-project)
  * [Usage](#usage)
  * [Description](#description)
  * [Implementation](#implementation)
    + [What is a deadlock ?](#what-is-a-deadlock-)
    + [What is a data race ?](#what-is-a-data-race-)
    + [How to check for data races ?](#how-to-check-for-data-races-)
  * [Is my project working correctly ?](#is-my-project-working-correctly-)

## Usage

```bash
$> make
$> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Description

Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger.

The [**Philosopher's Dining Problem**](https://en.wikipedia.org/wiki/Dining_philosophers_problem), originally formulated in 1965 by [Edsger Wybe Dijkstra](https://en.wikipedia.org/wiki/Edsger_W._Dijkstra), is a classic problem in computer science that illustrates the concept of deadlock and synchronization. The problem describes a scenario where a group of philosophers are seated around a round table and are each trying to eat their dinner. However, in order to eat, they must first pick up the chopsticks that are located between them and their neighbors.

## Implementation

In the C programming language, this problem can be implemented using threads and synchronization mechanisms such as semaphores or mutexes. Here's an example of how to implement the Philosopher's Dining Problem using semaphores:

1. Declare an array of mutexes, one for each chopstick.
2. Create a function for each philosopher thread that will run concurrently. Inside the function, the philosopher will first lock the mutex for the chopstick to their left, then lock the mutex for the chopstick to their right. Once both chopsticks are acquired, the philosopher can eat for a random amount of time.
3. Initialize each mutex using the `pthread_mutex_init()` function.
4. Create the philosopher threads and start them using the `pthread_create()` function.
5. Wait for all threads to complete using the `pthread_join()` function.
6. Release resources and exit the program.

Here is a sample code snippet for implementing the philosopher's dining problem using threads and mutexes _(minimal example)_:

<p align="center">
	<a href="/testing/threads_mutexes.c">
		<img src="https://user-images.githubusercontent.com/65598953/214824421-8bcb0a94-2668-453c-b816-1c28b0fc0c4f.png" width="500" />
	</a>
</p>

We used mutexes to implement the dining philosophers problem. Mutexes are a synchronization mechanism that allows us to lock and unlock resources. In the above example, we use a mutex to lock a chopstick before a philosopher can pick it up. If the chopstick is already locked, the philosopher will wait until the chopstick is unlocked before picking it up. Once the philosopher is done eating, they will unlock the chopstick so that another philosopher can pick it up.

Additionally, the `pthread_mutex_init()`, `pthread_create()`, `pthread_join()` and `pthread_mutex_destroy()` functions are used to initialize, create, wait for completion, and destroy the mutexes, respectively.

It's worth noting that the problem of deadlock can still occur if the philosophers are not implemented correctly. To avoid deadlock, philosophers must always acquire chopsticks in the same order _(e.g. left, then right)_ and handle errors correctly.

Also, in this example, the philosophers are eating infinitely, you may want to add a condition to the while loop to make sure it stops after a certain number of iterations.

As always, it's important to test this program with different inputs and different scenarios to ensure that it is working correctly and that it is not prone to deadlock or starvation.

Here is the same implementation but using forks and semaphores this time _(this is for the bonus part, it ain't that hard; give it a shot !!)_:

<p align="center">
	<a href="/testing/forks_semaphores.c">
		<img src="https://user-images.githubusercontent.com/65598953/214824148-daf738b3-9bae-4fc2-8bdb-7d0e66661f72.png" width="500" />
	</a>
</p>

In this example, the `sem_init()`, `sem_wait()`, `sem_post()`, and `sem_destroy()` functions are used to initialize, acquire, release, and destroy the semaphores, respectively. The `fork()` function is used to create child processes for each philosopher, and the `wait()` function is used to wait for all child processes to complete before exiting the program.

Just as in the mutex implementation, philosophers must always acquire forks in the same order _(e.g. left, then right)_ and handle errors correctly to avoid deadlock.

It is important to test the program with different inputs and different scenarios to ensure that it is working correctly and that it is not prone to deadlock or starvation.

Also, in this example, the philosophers are eating infinitely, you may want to add a condition to the while loop to make sure it stops after a certain number of iterations.

### What is a deadlock ?

A deadlock is a situation that occurs in a multi-threaded program when two or more threads are unable to proceed because each is waiting for one of the others to do something. Deadlocks can occur when multiple threads are trying to acquire a lock on a shared resource and each thread holds a lock that the other threads are waiting for.

A classic example of a deadlock is when two threads are each holding a lock on a resource and trying to acquire a lock on the other resource. For example, imagine two threads, **A** and **B**, are each holding a lock on resource **X** and trying to acquire a lock on resource **Y**. Thread **A** will wait indefinitely for thread **B** to release the lock on resource **Y**, and thread **B** will wait indefinitely for thread **A** to release the lock on resource **X**. This creates a deadlock, as both threads are unable to proceed.

Deadlocks can be hard to detect and reproduce, as they can occur only under certain conditions, such as when the program is run on a specific machine or when the program is run with specific inputs.

To avoid deadlock, it is important to design the program in such a way that it does not create a cycle of dependencies between threads, this can be done by :

- Acquiring locks in a consistent order
- Releasing locks as soon as possible
- Avoiding unnecessary lock acquisitions
- Using non-blocking synchronization constructs

Additionally, it's important to test the program with different inputs and different scenarios to ensure that it is not prone to deadlock.

### What is a data race ?

A data race is a situation that occurs in a multi-threaded program when two or more threads access the same memory location simultaneously and at least one of the accesses is a write operation. This can lead to unpredictable results, as the order of execution of the threads is not guaranteed.

A data race can occur when two threads access the same variable without synchronization, such as using a mutex, semaphore, or other synchronization mechanism. The problem can also occur when one thread reads a variable while another thread is writing to it.

Data races can be hard to detect, as they can lead to subtle bugs that only appear under certain conditions, such as when the program is run on a specific machine or when the program is run with specific inputs.

To avoid data races, it is important to use appropriate synchronization mechanisms such as mutex, semaphores or other lock-free algorithms that ensure that only one thread can access a shared resource at a time. Additionally, it's important to use atomic operations when accessing a shared variable, such as the atomic variables in C++ or the volatile keyword in C. But in this project, you only have the right to use mutexes/semaphores to do so.

### How to check for data races ?

There are several ways to check for data races in C:

1. **Compiler Flags:** Some compilers, such as [**GCC**](https://gcc.gnu.org/) and [**Clang**](https://clang.llvm.org/), provide flags that can be used to detect data races at runtime. For example, GCC provides the `-fsanitize=thread` flag, which enables thread-sanitizer to detect data races.

2. **Debugging Tools:** There are also various debugging tools, such as [**Valgrind**](https://valgrind.org/), that can be used to detect data races. Valgrind is a dynamic analysis tool that can detect data races, memory leaks, and other bugs.

3. **Manual Inspection:** It is also possible to manually inspect the code to check for data races by looking for shared variables that are accessed by multiple threads without proper synchronization.

4. **Thread-safe libraries:** You can also use thread-safe libraries such as [**Pthreads**](https://docs.oracle.com/cd/E19120-01/open.solaris/816-5137/tlib-1/index.html) or [**C++11 thread library**](https://en.cppreference.com/w/cpp/thread), which provides synchronization mechanisms such as mutexes, semaphores and other lock-free algorithms that can help you avoid data races.

5. **Unit tests:** You can write [unit tests](https://ieeexplore.ieee.org/abstract/document/7166265) that check for race conditions and other concurrency bugs. These tests should be run with different inputs and different scenarios to ensure that the program is working correctly and that it is not prone to data races.

It is important to note that detecting data races is not always easy, and some data races may be hard to reproduce and detect. Therefore, it is important to use multiple methods to check for data races and to thoroughly test the program under different conditions.

## Is my project working correctly ?

To check if your project is working correctly, you can test the following cases for both mandatory and bonus parts:

- Test with **1 800 200 200**, the philosopher should not eat and should die!
- Test with **5 800 200 200**, no one should die!
- Test with **5 800 200 200 7**, no one should die and the simulation should stop when all the philosophers has eaten at least 7 times each.
- Test with **4 410 200 200**, no one should die!
- Test with **4 310 200 100**, a philosopher should die!
- Test with 2 philosophers and check the different times (a death delayed by more than 10ms is unacceptable).

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fabdeljalil-salhi%2Fphilosophers&count_bg=%233DACC8&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=REPO+VIEWS&edge_flat=true)](https://hits.seeyoufarm.com)
