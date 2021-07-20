--ZAD1
select * from zespoly order by 1,2,3
----
--ZAD2
select * from pracownicy order by 1
----
--ZAD3
select nazwisko, etat, placa_pod * 12 from pracownicy order by 1, 2, 3
----
--ZAD4
select nazwisko, placa_pod + coalesce(placa_dod, 0) from pracownicy order by 1, 2
----
--ZAD5
select * from zespoly order by 2, 1, 3
----
--ZAD6
select etat from pracownicy group by etat order by 1
----
--ZAD7
select * from pracownicy where etat like 'ASYSTENT' order by 1
----
--ZAD8
select * from pracownicy where id_zesp in ('20', '30') ORDER BY placa_pod DESC
----
--ZAD9
select * from pracownicy where placa_pod between 300 and 1800 order by 1
----
--ZAD10
select * from pracownicy where nazwisko like '%ski' order by 1
----
--ZAD11
select * from pracownicy where placa_pod >= 2000 AND id_szefa IS NOT NULL order by 1
----
--ZAD12
select nazwisko, zatrudniony, etat from pracownicy where zatrudniony between '1992-01-01' AND '1993-12-31' order by 1, 2
----
--ZAD13
select * from pracownicy where placa_dod > 500 order by etat, nazwisko
----
--ZAD14
select nazwisko || ' pracuje od ' || zatrudniony || ' i zarabia ' || placa_pod AS "PROFESOROWIE" from pracownicy
where nazwisko in ('Nowak', 'Janicki', 'Kowalski', 'Nowicki') order by placa_pod DESC
----
--ZAD15
select nazwisko, ROUND(placa_pod * 1.15, 0) from pracownicy order by 1, 2
----
--ZAD16
select CONCAT(RPAD(nazwisko, 20, '.'), LPAD(etat, 20, '.')) as "nazwisko i etat" from pracownicy order by id_prac
----
--ZAD17
select CONCAT(substring(etat, 1, 2), id_prac), id_prac, nazwisko, etat from pracownicy order by 1
----
--ZAD18
select nazwisko, REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(nazwisko, 'K', 'X'), 'k', 'X'), 'L', 'X'), 'l', 'X'), 'M', 'X')
, 'm', 'X') from pracownicy order by 1
----
--ZAD19
select nazwisko, CONCAT(CONCAT(CONCAT(RPAD(TO_CHAR(zatrudniony, 'Month'), 9, ' '), ', '),
LPAD(cast(extract(day from zatrudniony) as varchar), 2, '0'), ' '), extract(year from zatrudniony))
as data_zatrudnienia from pracownicy where id_zesp = 20 order by id_prac
----
--ZAD20
select to_char(now(), 'Day');
----
--ZAD21
select id_prac,
CASE
   WHEN placa_pod > 1850 THEN 'wiecej'
   WHEN placa_pod = 1850 THEN 'rowna'
   ELSE 'mniej'
END
from pracownicy order by 1
----
--ZAD22
SELECT imie, nazwisko, placa_dod FROM pracownicy ORDER BY placa_dod DESC NULLS LAST, id_prac
----
