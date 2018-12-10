import sys

for lint in sys.stdin:  # read from stdin
  line = line.strip()   # remove leading and trailing whitespaces
  words = line.split()  # split the line into words and returns as a list
  for word in words:
    # write the results to STDOUT
     print('%s\t%s' %(word, 1)) # emit the word and a 1 as its count
