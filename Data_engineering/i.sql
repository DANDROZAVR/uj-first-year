--ZAD1
create or replace function cast_int(arg varchar)
      returns integer as
$$
      begin
              return cast(arg as integer);
              exception
                      when others then return null;
      end;
$$ language plpgsql
----
--ZAD2
CREATE OR REPLACE FUNCTION unnest_table(_tbl text)
  RETURNS setof text[] LANGUAGE plpgsql AS
$func$
BEGIN
 
RETURN QUERY EXECUTE '
SELECT (ARRAY[' || (
    SELECT string_agg(a.attname || '::text', ',' ORDER BY a.attnum)
    FROM   pg_catalog.pg_attribute a
    WHERE  a.attrelid = _tbl::regclass
    AND    a.attnum > 0
    AND    a.attisdropped = false
    ) || '])
FROM   ' || _tbl::regclass;
 
END
$func$;
 
select unnest_table('tab');
----
--ZAD3
create or replace function nulls(VARIADIC anyarray)
      returns integer as
$$
      declare
              ans integer;
              i integer;
      begin
              ans = 0;
              for i in 1..array_length($1, 1)
              LOOP
                      if $1[i] is null
                      then
                              ans = ans + 1;
                      end if;
              END LOOP;
              return ans;
      end;
$$ language plpgsql
----
--ZAD4
create or replace function remove_duplicates(tab text)
      returns void as
$$
      begin
              execute 'delete
                              from ' || tab || ' main
                              where (select count(*)
                                        from ' || tab || ' fufel
                                        where main.* = fufel.* AND fufel.ctid > main.ctid) > 0
                              ';
      end;
$$ language plpgsql;
----
--ZAD5
create or replace function array_intersect(f anyarray, s anyarray)
      returns anyarray as
$$
      begin
              return array(select * from unnest(f)
                         intersect
                         select * from unnest(s) order by 1);
      end;
$$ language plpgsql;
----
--ZAD6
create or replace function array_sort(f anyarray)
      returns anyarray as
$$
      begin
              return array(select * from unnest(f) order by 1);
      end;
$$ language plpgsql;
----
--ZAD7
select *, (ctid::text::point)[1]::integer as numer
from tab
where (ctid::text::point)[1]::integer % 3 = 1
----
--ZAD8
select *
from zwierzeta
order by rodzaj != 'pies',
               rodzaj != 'kot',
               nazwa;
----
--ZAD9
alter table tab drop constraint tab_b_check;
alter table tab
alter column b
      set data type boolean
              using case when b = 'tak' then true else false end;
----
--ZAD10
select tablename
from pg_tables
where schemaname = 'public'
----
--ZAD11
create or replace function remove_all()
      returns void as
$$
      declare
              i record;
      begin
              for i in select tablename from pg_tables where schemaname = 'public' loop
                      execute 'drop table if exists ' || i.tablename || ' cascade';
              end loop;
      end;
$$ language plpgsql;
 
select remove_all();
----
--ZAD12
select
    tablename as nazwa,
    pg_total_relation_size (tablename::varchar) as rozmiar
    from pg_tables
      where schemaname = 'public'
----
--ZAD13
----
--ZAD14
----
--ZAD15a
----
--ZAD15b
----
--ZAD16
----
--ZAD17
----
--ZAD18
----
--ZAD19
 
----
