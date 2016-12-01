import subprocess
command = ["./run_soduku", "--solve", "data/puzzles/set1/puzzle1.txt"]
proc = subprocess.Popen(command, stdout=subprocess.PIPE)
output = proc.communicate()[0]
print output 