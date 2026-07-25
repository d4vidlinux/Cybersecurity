#!/usr/bin/env python3

import requests
from concurrent.futures import ThreadPoolExecutor 
import sys
import pyfiglet

URL = sys.argv[1]
WORDLIST = sys.argv[2]
BANNER = pyfiglet.figlet_format("Janus Enumeration")
banner = f"{"="*30}{BANNER}{"="*100}"
author = """
Author: d4vidlinux
Copyright (c) 2026 d4vidlinux"""

with open(WORDLIST) as f:
    wordlist = set([line.strip() for line in f])

def enumeration(url, word):
    try:
        
        if url[-1] == "/":
            pass
        else:
            url += "/"

        r = requests.get(url+word)
        result = f"[+] {url}{word} - {r.status_code}"

        if r.status_code != 404:
            print(result)


    except requests.RequestException:
        pass

print(banner+author)
print("\n")

with ThreadPoolExecutor(max_workers=20) as TPE:
    TPE.map(lambda word: enumeration(URL, word), wordlist)

print("\n")
