--ZAD1
create or replace function check_pesel()
      returns trigger as
$check_pesel$
      declare
              bad boolean;
              i integer;
              sum integer;
              c integer;
      begin
              bad = false;
              sum = 0;
              if (length(new.pesel) != 11)
              then
                      raise exception 'Niepoprawny PESEL';
              end if;
              for i in 1..11
              LOOP
                      c = substring(new.pesel, i, 1)::integer;
                      if (i % 4 = 1 or i = 11)
                      then
                              sum = sum + c * 1;
                      elseif (i % 4 = 2)
                      then
                              sum = sum + c * 3;
                      elseif (i % 4 = 3)
                      then
                              sum = sum + c * 7;
                      else
                              sum = sum + c * 9;
                      end if;
              END LOOP;
              if (sum % 10 != 0)
              then
                      raise exception 'Niepoprawny PESEL';
              end if;
              return new;
      end;
$check_pesel$ language plpgsql;
 
create trigger check_pesel before update or insert
on pacjenci
for each row execute procedure check_pesel();
----
--ZAD2
create or replace function add_wizyt()
      returns trigger as
$add_wizyt$
begin
      if (new.data_zakonczenia is null)
      then
              new.data_zakonczenia = new.data_rozpoczecia::timestamp + '30 minutes'::interval;
      end if;
      return new;
end;
$add_wizyt$ language plpgsql;
 
create trigger add_wizyt before update or insert
on wizyty
for each row execute procedure add_wizyt();
----
--ZAD3
create or replace function date_delete()
      returns trigger as
$date_delete$
      begin
              if (current_timestamp - '5 years'::interval < old.data_zakonczenia)
              then
                      return null;
              end if;
              return old;
      end;
$date_delete$ language plpgsql;
 
create trigger date_delete before delete
on wizyty
for each row execute procedure date_delete();
----
--ZAD4
create or replace function add_visit()
      returns trigger as
$add_visit$
      declare
              bad boolean;
      begin
              if (new.data_zakonczenia - '1 hour'::interval > new.data_rozpoczecia)
              then
                      bad = true;
              end if;
              if (select count(*) from wizyty
                      where data_rozpoczecia > new.data_zakonczenia or data_zakonczenia < new.data_rozpoczecia
                  ) < (select count(*) from wizyty)
              then
                      bad = true;
              end if;
              if (bad = true)
              then
                      new = null;
                      return null;
              end if;
              return new;
      end;
$add_visit$   language plpgsql;
 
drop trigger if exists add_visit on wizyty;
create trigger add_visit before insert or update
on wizyty
for each row execute function add_visit();
----
--ZAD5
create table lekarze_prowadzacy(
      pesel char(11) not null references pacjenci,
      lekarz integer not null references lekarze,
      primary key(lekarz, pesel)
);
 
create or replace function LAST_FUNCTION()
      returns trigger as
$$
declare
      ans int;
begin
      ans = (select id
                 from lekarze join specjalizacje on id_lekarza = id
                 where specjalizacja = 'Medycyna rodzinna'
                 group by id
                 order by (select count(*)
                                       from lekarze_prowadzacy
                                       where lekarz = id)
                      limit 1
                );
      if (ans is null)
      then
              return old;
      end if;
      insert into lekarze_prowadzacy(pesel, lekarz)
              values
      (new.pesel, ans);
      return new;
end;
$$ language plpgsql;
 
 
create trigger LAST_TASK after insert
on pacjenci
for each row execute function LAST_FUNCTION();
 
--insert into pacjenci values
--('21111111111', 'aaa', 'OOO');
----
--ZAD6
create or replace view pediatrzy as
      select z.*
      from lekarze z join specjalizacje on z.id = id_lekarza
      where specjalizacja = 'Pediatria';
 
create or replace function add_ped()
      returns trigger as
$add_ped$
      begin
              insert into lekarze(id, imie, nazwisko) values (new.id, new.imie, new.nazwisko);
              insert into specjalizacje(id_lekarza, specjalizacja) values(new.id, 'Pediatria');
              return new;
      end;
$add_ped$ language plpgsql;
 
create trigger add_ped instead of insert
on pediatrzy
for each row execute function add_ped();
----
--ZAD7
create or replace view chirudzy as
      select z.id, z.imie, z.nazwisko
      from lekarze z join specjalizacje on z.id = id_lekarza
      where specjalizacja = 'Chirurgia';
 
create or replace rule add_ch2 as
on delete to chirudzy
do instead nothing;
----
--ZAD8
create or replace rule add_ch as
on delete to lekarze
where (select count(*)
         from lekarze join specjalizacje on id_lekarza = id
         where id_lekarza = old.id AND specjalizacja = 'Chirurgia'
        ) > 0
do instead nothing;
----
--ZAD9
create or replace rule add_ch as
on delete to pacjenci
do also
      delete
      from wizyty
      where pacjent = old.pesel;
----
--ZAD10
drop table if exists another_table cascade;
create table another_table(
      pacjent character varying(11),
      specjalista character varying(80),
      termin_od timestamp,
      termin_do timestamp
      --as specjalizacja
);
--drop view if exists terminarz;
create or replace view terminarz as
      select * from another_table;
--select pacjent, specjalizacja as specjalista, data_rozpoczecia as termin_od, data_zakonczenia as termin_do
--from wizyty join lekarze on id = lekarz;
create or replace function get_doctor(data_rozp timestamp, data_zak timestamp, doctor_class character varying(80))
      returns integer
as $$
declare
      ans int;
begin
      ans =
      return ans;
end;
$$ language plpgsql;
 
create or replace function add_doctor(item record)
returns void as
$$
      declare
              ans integer;
      begin
              ans =
               (select d.id
                from lekarze d join specjalizacje on d.id = id_lekarza
          where item.specjalista = specjalizacja AND (select count(*)
                                                                                                      from lekarze join wizyty on lekarz = id
                                                                                                      AND ((item.termin_do > data_rozpoczecia AND item.termin_od < data_zakonczenia))
                                                                                                      where d.id = id) = 0
                order by id_lekarza limit 1);
 
              if (ans is not null)
              then
                      insert into wizyty values (ans, item.pacjent, item.termin_od, item.termin_do);
              end if;
      end;
$$ language plpgsql;
 
create or replace rule add_term as
on insert to terminarz do instead
(
      select add_doctor(new);
);
 
--select * from lekarze join specjalizacje on id = id_lekarza where specjalizacja = 'Pediatria';
--insert into terminarz values(46062718514, 'Pediatria', '2019-07-22 14:00:00', '2019-07-22 14:30:00');
--select * from wizyty order by data_zakonczenia DESC;
 
----
--ZAD11
----
--ZAD12
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
