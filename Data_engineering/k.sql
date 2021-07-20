--ZAD1
create or replace function fib(n int)
      returns numeric as
$$
      declare
              p1 numeric;
              p2 numeric;
              ans numeric;
              i int;
      begin
          if (n < 0) then
                      return 0;
              end if;
              if (n <= 1) then
                      return n;
              end if;
              p1 = 0;
              p2 = 1;
              for i in 2..n loop
                      ans = p1 + p2;
                      p1 = p2;
                      p2 = ans;
              end loop;
              return ans;
      end;
$$ language plpgsql;
----
--ZAD2
create or replace function srednia(id int)
      returns numeric(4, 3) as
$$
      declare
              ans numeric;
      begin
              ans = (select round(avg(c::integer), 3) from(
                              select unnest(notatka) as c
                              from notatki
                              where id_studenta = id) a
                         where a.c >= '2' and a.c <= '5');
              return ans;
      end;
$$ language plpgsql;
----
--ZAD3
create table oceny(
      id_studenta int not null references studenci(id),
      ocena int not null check(ocena >= 2 and ocena <= 5)
);
 
create or replace function f(ctid1 tid, idd int)
      returns void as
$$
      declare
              i record;
      begin
              for i in (select * from(select unnest(notatka) as c
                                              from notatki
                                              where id_studenta = idd and
                                                        ctid = ctid1) a
                                      where a.c >= '2' and a.c <= '5') loop
                      insert into oceny
                              values
                      (idd, i.c::integer);
              end loop;
      end;
$$ language plpgsql;
 
select f(ctid, id_studenta)
from notatki;
 
drop table if exists notatki;
----
--ZAD4
alter table studenci
add column egzamin int check(egzamin >= 2 and egzamin <= 5);
 
create or replace function addocena(ids int, ocen int)
      returns void as
$$
      begin
              update studenci
              set egzamin = ocen
              where id = ids;
      end;
$$ language plpgsql;
 
select addocena(id_studenta, ocena)
from egzaminy;
 
drop table egzaminy cascade;
 
create rule del2 as
on delete to studenci
do instead nothing;
 
create or replace function upd()
      returns trigger as
$$
      begin
              if (old.egzamin is not null) then
                      return null;
              end if;
              if (--new.egzamin is not null and
              (select count(*) from nieobecnosci where id_studenta = old.id) > 3) then
                      return null;
              end if;
              return new;
      end;
$$ language plpgsql;
 
create trigger upd1 before update
on studenci
for each row execute function upd();
----
--ZAD5
create table historia_cen(
      czas timestamp not null,
      pid int  references produkty,
      stara_cena numeric(10,2),
      nowa_cena numeric(10,2)
);
 
create or replace function ins()
      returns trigger as
$$
      begin
              insert into historia_cen
                      values
              (clock_timestamp(), new.pid, null, new.cena);
              return new;
      end;
$$ language plpgsql;
 
create trigger ins1 after insert
on produkty
for each row execute function ins();
 
create or replace function upd()
      returns trigger as
$$
      begin
              if (new.cena != old.cena or (new.cena is null and old.cena is not null) or (new.cena is not null and old.cena is null)) then
                      insert into historia_cen
                              values
                      (clock_timestamp(), new.pid, old.cena, new.cena);
                      return new;
              end if;
              return new;
      end;
$$ language plpgsql;
 
create trigger upd1 after update
on produkty
for each row execute function upd();
----
--ZAD6
rollback;
/*DROP TABLE IF EXISTS produkty2 cascade;
CREATE TABLE produkty2 (
    id integer PRIMARY KEY,
    cena numeric(8,2) NOT NULL,
    kolor character varying(80) NOT NULL,
    klasa_energetyczna character varying(5) NOT NULL,
    CONSTRAINT ck_cena CHECK (cena > 0)
);
 
DROP TABLE IF EXISTS lodowki2 cascade;
CREATE TABLE lodowki2 (
    id_produktu integer NOT NULL UNIQUE,
    pojemnosc_chlodziarki numeric(4,0) NOT NULL,
    pojemnosc_zamrazarki numeric(4,0) NOT NULL,
    bezszronowa boolean NOT NULL,
    CONSTRAINT ck_pc CHECK (pojemnosc_chlodziarki > 0),
    CONSTRAINT ck_pz CHECK (pojemnosc_zamrazarki > 0),
    CONSTRAINT fk_lodowki_produkty FOREIGN KEY (id_produktu) REFERENCES produkty
);
 
 
DROP TABLE IF EXISTS pralki2 cascade;
CREATE TABLE pralki2 (
    id_produktu integer NOT NULL UNIQUE,
    pojemnosc_znamionowa numeric(3,1) NOT NULL,
    roczne_zuzycie_wody numeric(6,0) NOT NULL,
    klasa_prania character(1) NOT NULL,
    CONSTRAINT ck_pzn CHECK (pojemnosc_znamionowa > 0),
    CONSTRAINT ck_rzw CHECK (roczne_zuzycie_wody > 0),
    CONSTRAINT ck_klasa_prania CHECK (klasa_prania IN ('A', 'B', 'C')),
    CONSTRAINT fk_pralki_produkty FOREIGN KEY (id_produktu) REFERENCES produkty
);
 
 
create or replace ins_prod()
      returns trigger as
$$
      begin
              insert into produkty2
                      values
              (new.id, new.cena, new.kolor, new.klasa_energetyczna);
              return new;
      end;
$$ language plpgsql;
 
drop trigger if exists
create trigger ins_prodt before insert
on produkty
*/
 
 
create or replace function ins_prod()
      returns trigger as
$$
      begin
              if (select count(*) from lodowki where id_produktu = new.id) = 0 and (select count(*) from pralki where id_produktu = new.id) = 0 then
                      raise notice 'BLAD';
              end if;
              if (select count(*) from lodowki where id_produktu = new.id) > 0 and (select count(*) from pralki where id_produktu = new.id) > 0 then
                      raise notice 'BLAD';
              end if;
              return new;
      end;
$$ language plpgsql;
 
drop trigger if exists ins_prodt on produkty;
create constraint trigger ins_prodt after insert
on produkty deferrable initially deferred
for each row execute procedure ins_prod();
 
create or replace function ins_pral()
      returns trigger as
$$
      begin
              if (select count(*) from produkty where new.id_produktu = id) = 0 then
                      raise notice 'BLAD';
              end if;
              if (select count(*) from lodowki where new.id_produktu = id_produktu) > 0 then
                      raise notice 'BLAD';
              end if;
              return new;
      end;
$$ language plpgsql;
 
drop trigger if exists ins_pralt on pralki;
create constraint trigger ins_pralt after insert
on pralki deferrable initially deferred
for each row execute procedure ins_pral();
 
create or replace function ins_lod()
      returns trigger as
$$
      begin
              if (select count(*) from produkty where new.id_produktu = id) = 0 then
                      raise notice 'BLAD';
              end if;
              if (select count(*) from pralki where new.id_produktu = id_produktu) > 0 then
                      raise notice 'BLAD';
              end if;
              return new;
      end;
$$ language plpgsql;
 
drop trigger if exists ins_lod1 on lodowki;
create constraint trigger ins_lod1 after insert
on lodowki deferrable initially deferred
for each row execute procedure ins_lod();
 
 
----
--ZAD7
----
--ZAD8
----
--ZAD9
----
--ZAD10
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
