# Multithread Library Project

This project showcases a multithreaded file processing system implemented with a worker pool. It efficiently reads text files from a directory, processes them to count word occurrences, and compares the performance of multithreaded processing against sequential processing.

Over 1,000 iterations of processing four books, the multithreaded approach achieves an average runtime improvement of 47% compared to sequential processing!

## Project Goals

- **Adaptability**: Extend the worker pool to support various types of tasks beyond file processing.
- **Efficiency**: Handle a high volume of tasks and threads with minimal overhead.
- **Performance Optimization**: Enhance the performance gains from multithreading.
- **User-Friendly**: Offer an intuitive interface for task management and worker pool operations.

## Features

- **Worker Pool**: Manages a pool of worker threads to process tasks concurrently.
- **File Handler**: Reads and processes text files to count word occurrences.
- **Performance Comparison**: Measures and compares the time taken for multithreaded and sequential file processing.


## Building the Project

1. Clone the repository:
    ```sh
    git clone git@github.com:jonathan-r-davis/multithread-helper.git
    cd multithread-helper
    ```

2. Build the project with Makefile:
    ```sh
    make
    ```

3. Run the project:
    ```sh
    ./main
    ```

4. Rebuild the project:
    ```sh
    make rebuild
    ```

5. Clean the project:
    ```sh
    make clean
    ```
    
## Code Overview

### WorkerPool

The `WorkerPool` class manages a pool of worker threads that execute tasks concurrently.

### FileHandler

The `FileHandler` class handles reading and processing text files to count word occurrences.

### main.cpp

The `main.cpp` file contains the main function that sets up the worker pool, enqueues file processing tasks, and measures the performance of multithreaded and sequential processing.

## License

This project is licensed under the MIT License.