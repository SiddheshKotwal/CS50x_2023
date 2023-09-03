SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.title IN (
    SELECT title FROM movies
    JOIN people ON people.id = stars.person_id
    JOIN stars ON movies.id = stars.movie_id
    WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
    )
AND people.name != "Kevin Bacon";