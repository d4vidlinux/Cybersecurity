# Port Scanner

This is a Port Scanner developed in C to assist in identifying active and potentially vulnerable ports.

Inspired by the `nmap` tool.

It supports 5 command-line arguments: HELP (help screen), IP (required), PORT (optional), START (optional), and LIMIT (optional).


### HELP

Displays only the help screen, providing instructions on how to properly use the `Port Scanner` tool.

### IP

The IP address is mandatory for the scanner. It specifies the target to be scanned.

When only this argument is provided, the `Port Scanner` performs a full scan across ports 0 to 65535, displaying open ports, their associated services, and protocols.

### PORT

Used to test a specific port. With this option, the output indicates whether the specified port is open or closed.

Using the TCP/IP protocol, the socket attempts to establish a connection through the three-way handshake. A successful connection returns 0.

The script uses an `if` statement to check the return value. If the connection attempt returns 0, the output indicates that the port is open.

Using this option prevents the other scanning options from taking effect. For example:

`./main 127.0.0.1 -p 80 -s 20 -l 100`

This will only display the result for port 80.

### START

Specifies the port at which the scan should begin, changing the `port` variable to the provided value.

Default: 0

### LIMIT

Specifies the upper limit of the scan, changing the `limit` variable to the provided value.

Default: 65535

## Examples

### Default scan

`./main 127.0.0.1`

Output:

```bash
Port Opened: 631        Service: ipp - Protocol: tcp
Port Opened: 1716       Service: xmsg - Protocol: tcp
```

### Specified port

**Closed:**

`./main 127.0.0.1 -p 630`

Output:

```bash
Port Closed: 630
```

**Open:**

`./main 127.0.0.1 -p 631`

Output:

```bash
Port Opened: 631        Service: ipp - Protocol: tcp
```

### Start port

`./main 127.0.0.1 -s 632`

Output:

```bash
Port Opened: 1716        Service: xmsg - Protocol: tcp
```

### Port limit

`./main 127.0.0.1 -l 1000`

Output:

```bash
Port Opened: 631        Service: ipp - Protocol: tcp
```

## Features

- Uses the `/etc/services` file to map port numbers to their corresponding services.
- Modularized code using `functions.h` and `functions.c`.

## Usage

**1. Compile using `gcc`:**

```bash
gcc main.c functions.c -o main
```

**2. Run the program:**

```bash
./main 127.0.0.1
```

## Warning

- Developed for educational purposes.
- Do not use against systems without proper authorization.
- The script may produce false positives when identifying the services running on open ports.
- `Port Closed` only means that a TCP connection could not be established with the port. The port may simply be filtered.
- Connection attempts do not currently have a timeout mechanism.

## Author

d4vidlinux