from operator import itemgetter
import sys

current_word = None
current_count = 0
word = None

for line in sys.stdin:  # read one line from standard input
  line = line.strip()   # remove blank in line
  word, count = line.split('/t', 1)   # divde and store line in key, value
  try:
    count = int(count)
  except ValueError:
    continue
    
  if current_word == word:    # if same words comes out sqeuntially
      current_count += count
  else:
      if current_word:
          print('%s\t%s' % (current_word, current_count))
      current_count = count
      current_word = word
  
  # print word
  if current_word == word:
      print('%s\t%s' % (current_word, current_count))
