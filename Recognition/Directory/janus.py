#!/usr/bin/env python3

import requests
from concurrent.futures import ThreadPoolExecutor 
import pyfiglet
import argparse
import time

# Args 
parser = argparse.ArgumentParser(description="Directory Enumerator")
parser.add_argument("-u", "--url", help="Set a url here. Example: http://example.com", required=True)
parser.add_argument("-w", "--wordlist", help="Set a wordlist here. Example: /home/user/Wordlists/small.txt", required=True)
parser.add_argument("-t", "--threads", type=int, help="Threads to use. Default: 20", default=20, required=False)
parser.add_argument("-T", "--timeout", type=float, help="Set the timeout for requests. Default: 2", default=2, required=False)

args = parser.parse_args()

# Global Variables
BANNER = pyfiglet.figlet_format("Janus Enumeration")
URL = args.url
WORDLIST = args.wordlist
THREADS = args.threads
TIMEOUT = args.timeout

# Variables
banner = "="*30 + BANNER + "="*100
author = """
Author: d4vidlinux
Copyright (c) 2026 d4vidlinux"""
session = requests.Session()

def main():
    # Wordlist parser
    with open(WORDLIST) as f:
        wordlist = set([line.strip() for line in f])

    # Main Function
    def enumeration(url, word):
        try:
            
            if not url.endswith("/"):
                url += "/"

            r = session.get(url+word, timeout=TIMEOUT)
            result = f"[+] {url}{word} - {r.status_code}"

            if r.status_code != 404:
                print(result)

        except requests.exceptions.ConnectionError as errc:
            print(f"[!] Connection Error occurred: {errc}")  # DNS failure or refused connection

        except requests.exceptions.Timeout as errt:
            print(f"[!] Timeout Error occurred: {errt}")  # Server took too long to respond

        except requests.exceptions.TooManyRedirects as errr: # redirect loop
            print(f"[!] Too Many Redirects occurred: {errr}")  

        except requests.exceptions.RequestException as err:
            print(f"[!] An unknown Request error occurred: {err}")

    # Execution Time
    begin = time.perf_counter()

    # Introduction
    print(banner+author)
    print("\n")

    # Threads
    with ThreadPoolExecutor(max_workers=THREADS) as TPE:
        TPE.map(lambda word: enumeration(URL, word), wordlist)
        

    final = time.perf_counter()

    # Final
    print(f"\nFinished in {final - begin:.2f} seconds\n")

if __name__ == "__main__":
    main()
