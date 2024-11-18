from datetime import date
def ddiff(d11, d1):
    try:
        diff = (d1 - d0).days + 1
        print("result: ", diff)
    except ValueError:
        print("result: ", 0)
    print()

#ddiff(date(1, 1, 1), date(1,12,31))
#ddiff(date(4, 1, 1), date(4,12,31))
#ddiff(date(104, 1, 1), date(100,12,31))

def getDays(y, m, d):
    #print(y, m, d)
    d0 = date(1, 1, 1)
    try:
        d1 = date(y, m, d)
        diff = (d1 - d0).days + 1
    except ValueError:
        diff = 0
    print(f'test_strDateToDays("{y}-{m}-{d}", {diff});')

getDays(104, 1, 1)
getDays(104, 1, 31)
getDays(104, 2, 1)
getDays(104, 2, 28)
getDays(104, 2, 29)
getDays(104, 2, 30)
getDays(104, 7, 25)
getDays(104, 12, 31)

getDays(204, 1, 1)
getDays(204, 1, 31)
getDays(204, 2, 1)
getDays(204, 2, 28)
getDays(204, 2, 29)
getDays(204, 2, 30)
getDays(204, 7, 25)
getDays(204, 12, 31)

getDays(304, 1, 1)
getDays(304, 1, 31)
getDays(304, 2, 1)
getDays(304, 2, 28)
getDays(304, 2, 29)
getDays(304, 2, 30)
getDays(304, 7, 25)
getDays(304, 12, 31)

getDays(404, 1, 1)
getDays(404, 1, 31)
getDays(404, 2, 1)
getDays(404, 2, 28)
getDays(404, 2, 29)
getDays(404, 2, 30)
getDays(404, 7, 25)

getDays(504, 1, 1)
getDays(504, 1, 31)
getDays(504, 2, 1)
getDays(504, 2, 28)
getDays(504, 2, 29)
getDays(504, 2, 30)
getDays(504, 7, 25)
getDays(504, 12, 31)
getDays(504, 12, 31)

getDays(604, 1, 1)
getDays(604, 1, 31)
getDays(604, 2, 1)
getDays(604, 2, 28)
getDays(604, 2, 29)
getDays(604, 2, 30)
getDays(604, 7, 25)
getDays(604, 12, 31)
getDays(604, 12, 31)

getDays(704, 1, 1)
getDays(704, 1, 31)
getDays(704, 2, 1)
getDays(704, 2, 28)
getDays(704, 2, 29)
getDays(704, 2, 30)
getDays(704, 7, 25)
getDays(704, 12, 31)
getDays(704, 12, 31)

getDays(804, 1, 1)
getDays(804, 1, 31)
getDays(804, 2, 1)
getDays(804, 2, 28)
getDays(804, 2, 29)
getDays(804, 2, 30)
getDays(804, 7, 25)
getDays(804, 12, 31)
getDays(804, 12, 31)

getDays(2004, 1, 1)
getDays(2004, 1, 31)
getDays(2004, 2, 1)
getDays(2004, 2, 28)
getDays(2004, 2, 29)
getDays(2004, 2, 30)
getDays(2004, 7, 25)
getDays(2004, 12, 31)
getDays(2004, 12, 31)
