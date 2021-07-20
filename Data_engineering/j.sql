--ZADa
create sequence for_id start with 1 increment by 1;
create table naukowcy(
      imie varchar(100) not null default '',
      nazwisko varchar(100) not null default '',
      rok numeric(4) not null default 0,
      id int not null primary key
);
 
create or replace function upd()
      returns trigger as
$$
      begin
              new.id = old.id;
              return new;
      end;
$$ language plpgsql;
 
create or replace function ins()
      returns trigger as
$$
      begin
              new.id = nextval('for_id');
              return new;
      end;
$$ language plpgsql;
 
 
create trigger upd before update
on naukowcy
for each row execute function upd();
 
create trigger ins before insert
on naukowcy
for each row execute function ins();
----
--ZADb
create sequence bfor_id1 start with 1 increment by 1;
create sequence bfor_id2 start with 1 increment by 1;
create table czasopisma(
      krotka_nazwa varchar(100) not null unique,
      pelna_nazwa varchar(100) not null,
      id integer not null primary key default nextval('bfor_id1')
);
create table konferencje(
      nazwa varchar(100) not null,
      kraj varchar(100) not null,
      miejsce varchar(100) not null,
      rok numeric(4) not null,
      id integer not null primary key default nextval('bfor_id2'),
      unique (nazwa, rok)
);
----
--ZADc
create sequence cfor_id start with 1 increment by 1;
create table typy(
      typ int not null primary key,
      opis varchar(100) not null
);
insert into typy
      values
 (1, 'czasopismo'),
 (2, 'konferencja');
 
create table publikacje(
      nazwa varchar(100) not null,
      typ integer not null references typy(typ),
      zrodlo integer not null,
      rok numeric(4) not null,
      numer integer not null,
      od integer not null,
      "do" integer not null,
      id integer not null primary key default nextval('cfor_id')
);
create or replace function check_pub_ins()
      returns trigger as
$$
      declare
              bad boolean;
      begin
              bad = false;
              if (new.typ = 1) then
                      if (select count(*) from czasopisma c where c.id = new.zrodlo) = 0 then
                              bad = true;
                      end if;
              elsif (new.typ = 2) then
                      if (select count(*) from konferencje c where c.id = new.zrodlo) = 0 then
                              bad = true;
                      end if;
              else
                      bad = true;
              end if;
              if (select count(*)
                      from publikacje p
                  where new.zrodlo = p.zrodlo and new.rok = p.rok and  new.numer = p.numer
                              and new.od <= p."do" and new.do >= p."od") > 0 then
                 bad = true;
              end if;
              if (bad = true) then
                      return null;
              end if;
              return new;
      end;
$$ language plpgsql;
 
 
create or replace function check_pub_upd()
      returns trigger as
$$
      declare
              bad boolean;
      begin
              bad = false;
              if (new.typ = 1) then
                      if (select count(*) from czasopisma c where c.id = new.zrodlo) = 0 then
                              bad = true;
                      end if;
              elsif (new.typ = 2) then
                      if (select count(*) from konferencje c where c.id = new.zrodlo) = 0 then
                              bad = true;
                      end if;
              else
                      bad = true;
              end if;
              if (select count(*)
                      from publikacje p
                  where new.zrodlo = p.zrodlo and new.rok = p.rok and  new.numer = p.numer
                              and new.od <= p."do" and new.do >= p."od" and new.id != p.id) > 0 then
                 bad = true;
              end if;
              if (old.id != new.id) then
                      bad = true;
              end if;
              if (bad = true) then
                      return old;
              end if;
              return new;
      end;
$$ language plpgsql;
 
 
create trigger ctrig1 before insert
on publikacje
for each row execute function check_pub_ins();
 
create trigger ctrig2 before update
on publikacje
for each row execute function check_pub_upd();
----
--ZADd
create table publikacje_autorzy(
              idpub int not null references publikacje(id),
              idautor int not null references naukowcy(id),
              primary key (idpub, idautor)
      );
      create or replace function nowa_publikacja(nazwaa varchar, typp int, zrodloo int, rokk numeric(4), numerr int, odd int, doo int, pierwszyautorr int)
              returns int as
      $$
              declare
                      ans int;
                      bad boolean;
                      templen int;
              begin
                  bad = false;
                      templen = (select count(*) from publikacje);
                      insert into publikacje
                              values
                      (nazwaa, typp, zrodloo, rokk, numerr, odd, doo);
                      if (templen = (select count(*) from publikacje)) then
                              return null;
                      end if;
                      ans = (select sum(id) from publikacje p where p.typ = typp and p.zrodlo = zrodloo and p.rok = rokk and p.numer = numerr and p.od = odd limit 1);
                      if (ans = null) then
                              return null;
                      end if;
                      insert into publikacje_autorzy
                                      values
                      (ans, pierwszyautorr);
                      return ans;
                      exception
                        when others then return null;
              end;
      $$ language plpgsql;
 
      create or replace function dodaj_autora(id_autor int, id_publikacja int)
              returns void as
      $$
              begin
                      insert into publikacje_autorzy
                              values
                      (id_autor, id_publikacja);
                      exception
                        when others then null;
              end;
      $$ language plpgsql;
----
--ZADe
create table referencje(
      idpub integer not null references publikacje(id),
      idcytat integer not null references publikacje(id) check(idcytat != idpub),
      unique(idcytat, idpub)
);
----
--ZADf
----
--ZADg
----
