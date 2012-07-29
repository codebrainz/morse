#!/usr/bin/env python

"""
Reads Morse codes from JSON file and formats them for a C string array.

See COPYING file for copyright and license information.
"""

import json
import sys
import optparse

def code_max(data):
  max_len = 0
  for n, c, code in data:
    l = len(code)
    if l > max_len:
      max_len = l
  return max_len

def get_name_and_code(data, char):
  char = char.upper()
  for n, c, code in data:
    if str(c.upper()) == str(char):
      return n, code
  return "", ""

def gen_data_array(data):
  text = ''
  max_code_len = code_max(data) + len('  "",')
  for i in range(0, 256):
    name, code = get_name_and_code(data, chr(i))
    line = '  "%s",' % code
    line = line.ljust(max_code_len)
    if len(code) > 0:
      com = '/* %d: %s */' % (i, name.upper())
    else:
      com = '/* %d: NOT USED */' % i
    text += str(line + com).rstrip() + '\n'
  return text.strip()

def do_replacements(tmpl, data):
  data_array = gen_data_array(data)
  code = tmpl.replace('/*@@morse_codes@@*/', data_array)
  return code

def main(args):
  p = optparse.OptionParser()
  p.add_option('-t', '--template', metavar='FILE', dest='tmpl', default=None,
    help='header file template')
  p.add_option('-j', '--json', metavar='FILE', dest='json', default=None,
    help='json data file')
  opts, args = p.parse_args(args)
  if not opts.tmpl:
    p.error('missing required template file option')
  if not opts.json:
    p.error('missing required json data file argument')
  tmpl = open(opts.tmpl, 'r').read()
  data = json.loads(open(opts.json, 'r').read())
  code = do_replacements(tmpl, data)
  print(code)
  return 0

if __name__ == "__main__":
  sys.exit(main(sys.argv))
