CREATE TABLE houses (
    house_id INTEGER PRIMARY KEY NOT NULL,
    house TEXT NOT NULL UNIQUE,
    head TEXT NOT NULL UNIQUE
);

CREATE TABLE _students (
    student_id INTEGER NOT NULL PRIMARY KEY,
    student_name TEXT NOT NULL UNIQUE
);

CREATE TABLE house_assignments (
    student_id INTEGER UNIQUE PRIMARY KEY,
    house_id INTEGER NOT NULL,
    FOREIGN KEY(student_id) REFERENCES _students(student_id),
    FOREIGN KEY(house_id) REFERENCES houses(house_id)
);