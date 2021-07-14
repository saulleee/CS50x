-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.

-- SELECT name FROM people WHERE id IN (SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = "1958"));

SELECT name
FROM people
WHERE id IN
(SELECT person_id
FROM stars
WHERE movie_id IN
(SELECT id
FROM movies
WHERE id IN
(SELECT movie_id
FROM stars
WHERE person_id IN
(SELECT id
FROM people
WHERE name = "Kevin Bacon" AND birth = "1958"))))
AND name != "Kevin Bacon";

-- The same result come from these:
--
-- SELECT people.name
-- FROM people JOIN stars ON people.id = stars.person_id JOIN movies ON movies.id = stars.movie_id
-- WHERE movies.title = "The Matrix";
--
-- SELECT name
-- FROM people
-- WHERE id IN
-- (SELECT person_id
-- FROM stars
-- WHERE movie_id IN
-- (SELECT id
-- FROM movies
-- WHERE title = "The Matrix"));