#!/usr/bin/python

from bs4 import BeautifulSoup
import urllib2

contents = urllib2.urlopen('http://news.ycombinator.com')

soup = BeautifulSoup(contents.read())

titles = soup.find_all('td',class_="title")

for title in titles:
	if title.get('align')==None:
		print '[Title] '+title.a.contents[0]
		print '[URL] '+title.a['href']
		print ' '

