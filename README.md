# Get Next Line

## Table of Contents
- [Description](#description)
- [Project Overview](#project-overview)
- [Function Prototype](#function-prototype)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Strategy](#implementation-strategy)
- [Bonus Part](#bonus-part)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Common Challenges](#common-challenges)
- [Resources](#resources)

## Description

**Get Next Line** is a crucial project in the 42 School curriculum that challenges students to create a function that reads a file line by line. This project introduces advanced concepts in C programming including static variables, dynamic memory allocation, buffer management, and file descriptor handling.

The function must be able to read from any file descriptor (files, standard input, network connections, etc.) one line at a time, regardless of the buffer size used for reading.

### Learning Objectives
- Understanding static variables and their persistence
- Dynamic memory allocation and management
- Buffer handling and optimization
- File descriptor operations
- Efficient string manipulation
- Edge case handling (empty lines, no newlines, large files)

All code must follow the **42 Norm** coding standard.

## Project Overview

The goal is to create a function that:
- Reads from a file descriptor one line at a time
- Returns each complete line including the terminating `\n` (except for the last line if it doesn't end with `\n`)
- Uses a configurable buffer size (defined at compile time)
- Handles multiple file descriptors simultaneously (bonus)
- Manages memory efficiently without leaks

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- **Success**: A string containing the next line (including `\n` if present)
- **End of file**: `NULL`
- **Error**: `NULL`

## Requirements

### Mandatory Part
- Function must read from a file descriptor and return one line at a time
- Repeated calls should return successive lines
- Buffer size is defined by `BUFFER_SIZE` during compilation
- Function should work with different buffer sizes (1, 42, 9999, etc.)
- Must handle files with or without final newline
- Must not lose data between function calls

### Technical Constraints
- Only one static variable allowed
- Memory leaks are forbidden
- Undefined behavior if file changes between calls
- Function should work with both files and standard input

## Installation

```bash
# Clone the repository
git clone # Get Next Line

## Table of Contents
- [Description](#description)
- [Project Overview](#project-overview)
- [Function Prototype](#function-prototype)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Strategy](#implementation-strategy)
- [Bonus Part](#bonus-part)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [Testing](#testing)
- [Common Challenges](#common-challenges)
- [Resources](#resources)

## Description

**Get Next Line** is a crucial project in the 42 School curriculum that challenges students to create a function that reads a file line by line. This project introduces advanced concepts in C programming including static variables, dynamic memory allocation, buffer management, and file descriptor handling.

The function must be able to read from any file descriptor (files, standard input, network connections, etc.) one line at a time, regardless of the buffer size used for reading.

### Learning Objectives
- Understanding static variables and their persistence
- Dynamic memory allocation and management
- Buffer handling and optimization
- File descriptor operations
- Efficient string manipulation
- Edge case handling (empty lines, no newlines, large files)

All code must follow the **42 Norm** coding standard.

## Project Overview

The goal is to create a function that:
- Reads from a file descriptor one line at a time
- Returns each complete line including the terminating `\n` (except for the last line if it doesn't end with `\n`)
- Uses a configurable buffer size (defined at compile time)
- Handles multiple file descriptors simultaneously (bonus)
- Manages memory efficiently without leaks

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: The file descriptor to read from

### Return Value
- **Success**: A string containing the next line (including `\n` if present)
- **End of file**: `NULL`
- **Error**: `NULL`

## Requirements

### Mandatory Part
- Function must read from a file descriptor and return one line at a time
- Repeated calls should return successive lines
- Buffer size is defined by `BUFFER_SIZE` during compilation
- Function should work with different buffer sizes (1, 42, 9999, etc.)
- Must handle files with or without final newline
- Must not lose data between function calls

### Technical Constraints
- Only one static variable allowed
- Memory leaks are forbidden
- Undefined behavior if file changes between calls
- Function should work with both files and standard input

## Installation

```bash
# Clone the repository
git clone https://github.com/Selmand42/Get-Next-Line
cd get-next-line

# Compile with your program (no Makefile required)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Or for bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

## Usage

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    printf("Enter lines (Ctrl+D to end):\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You entered: %s", line);
        free(line);
    }

    return (0);
}
```

### Compilation Examples

```bash
# Small buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c

# Standard buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Large buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
```

## Implementation Strategy

### Core Algorithm

1. **Read into buffer**: Use `read()` to fill buffer with `BUFFER_SIZE` bytes
2. **Find newline**: Search for `\n` in the accumulated data
3. **Extract line**: Return everything up to and including `\n`
4. **Save remainder**: Store remaining data in static variable for next call
5. **Repeat**: Continue until end of file

### Key Components

#### Static Variable Management
```c
static char *remainder = NULL; // Persistent between function calls
```

#### Buffer Reading
```c
char buffer[BUFFER_SIZE + 1];
int bytes_read = read(fd, buffer, BUFFER_SIZE);
```

#### String Joining
```c
remainder = ft_strjoin(remainder, buffer); // Concatenate with existing data
```

#### Line Extraction
```c
char *line = extract_line(remainder); // Get line up to \n
remainder = update_remainder(remainder); // Keep what's after \n
```

### Memory Management Pattern

1. **Allocate**: Create new strings as needed
2. **Free old**: Always free previous static content before updating
3. **Update static**: Store remaining content for next call
4. **Return line**: Give caller ownership of line (must free)

## Bonus Part

The bonus part extends the function to handle **multiple file descriptors simultaneously**.

### Bonus Features
- Can read from multiple files at the same time
- Each file descriptor maintains its own reading position
- Switching between file descriptors doesn't lose data

### Implementation Difference
```c
// Bonus uses array or linked list of static variables
static char *remainder[MAX_FD]; // Array approach
// or
static t_list *fd_list; // Linked list approach
```

### Bonus Usage Example
```c
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    // Read alternately from both files
    line = get_next_line(fd1); // First line from file1
    printf("File1: %s", line);
    free(line);

    line = get_next_line(fd2); // First line from file2
    printf("File2: %s", line);
    free(line);

    line = get_next_line(fd1); // Second line from file1
    printf("File1: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

## Examples

### Example 1: Basic File Reading

```c
// test.txt content:
// Hello World
// This is line 2
// Final line

#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    int line_count = 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", line_count++, line);
        free(line);
    }
    close(fd);
    return (0);
}

// Output:
// Line 1: Hello World
// Line 2: This is line 2
// Line 3: Final line
```

### Example 2: Edge Cases

```c
// empty.txt: (empty file)
// no_newline.txt: "No newline at end"
// only_newlines.txt: "\n\n\n"

int main(void)
{
    test_file("empty.txt");
    test_file("no_newline.txt");
    test_file("only_newlines.txt");
    return (0);
}

void test_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;

    printf("Testing %s:\n", filename);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("'%s'\n", line);
        free(line);
    }
    close(fd);
    printf("---\n");
}
```

## Project Structure

Based on the [repository structure](https://github.com/Selmand42/Get-Next-Line):

```
.
├── get_next_line.c           # Main function implementation
├── get_next_line.h           # Header file with prototypes
├── get_next_line_utils.c     # Helper functions
├── get_next_line_bonus.c     # Bonus implementation (multiple FDs)
├── get_next_line_bonus.h     # Bonus header file
├── get_next_line_utils_bonus.c # Bonus helper functions
└── README.md                 # Project documentation
```

### Required Files for Submission
- **Mandatory**: `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c`
- **Bonus**: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`

## Testing

### Test Different Buffer Sizes

```bash
# Test with various buffer sizes
for size in 1 5 42 100 1000 9999; do
    echo "Testing with BUFFER_SIZE=$size"
    gcc -D BUFFER_SIZE=$size get_next_line.c get_next_line_utils.c test_main.c
    ./a.out test.txt
    echo "---"
done
```

### Test Files to Create

```bash
# Create test files
echo -e "Line 1\nLine 2\nLine 3" > normal.txt
echo -n "No newline at end" > no_newline.txt
echo -e "\n\n\n" > only_newlines.txt
touch empty.txt

# Large file test
for i in {1..1000}; do echo "This is line number $i"; done > large.txt
```

### Comprehensive Test Program

```c
#include "get_next_line.h"

void test_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int count = 0;

    printf("=== Testing %s ===\n", filename);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: '%s'\n", ++count, line);
        free(line);
    }

    printf("Total lines: %d\n", count);
    close(fd);
    printf("\n");
}

int main(void)
{
    test_file("normal.txt");
    test_file("no_newline.txt");
    test_file("only_newlines.txt");
    test_file("empty.txt");
    test_file("large.txt");

    return (0);
}
```

### Testing Tools

Popular community testing tools:
- [GNL Tester by Tripouille](https://github.com/Tripouille/gnlTester)
- [42 File Checker](https://github.com/jgigault/42FileChecker)
- [GNL Lover](https://github.com/charMstr/GNL_lover)

## Common Challenges

### Memory Management Issues
- **Memory leaks**: Always free allocated memory
- **Double free**: Don't free the same pointer twice
- **Static variable**: Properly manage persistent data

### Buffer Handling Problems
- **Partial reads**: Handle cases where `read()` returns less than `BUFFER_SIZE`
- **No newlines**: Files that don't end with `\n`
- **Empty reads**: When `read()` returns 0 (EOF)

### Edge Cases
- **Invalid file descriptor**: Handle `fd < 0`
- **Read errors**: When `read()` returns -1
- **Empty files**: Files with no content
- **Binary files**: Files with null bytes

### Optimization Considerations
- **Buffer size**: Very small sizes (1) vs very large sizes (9999)
- **String operations**: Efficient concatenation and searching
- **Memory usage**: Minimize allocations for better performance

## Resources

### Official Documentation
- [42 Get Next Line Subject](https://cdn.intra.42.fr/pdf/pdf/960/en.subject.pdf)
- [C File I/O Functions](https://en.cppreference.com/w/c/io)

### Useful References
- [Static Variables in C](https://en.cppreference.com/w/c/language/storage_duration)
- [File Descriptors](https://en.wikipedia.org/wiki/File_descriptor)
- [Dynamic Memory Allocation](https://en.cppreference.com/w/c/memory)

### Testing Resources
- [GNL Tester by Tripouille](https://github.com/Tripouille/gnlTester)
- [GNL Lover](https://github.com/charMstr/GNL_lover)
- [42 Testers](https://github.com/jgigault/42FileChecker)

## Tips for Success

### Implementation Tips
1. **Start simple**: Get basic functionality working first
2. **Handle edge cases**: Empty files, no newlines, read errors
3. **Test thoroughly**: Use different buffer sizes and file types
4. **Memory check**: Use valgrind to detect leaks
5. **Norm compliance**: Follow 42 coding standards strictly

### Debugging Strategies
- Print buffer contents to understand data flow
- Use small buffer sizes to test edge cases
- Test with files of different sizes and formats
- Verify memory management with debugging tools

---

**Grade Expectations**: A correct implementation should achieve 100/100 when it handles all edge cases, manages memory properly, and works with various buffer sizes.

**Note**: This project is essential for understanding file I/O and will be used in many subsequent 42 projects. The skills learned here are fundamental for system programming and large project development.

cd get-next-line

# Compile with your program (no Makefile required)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Or for bonus
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

## Usage

### Basic Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    printf("Enter lines (Ctrl+D to end):\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You entered: %s", line);
        free(line);
    }

    return (0);
}
```

### Compilation Examples

```bash
# Small buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c

# Standard buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Large buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 get_next_line.c get_next_line_utils.c main.c
```

## Implementation Strategy

### Core Algorithm

1. **Read into buffer**: Use `read()` to fill buffer with `BUFFER_SIZE` bytes
2. **Find newline**: Search for `\n` in the accumulated data
3. **Extract line**: Return everything up to and including `\n`
4. **Save remainder**: Store remaining data in static variable for next call
5. **Repeat**: Continue until end of file

### Key Components

#### Static Variable Management
```c
static char *remainder = NULL; // Persistent between function calls
```

#### Buffer Reading
```c
char buffer[BUFFER_SIZE + 1];
int bytes_read = read(fd, buffer, BUFFER_SIZE);
```

#### String Joining
```c
remainder = ft_strjoin(remainder, buffer); // Concatenate with existing data
```

#### Line Extraction
```c
char *line = extract_line(remainder); // Get line up to \n
remainder = update_remainder(remainder); // Keep what's after \n
```

### Memory Management Pattern

1. **Allocate**: Create new strings as needed
2. **Free old**: Always free previous static content before updating
3. **Update static**: Store remaining content for next call
4. **Return line**: Give caller ownership of line (must free)

## Bonus Part

The bonus part extends the function to handle **multiple file descriptors simultaneously**.

### Bonus Features
- Can read from multiple files at the same time
- Each file descriptor maintains its own reading position
- Switching between file descriptors doesn't lose data

### Implementation Difference
```c
// Bonus uses array or linked list of static variables
static char *remainder[MAX_FD]; // Array approach
// or
static t_list *fd_list; // Linked list approach
```

### Bonus Usage Example
```c
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    // Read alternately from both files
    line = get_next_line(fd1); // First line from file1
    printf("File1: %s", line);
    free(line);

    line = get_next_line(fd2); // First line from file2
    printf("File2: %s", line);
    free(line);

    line = get_next_line(fd1); // Second line from file1
    printf("File1: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

## Examples

### Example 1: Basic File Reading

```c
// test.txt content:
// Hello World
// This is line 2
// Final line

#include "get_next_line.h"

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    int line_count = 1;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", line_count++, line);
        free(line);
    }
    close(fd);
    return (0);
}

// Output:
// Line 1: Hello World
// Line 2: This is line 2
// Line 3: Final line
```

### Example 2: Edge Cases

```c
// empty.txt: (empty file)
// no_newline.txt: "No newline at end"
// only_newlines.txt: "\n\n\n"

int main(void)
{
    test_file("empty.txt");
    test_file("no_newline.txt");
    test_file("only_newlines.txt");
    return (0);
}

void test_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;

    printf("Testing %s:\n", filename);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("'%s'\n", line);
        free(line);
    }
    close(fd);
    printf("---\n");
}
```

## Project Structure

Based on the [repository structure](https://github.com/Selmand42/Get-Next-Line):

```
.
├── get_next_line.c           # Main function implementation
├── get_next_line.h           # Header file with prototypes
├── get_next_line_utils.c     # Helper functions
├── get_next_line_bonus.c     # Bonus implementation (multiple FDs)
├── get_next_line_bonus.h     # Bonus header file
├── get_next_line_utils_bonus.c # Bonus helper functions
└── README.md                 # Project documentation
```

### Required Files for Submission
- **Mandatory**: `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c`
- **Bonus**: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`

