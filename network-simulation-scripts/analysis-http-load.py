#!/usr/bin/python
#coding=gb18030

if __name__ == '__main__':
    import sys
    import re
    pattern0 = re.compile(r'.[usr|qps]=(?P<usr>.+) (?P<rep>.+)')
    pattern1 = re.compile(r'(?P<fetches>.+) fetches, ')
    pattern2 = re.compile(r'(?P<rate>.+) fetches/sec, ')
    pattern3 = re.compile(r'msecs/connect: (?P<mean>.+) mean, (?P<max>.+) max, (?P<min>.+) min')
    pattern4 = re.compile(r'code 200 -- (?P<code>.+)')

    match0 = None
    match1 = None
    match2 = None
    match3 = None
    match4 = None
    for line in sys.stdin:
        ss = line.strip()
        if not match0:
            match0 = pattern0.search(ss)
        if not match1:
            match1 = pattern1.search(ss)
        if not match2:
            match2 = pattern2.search(ss)
        if not match3:
            match3 = pattern3.search(ss)
        if not match4:
            match4 = pattern4.search(ss)
        if match0 and match1 and match2 and match3 and match4:
            usr = match0.group("usr")
            rep = match0.group("rep")
            fetches = match1.group("fetches")
            rate = match2.group("rate")
            mean = match3.group("mean")
            max = match3.group("max")
            min = match3.group("min")
            code = match4.group("code")
            match0 = None
            match1 = None
            match2 = None
            match3 = None
            match4 = None
            print usr + '\t' + rep + '\t' + fetches + '\t' + rate + '\t' + mean + '\t' + max + '\t' + min + '\t' + code