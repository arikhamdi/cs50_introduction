Select title from (
    Select movies.id, movies.title from movies where id in (
        Select movies.id from movies
        join stars on stars.movie_id=movies.id
        where stars.person_id=(select id from people where name='Johnny Depp')
        )
) as m
join stars on m.id=stars.movie_id
where stars.person_id=(select id from people where name='Helena Bonham Carter');