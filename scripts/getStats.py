#!/usr/bin/env python3

import sys
import regex as re

for filename in sys.argv[1:]:
    file = open(filename,'r')

    ret = ""
    for line in file.readlines():
        if not re.match(r"\s*\n+",line) and not re.match(r"^#.*?",line):
            if not re.match(r" Performance counter stats for.*?",line):
                #remove times
                if not re.match(r".*?seconds.*?",line):
                    aux = line.split("#")
                    aux2 = re.split("\s+",aux[0])
                    aux3 = re.split("\s+",aux[1])
                    
                    #clean
                    while "" in aux2:
                        aux2.remove("")

                    while "" in aux3:
                        aux3.remove("")

                    ret += aux2[0] + " " + aux3[0] + " "
    print(ret)
