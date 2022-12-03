#!/usr/bin/env python3

# Lib imports
import curses

# Local file imports
from draw import *

def main():
    # Init Curses
    stdscr = curses.initscr()
    curses.noecho()
    curses.cbreak()
    stdscr.keypad(True)
    curses.curs_set(0)
    stdscr.clear()
    stdscr.refresh()

    draw_date(stdscr)
    stdscr.getkey()

    # Terminate Curses
    curses.nocbreak()
    stdscr.keypad(False)
    curses.echo()
    curses.endwin()

main()
