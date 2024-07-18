#!/bin/bash

# Run the server and capture its output
server_output=$(./server)

# Run the client with the server's output as the first argument,
# and the script's first argument as the second argument
./client "$server_output" "$1"