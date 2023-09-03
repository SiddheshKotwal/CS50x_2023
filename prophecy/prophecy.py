from cs50 import SQL
import csv

db = SQL("sqlite:///roster.db")

try:
    db.execute('INSERT INTO houses(house, head) SELECT DISTINCT house, head FROM students;')
except ValueError:
    pass
house_dict = db.execute('SELECT * FROM houses')

with open("students.csv", 'r') as f:
    file = csv.DictReader(f)
    for row in file:
        name = row['student_name']
        try:
            db.execute('INSERT INTO _students(student_name) VALUES(?)', name)
        except ValueError:
            pass
        for i in  range(4):
            if row['house'] == house_dict[i]['house']:
                try:
                    db.execute('INSERT INTO house_assignments(student_id, house_id) VALUES(?, ?)',int(row['id']), int(house_dict[i]['house_id']))
                except ValueError:
                    pass