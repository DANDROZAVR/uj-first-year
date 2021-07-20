--ZAD1
create sequence if not exists seq
      increment by 1
      start 10
      minvalue 10
      maxvalue 99
----
--ZAD2
----
--ZAD3
create unique index on transakcje (z_konta, na_konto, data_zlecenia)
----
--ZAD4
 
create or replace view wplaty_wyplaty as
      select id as "Konto", (select count(*) from transakcje where z_konta = t.id) as "Ilosc wyplat",
        (select count(*) from transakcje where na_konto = t.id) as "Ilosc wplat"
      from (select nr_konta as id from konta) t
----
--ZAD5
create or replace view wplaty_wyplaty as
      select id as "Konto", (select count(*) from transakcje where z_konta = t.id) as "Ilosc wyplat",
        (select count(*) from transakcje where na_konto = t.id) as "Ilosc wplat"
      from (select nr_konta as id from konta) t;
select * from wplaty_wyplaty;
insert into transakcje(id, na_konto, kwota) values (200, 1004, 500.00);
select * from wplaty_wyplaty;
drop view wplaty_wyplaty;
----
--ZAD6
create or replace function oblicz_koszt(item numeric(11, 2))
      returns numeric(11, 2) as $$
              begin
                      return ROUND(item * 0.02, 2);
              end;
      $$ language plpgsql;
----
--ZAD7
create or replace function oblicz_koszt(item numeric(11, 2))
      returns numeric(11, 2) as $$
              begin
                      return ROUND(item * 0.02, 2);
              end;
      $$ language plpgsql;
select oblicz_koszt(kwota) from transakcje
----
--ZAD8
create or replace function bilans_kont()
      returns table(
              konto numeric(11, 2),
              suma_wplat numeric(11, 2),
              suma_wyplat numeric(11, 2)
      )  as
$$
      begin
       return query(select id, (select coalesce(sum(kwota), 0) from transakcje where na_konto = t.id),
        (select coalesce(sum(kwota), 0) from transakcje where z_konta = t.id)
      from (select nr_konta as id from konta) t);
      end;
$$ language plpgsql;
----
--ZAD9
create or replace function bilans_kont()
      returns table(
              konto numeric(11, 2),
              suma_wplat numeric(11, 2),
              suma_wyplat numeric(11, 2)
      )  as
$$
      begin
       return query(select id, (select coalesce(sum(kwota), 0) from transakcje where na_konto = t.id),
        (select coalesce(sum(kwota), 0) from transakcje where z_konta = t.id)
      from (select nr_konta as id from konta) t);
      end;
$$ language plpgsql;
select konto, suma_wplat - suma_wyplat as "bilans" from bilans_kont()
----
--ZAD10a
create or replace function silnia(n numeric)
returns
      numeric as
$$
      declare
              ans numeric;
              i integer;
      begin
              ans = 1;
              for i in 1..n
              LOOP
                      ans = ans * i;
              END LOOP;
              return ans;
      end;
$$ language plpgsql;
----
--ZAD10b
create or replace function silnia(n numeric)
returns
      numeric as
$$
      begin
              if (n <= 1)
              then
                      return 1;
              end if;
              return n * silnia(n - 1);
      end;
$$ language plpgsql;
----
--ZAD11
create sequence seq minvalue 1000 maxvalue 5000 increment 10;
 
create or replace function bilans_kont()
      returns table(
              konto numeric(11, 2),
              suma_wplat numeric(11, 2),
              suma_wyplat numeric(11, 2)
      )  as
$$
      begin
       return query(select id, (select coalesce(sum(kwota), 0) from transakcje where na_konto = t.id),
        (select coalesce(sum(kwota), 0) from transakcje where z_konta = t.id)
      from (select nr_konta as id from konta) t);
      end;
$$ language plpgsql;
 
create or replace function bonus_swiateczny(p numeric(11, 2) default 0.01)
      returns void as
$$
      declare
              konto record;
      begin
              for konto in select * from bilans_kont()
              LOOP
                      insert into transakcje (id, na_konto, kwota)
                      values
                      (nextval('seq'), konto.konto, ROUND(p * konto.suma_wyplat, 2));
              END LOOP;
      end;
$$ language plpgsql;
----
--ZAD12
create or replace function stan_konta(konto numeric(11), czas timestamp)
      returns numeric(11, 2) as
$$
      declare
              status numeric(11, 2);
              ac record;
      begin
              status = 0.00;
              for ac in select * from transakcje order by data_zlecenia
              LOOP
                      if ac.data_zlecenia > czas then exit; end if;
                      if ac.na_konto = konto
                      then
                              status = status + ac.kwota;
                      ELSEIF ac.z_konta = konto
                      then
                              status = status - ac.kwota;
                      END IF;
                      if status < 0.00
                      then
                              raise exception 'Wykryto ujemny bilans konta';
                      end if;
              END LOOP;
              return status;
      end;
$$ language plpgsql;
----
--ZAD13
create or replace function stan_konta(konto numeric(11), czas timestamp)
      returns numeric(11, 2) as
$$
      declare
              status numeric(11, 2);
              ac record;
      begin
              status = 0.00;
              for ac in select * from transakcje order by data_zlecenia
              LOOP
                      if ac.data_zlecenia > czas then exit; end if;
                      if ac.na_konto = konto
                      then
                              status = status + ac.kwota;
                      ELSEIF ac.z_konta = konto
                      then
                              status = status - ac.kwota;
                      END IF;
                      if status < 0.00
                      then
                              raise exception 'Wykryto ujemny bilans konta';
                      end if;
              END LOOP;
              return status;
      end;
$$ language plpgsql;
 
create or replace function historia_konta(konto numeric(11, 2))
      returns table (
              data timestamp,
              stan numeric(11, 2)
      ) as
$$
      begin
              return query(
                      select data_zlecenia, stan_konta(konto, data_zlecenia)
                      from transakcje
                      where z_konta = konto or na_konto = konto
                      order by data_zlecenia
              );
        end;
$$ language plpgsql;
----
--ZAD14
create or replace function stan_konta(konto numeric(11), czas timestamp)
      returns timestamp as
$$
      declare
              status numeric(11, 2);
              ac record;
      begin
              status = 0.00;
              for ac in select * from transakcje order by data_zlecenia
              LOOP
                      if ac.data_zlecenia > czas then exit; end if;
                      if ac.na_konto = konto
                      then
                              status = status + ac.kwota;
                      ELSEIF ac.z_konta = konto
                      then
                              status = status - ac.kwota;
                      END IF;
                      if status < 0.00
                      then
                              return ac.data_zlecenia;
                      end if;
              END LOOP;
              return null;
      end;
$$ language plpgsql;
 
create or replace function moment_rozspojniajacy()
      returns timestamp as
$$
      declare
              ac record;
      begin
              for ac in select * from transakcje order by data_zlecenia
              LOOP
                      if (stan_konta(ac.z_konta, ac.data_zlecenia) is not null)
                      then
                              return stan_konta(ac.z_konta, ac.data_zlecenia);
                      end if;
                      if (stan_konta(ac.na_konto, ac.data_zlecenia) is not null)
                      then
                              return stan_konta(ac.na_konto, ac.data_zlecenia);
                      end if;
              END LOOP;
              return null;
      end;
$$ language plpgsql;
 
 
----
--ZAD15
----
--ZAD16
----
--ZAD17
----
--ZAD18
----
--ZAD19
 
----
