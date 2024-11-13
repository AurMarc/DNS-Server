# DNS Server Implementation in C++

This is a simple DNS server implementation in C++ that listens for DNS queries over UDP on port `2053`. It parses incoming DNS queries, generates DNS responses, and sends them back to the client. The server is capable of handling basic DNS queries and can be extended to support additional DNS features.

## Features

- Listens for DNS queries over UDP.
- Parses incoming DNS query messages and generates corresponding DNS response messages.
- Responds with a mock DNS A record (IPv4 address) for queried domain names.
- Optionally forwards DNS queries to a configured upstream DNS resolver.
- Supports handling DNS query sections (questions) and returns appropriate answers.

## Prerequisites

- C++17 or later
- Linux/Unix-like environment (the implementation uses POSIX networking APIs)
- `Make` or CMake for building

## Dependencies

- No external libraries are required. The implementation uses standard C++ libraries and POSIX APIs.

## Files

- `dnsheader.hpp` - Contains the DNS header structure definitions and utility functions for parsing and encoding DNS headers.
- `dnsquestion.hpp` - Contains the DNS question section structure definition and utility functions for handling DNS questions.
- `dnsanswer.hpp` - Contains the DNS answer section structure definition and utility functions for encoding DNS answers.
- `main.cpp` - The main DNS server code that listens for incoming UDP packets, processes the DNS queries, and sends the responses.

## Build Instructions

### Using Makefile

1. Clone the repository or download the source code to your local machine.
2. Navigate to the directory containing the source code.
3. Run the following command to build the server:
    ```bash
    make
    ```

### Using CMake

Alternatively, you can use CMake to build the project.

1. Create a build directory:
    ```bash
    mkdir build
    cd build
    ```
2. Run CMake to generate the build files:
    ```bash
    cmake ..
    ```
3. Build the project:
    ```bash
    make
    ```

## Usage

### Starting the Server

To start the server, run the executable as follows:

```bash
./dns_server
