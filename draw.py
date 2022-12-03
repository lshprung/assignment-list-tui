import curses
from datetime import date

def draw_date(stdscr, x = -1, y = 1):
    day_num = date.today().day
    date_str = date.today().strftime("%A, %B ")

    if (day_num % 10) == 1:
        date_str += str(day_num) + "st"
    elif (day_num % 10) == 2:
        date_str += str(day_num) + "nd"
    elif (day_num % 10) == 3:
        date_str += str(day_num) + "rd"
    else:
        date_str += str(day_num) + "th"

    if x < 0:
        x = int((stdscr.getmaxyx()[1] - len(date_str))/2)

    stdscr.addstr(y, x, date_str)
    stdscr.refresh()