## Testing

### Test Different Buffer Sizes

```bash
# Test with various buffer sizes
for size in 1 5 42 100 1000 9999; do
    echo "Testing with BUFFER_SIZE=$size"
    gcc -D BUFFER_SIZE=$size get_next_line.c get_next_line_utils.c test_main.c
    ./a.out test.txt
    echo "---"
done
```

### Test Files to Create

```bash
# Create test files
echo -e "Line 1\nLine 2\nLine 3" > normal.txt
echo -n "No newline at end" > no_newline.txt
echo -e "\n\n\n" > only_newlines.txt
touch empty.txt

# Large file test
for i in {1..1000}; do echo "This is line number $i"; done > large.txt
```

### Comprehensive Test Program

```c
#include "get_next_line.h"

void test_file(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *line;
    int count = 0;

    printf("=== Testing %s ===\n", filename);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: '%s'\n", ++count, line);
        free(line);
    }

    printf("Total lines: %d\n", count);
    close(fd);
    printf("\n");
}

int main(void)
{
    test_file("normal.txt");
    test_file("no_newline.txt");
    test_file("only_newlines.txt");
    test_file("empty.txt");
    test_file("large.txt");

    return (0);
}
```

### Testing Tools

Popular community testing tools:
- [GNL Tester by Tripouille](https://github.com/Tripouille/gnlTester)
- [42 File Checker](https://github.com/jgigault/42FileChecker)
- [GNL Lover](https://github.com/charMstr/GNL_lover)

## Common Challenges

### Memory Management Issues
- **Memory leaks**: Always free allocated memory
- **Double free**: Don't free the same pointer twice
- **Static variable**: Properly manage persistent data

### Buffer Handling Problems
- **Partial reads**: Handle cases where `read()` returns less than `BUFFER_SIZE`
- **No newlines**: Files that don't end with `\n`
- **Empty reads**: When `read()` returns 0 (EOF)

### Edge Cases
- **Invalid file descriptor**: Handle `fd < 0`
- **Read errors**: When `read()` returns -1
- **Empty files**: Files with no content
- **Binary files**: Files with null bytes

### Optimization Considerations
- **Buffer size**: Very small sizes (1) vs very large sizes (9999)
- **String operations**: Efficient concatenation and searching
- **Memory usage**: Minimize allocations for better performance

## Resources

### Official Documentation
- [42 Get Next Line Subject](https://cdn.intra.42.fr/pdf/pdf/960/en.subject.pdf)
- [C File I/O Functions](https://en.cppreference.com/w/c/io)

### Useful References
- [Static Variables in C](https://en.cppreference.com/w/c/language/storage_duration)
- [File Descriptors](https://en.wikipedia.org/wiki/File_descriptor)
- [Dynamic Memory Allocation](https://en.cppreference.com/w/c/memory)

### Testing Resources
- [GNL Tester by Tripouille](https://github.com/Tripouille/gnlTester)
- [GNL Lover](https://github.com/charMstr/GNL_lover)
- [42 Testers](https://github.com/jgigault/42FileChecker)

## Tips for Success

### Implementation Tips
1. **Start simple**: Get basic functionality working first
2. **Handle edge cases**: Empty files, no newlines, read errors
3. **Test thoroughly**: Use different buffer sizes and file types
4. **Memory check**: Use valgrind to detect leaks
5. **Norm compliance**: Follow 42 coding standards strictly

### Debugging Strategies
- Print buffer contents to understand data flow
- Use small buffer sizes to test edge cases
- Test with files of different sizes and formats
- Verify memory management with debugging tools

---

**Grade Expectations**: A correct implementation should achieve 100/100 when it handles all edge cases, manages memory properly, and works with various buffer sizes.

**Note**: This project is essential for understanding file I/O and will be used in many subsequent 42 projects. The skills learned here are fundamental for system programming and large project development.
