# Queue & Stack in C

Two small, interactive command-line programs written in C that implement the **Queue** and **Stack** data structures using doubly linked lists.

## Features

- **Queue (FIFO)**: enqueue, dequeue and print
- **Stack (LIFO)**: push, pop, peek and print
- Dynamic memory allocation with `malloc`/`free`
- Allocation failure checks
- Input validation: non-numeric input is rejected and the input buffer is cleared
- Clean-up of all allocated memory on exit

## Project Structure

```
.
├── queue.c      # Queue application (source)
├── queue.exe    # Queue application (prebuilt, Windows)
├── stack.c      # Stack application (source)
├── stack.exe    # Stack application (prebuilt, Windows)
└── README.md
```

## Requirements

- A C compiler such as `gcc` or `clang` (C99 or later, for `<stdbool.h>`)

## Build

```bash
gcc -Wall -Wextra -std=c99 -o queue queue.c
gcc -Wall -Wextra -std=c99 -o stack stack.c
```

## Run

**Windows:** prebuilt executables are included. Double-click them, or run from a terminal:

```
queue.exe
stack.exe
```

**Linux / macOS:** build from source (see above), then run:

```bash
./queue
./stack
```

## Usage

### Queue

```
---------- Queue Application ----------
1) Enqueue
2) Dequeue
3) Print Queue
4) Exit
Enter your choice:
```

| Option | Description |
| ------ | ----------- |
| 1 | Add a number to the **back** of the queue |
| 2 | Remove and show the number at the **front** of the queue |
| 3 | Print the queue from front to back |
| 4 | Free all memory and exit |

### Stack

```
---------- Stack Application ----------
1) Push
2) Pop
3) Peek
4) Print Stack
5) Exit
Enter your choice:
```

| Option | Description |
| ------ | ----------- |
| 1 | Push a number onto the **top** of the stack |
| 2 | Remove and show the number on top |
| 3 | Show the top number without removing it |
| 4 | Print the stack from top to bottom |
| 5 | Free all memory and exit |

### Example Session (Queue)

```
Enter your choice: 1
Enter a number: 10
Enter your choice: 1
Enter a number: 20
Enter your choice: 3
Queue: 10 20
Enter your choice: 2
Dequeued value: 10
```

## How It Works

Both structures are built from a doubly linked `Node`:

```c
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};
```

- **Queue** keeps `start` and `end` pointers, so enqueue and dequeue are both **O(1)**.
- **Stack** keeps a single `top` pointer, so push, pop and peek are all **O(1)**.
