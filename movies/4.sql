SELECT COUNT(*) AS 'Number of Movies with rating 10.0' FROM movies
JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;