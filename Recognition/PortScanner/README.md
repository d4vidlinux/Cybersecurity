# Port Scanner

This is a Port Scanner developed in C to assist in identifying active and potentially vulnerable ports.

Inspired by the `nmap` tool.

It accepts two arguments for execution: an IP address (required) and a port (optional).

- IP

The IP address is mandatory; it specifies the target to be scanned. If only this argument is provided, the Port Scanner will perform a full scan across all ports from 0 to 65535, identifying open ports, their associated services, and the protocols used.

- Port

The port argument allows for testing a specific port. The output will indicate whether the port is open or closed.

Using the TCP/IP protocol, the socket performs a three-way handshake. A successful connection returns 0. The script uses an `if` statement to check this return value; if it equals 0, the output will indicate that the port is open.

## Example (default)
`./main 127.0.0.1`

Output:
```bash
Port open: 631 Service: ipp - Protocol: tcp
Port open: 1716 Service: xmsg - Protocol: tcp
```

## Example (specified port)
Closed:
`./main 127.0.0.1 -p 630`

Output:

```bash
Port Closed: 630
```

Open:
`./main 127.0.0.1 -p 631`

```bash
Port open: 631 Service: ipp - Protocol: tcp
```

## Features

- Uses the `/etc/services` file to map ports to their corresponding services.

## Usage

1. Compile using `gcc`. ```bash
gcc principal.c -o principal
```

2. Execute
```bash
./principal 127.0.0.1
```

## Notice

- Created for educational purposes.
- Do not use on applications without authorization.
- The script may return false positives when identifying the service running on open ports.
- "Port Closed" simply means that a TCP connection could not be established with the port; it might still be filtered.
- There is no timeout between connections (yet).

## Author
d4vidlinux