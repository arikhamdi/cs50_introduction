select people.name from people
join stars on stars.person_id=people.id
where stars.movie_id in (
    select movies.id from movies
    join stars on stars.movie_id=movies.id
    where stars.person_id=(select people.id from people where name='Kevin Bacon' and birth=1958)
)
and not stars.person_id=(select people.id from people where name='Kevin Bacon')
group by people.name;

