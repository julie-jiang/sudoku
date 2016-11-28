"""
Preprocess the puzzles in rawpuzzle.txt
"""
import re
f = open("rawpuzzle.txt")
filelist = open("puzzle_list.txt", "w")
i = 1
for line in f:
    if re.search("^G.", line):
        fout = open("puzzle" + str(i) + ".txt", "w")
        filelist.write("puzzles/puzzle" + str(i) + ".txt\n")
        i += 1
    else:
        fout.write(" ".join(line))
