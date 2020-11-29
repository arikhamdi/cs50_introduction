select title from movies
join ratings on ratings.movie_id=movies.id
join stars on stars.movie_id=movies.id
where stars.person_id=(select id from people where name='Chadwick Boseman')
order by rating desc limit 5;