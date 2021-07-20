--ZAD1
drop table if exists zwierzeta cascade;
create table zwierzeta(
      gatunek varchar(100) not null,
      jajorodny char(1) not null check(jajorodny = 'T' or jajorodny = 'N'),
      liczba_konczyn numeric(2) not null,
      data_odkrycia date not null
);
----
--ZAD2
drop table if exists klienci cascade;
create table klienci(
      pesel char(11) primary key,
      adres varchar(100),
      wiek numeric(2) not null,
      wspolpraca_od date not null
);
----
--ZAD3
drop table if exists uczelnie cascade;
create table uczelnie(
      id_uczelni numeric(4) primary key,
      nazwa varchar(100) unique,
      adres varchar(100),
      budzet numeric(10, 2) not null,
      zalozona date not null
);
----
--ZAD4
drop table if exists ksiazki cascade;
create table ksiazki(
      id_ksiazki numeric(10) primary key,
      tytul varchar(100) not null,
      autorzy varchar(100),
      cena numeric(6, 2),
      data_wydania date
);
----
--ZAD5
drop table if exists pokoje cascade;
create table pokoje(
      numer_pokoju numeric(3) primary key,
      id_zesp numeric(2) references zespoly(id_zesp),
      liczba_okien numeric(1)
);
----
--ZAD6
drop table if exists plyty_cd cascade;
create table plyty_cd(
      kompozytor char(100) not null,
      tytul_albumu char(100) not null,
      data_nagrania date,
      data_wydania date check(data_wydania > data_nagrania),
      czas_trwania interval check (czas_trwania < '1 hour 22 minutes'),
      constraint un_ko_ty unique(kompozytor, tytul_albumu)
);
----
--ZAD7
create table szef_podwladny
as
(
      select p2.nazwisko as szef, p.nazwisko as podwladny
      from pracownicy p join pracownicy p2 on p.id_szefa = p2.id_prac
      where p.nazwisko is not null AND p2.nazwisko is not null
)
----
--ZAD8
drop table if exists plyty_cd cascade;
create table plyty_cd(
      kompozytor char(100) not null,
      tytul_albumu char(100) not null,
      data_nagrania date,
      data_wydania date check(data_wydania > data_nagrania),
      czas_trwania interval check (czas_trwania < '1 hour 22 minutes'),
      constraint un_ko_ty unique(kompozytor, tytul_albumu)
);
alter table plyty_cd drop constraint un_ko_ty;
alter table plyty_cd add constraint un_ko_ty primary key(kompozytor, tytul_albumu);
----
--ZAD9
create table plyty_cd(
      kompozytor char(100) not null,
      tytul_albumu char(100) not null,
      data_nagrania date,
      data_wydania date check(data_wydania > data_nagrania),
      czas_trwania interval check (czas_trwania < '1 hour 22 minutes'),
      constraint un_ko_ty unique(kompozytor, tytul_albumu)
);
alter table plyty_cd drop constraint un_ko_ty;
alter table plyty_cd add constraint un_ko_ty primary key(kompozytor, tytul_albumu);
alter table plyty_cd drop constraint un_ko_ty;
insert into plyty_cd(kompozytor, tytul_albumu)
      values
              ('Tomasz', 'lej mi pol'),
              ('Tomasz', 'lej mi pol');
alter table plyty_cd add constraint un_ko_ty primary key(kompozytor, tytul_albumu);
----
--ZAD10
create table zwierzeta(
      gatunek varchar(100) not null,
      jajorodny char(1) not null check(jajorodny = 'T' or jajorodny = 'N'),
      liczba_konczyn numeric(2) not null,
      data_odkrycia date not null
);
alter table zwierzeta rename to gatunki;
drop table if exists gatunki cascade;
----
--ZAD11
drop table if exists projekty cascade;
create table projekty (
        id_projektu numeric(4) primary key,
        opis_projektu char(20) unique not null,
        data_rozpoczecia date default now(),
        data_zakonczenia date check(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7, 2)
);
----
--ZAD12
drop table if exists projekty cascade;
create table projekty (
        id_projektu numeric(4) primary key,
        opis_projektu char(20) unique not null,
        data_rozpoczecia date default now(),
        data_zakonczenia date check(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7, 2)
);
drop table if exists przydzialy cascade;
create table przydzialy (
        id_projektu numeric(4) references projekty(id_projektu),
        id_prac numeric(4) references pracownicy(id_prac),
        od date default now(),
        "do" date default now() check ("do" > od),
        stawka numeric(7,2),
        rola char(20) check (rola in ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
        primary key (id_projektu, id_prac)
);
----
--ZAD13
drop table if exists projekty cascade;
create table projekty (
        id_projektu numeric(4) primary key,
        opis_projektu char(20) unique not null,
        data_rozpoczecia date default now(),
        data_zakonczenia date check(data_zakonczenia > data_rozpoczecia),
        fundusz numeric(7, 2)
);
drop table if exists przydzialy cascade;
create table przydzialy (
        id_projektu numeric(4) references projekty(id_projektu),
        id_prac numeric(4) references pracownicy(id_prac),
        od date default now(),
        "do" date default now(),
        stawka numeric(7,2),
        rola char(20) check (rola in ('KIERUJACY', 'ANALITYK', 'PROGRAMISTA')),
        primary key (id_projektu, id_prac)
);
alter table przydzialy add godziny numeric;
----
--ZAD14
----
--ZAD15
drop table if exists projekty cascade;
create table projekty (
  id_projektu numeric(4) primary key,
  opis_projektu char(20) not null,
  data_rozpoczecia date default current_date,
  data_zakonczenia date check( data_rozpoczecia < data_zakonczenia ),
  fundusz numeric(7, 2),
  constraint opu unique(opis_projektu)
);
alter table projekty alter column opis_projektu type char(30);
----
--ZAD16
insert into pracownicy(id_prac, nazwisko) values (121, 'Kok');
----
--ZAD17
alter table pracownicy drop imie
----
--ZAD18
create table pracownicy_zespoly as
(
      select nazwisko, etat, placa_pod * 12 as roczna_placa, nazwa as zespol, adres as adres_pracy
      from pracownicy natural join zespoly
)
----
