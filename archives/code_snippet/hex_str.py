#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys

choose = ""
data = ""


def hex2char():
    output = data.decode('hex')
    print output


def char2hex():
    output = data.encode('hex')
    print output


if __name__ == '__main__':
    if len(sys.argv) == 3:
        choose = sys.argv[1]
        data = sys.argv[2]

        if choose.lower() == 'hex2char':
            hex2char()
        if choose.lower() == 'char2hex':
            char2hex()

        if choose.lower() != 'hex2char' and choose.lower() != 'char2hex':
            print "Wrong param,try again"
    else:
        print "Usage: <hex2char|char2hex> <data>"
