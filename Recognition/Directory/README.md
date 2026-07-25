# Janus 

This is a simple directory enumeration tool inspired by Gobuster and ffuf.

The script uses the following syntax:

`python3 janus.py URL WORDLIST`

or

`./janus.py URL WORDLIST`

It uses multiple threads for faster execution.

![Code print](Janus_test.png)


## Features 

- Multithreaded scanning
- Simple command-line interface
- Clean terminal output

## Requirements
- Python 3.x installed
- requests
- pyfiglet

## Usage

1. Clone the repository:
```bash
    git clone https://github.com/d4vidlinux/janus.git
    cd janus
```
2. Install Python:
[Download Python](https://www.python.org/downloads)

3. Create and activate a virtual environment:
```bash
    python3 -m venv venv
    source venv/bin/activate
```

3. Make the script executable (optional):
```bash
    chmod +x janus.py
```
4. Install the requirements: 
```bash
    pip install -r requirements.txt
```

5. Execute:
```bash
    python janus.py http://example.com wordlist.txt
```




