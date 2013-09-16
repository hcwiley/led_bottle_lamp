#!/usr/bin/env python
import os, feedparser, time, serial

SERIAL_PORT = os.environ.get("SERIAL_PORT")
if not SERIAL_PORT:
  print "Set the SERIAL_PORT env variable"
  exit(1)

ser = serial.Serial(SERIAL_PORT, 9600)

ser.write('i')

USERNAME = os.environ.get('GMAIL_USERNAME') or False
PASSWORD = os.environ.get('GMAIL_PASSWORD') or False

if not USERNAME:
  print "Set the GMAIL_USERNAME env variable"
  exit(1)

if not PASSWORD:
  print "Set the GMAIL_PASSWORD env variable"
  exit(1)

DEBUG = 1

MAIL_CHECK_FREQ = 10      # check mail every 60 seconds

last_count = 0

def newMessages(count):
  ser.write('n')
  ser.write(count)

def clearMessages():
  ser.write('c')

while True:

  mail_feed = feedparser.parse("https://" + USERNAME + ":" + PASSWORD +
      "@mail.google.com/gmail/feed/atom")["feed"]

  mail_count = int(mail_feed['fullcount'])

  if DEBUG:
    print "You have", mail_count, "new emails!"

  if mail_count != last_count:
    if mail_count > last_count:
      newMessages(mail_count)
    else:
      clearMessages()

  time.sleep(MAIL_CHECK_FREQ)
