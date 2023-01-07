
## Implementation of SHA-256 algorithm in C++ without using external/internal libraries

### Requirements

- gcc or other c++ compiler
- cmake

### Compilation

- Execute cmake --build *INPUT PATH* --target TermProject_SHA256 -j 6

### Usage

- Run the compiled binary in your preferred shell
- Follow the on-screen instructions

### Known issues

- For an unknown reason, a CPU breakpoint is triggered if text longer 
than 1976 characters is passed for hashing. I have been researching 
the problem but couldn't find the exact solution. The breakpoint is
triggered when initialising the hash constants. There are indications
for it to be a memory allocation problem.
