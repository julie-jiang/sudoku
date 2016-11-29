"""
Preprocess the puzzles in puzzles/set2/rawpuzzle.txt
"""
import re
f = open("rawpuzzle.txt")
filelist = open("puzzle_list.txt", "w")
i = 1
for line in f:
    fout = open("puzzle" + str(i) + ".txt", "w")
    for j in range(9):
        oneline = line[j * 9:(j + 1) * 9].replace(".", "0")
        fout.write((" ".join(oneline)) + "\n")
    filelist.write("data/puzzles/set2/puzzle" + str(i) + ".txt\n")
    i += 1
    