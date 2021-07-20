--ZAD1
select name as language, count(*) submits
from jezyk j join submits on j.id=language
group by 1
order by 2 DESC
----
--ZAD2
create function q(t int, s int)
      returns bigint
      as $$
      (select nullif(count(*), 0)
      from submits
      where problemsid=t AND (status=s or s=0))
      $$ language sql;
select shortname as name,
q(id, 8) ok,
q(id, 7) ans,
q(id, 5) tle,
q(id, 4) rte,
q(id, 14) rte,
q(id, 3) rte,
q(id, 2) cmp,
q(id, 10) rul,
q(id, 11) hea,
q(id, 6) as int,
q(id, 0) as all
from problems
order by length(LEFT(shortname, 3)), 1
----
--ZAD3
create function q(t int, s numeric)
      returns bigint
      as $$
                        select nullif(count(y.*), 0)
              from (select usersid
                        from submits
                        where problemsid = t
                        group by 1
                                          having (max(ocena) >= s/10 - 0.01 AND max(ocena) <= s/10 + 0.09) OR s = 20
                                 ) y
      $$ language sql;
select shortname as name,
q(id, 10) "100",
q(id, 9) "100-90",
q(id, 8) "90-80",
q(id, 7) "80-70",
q(id, 6) "70-60",
q(id, 5) "60-50",
q(id, 4) "50-40",
q(id, 3) "40-30",
q(id, 2) "30-20",
q(id, 1) "20-10",
q(id, 0) "10-0",
q(id, 20) as all
from problems
order by length(LEFT(shortname, 3)), 1
----
