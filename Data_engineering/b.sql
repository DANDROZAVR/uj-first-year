--ZAD1
select ROUND(min(cena_netto * (1 + vat/ 100)), 2) as min, ROUND(max(cena_netto * (1 + vat/ 100)), 2) as max from produkty order by 1, 2
----
--ZAD2
select id_zamowienia, sum(ilosc) from produkty_zamowienia group by id_zamowienia order by 1, 2
----
--ZAD3
select produkt from produkty_zamowienia group by produkt having sum(ilosc) >= 50 order by 1
----
--ZAD4
select kategoria, ROUND(AVG(waga), 2) from produkty GROUP BY kategoria HAVING COUNT(*) >= 2 order by 2 DESC, 1 ASC
----
--ZAD5
select kategoria, min(cena_netto), max(cena_netto), max(cena_netto) - min(cena_netto) from produkty GROUP BY kategoria order by 1, 2, 3
----
--ZAD6
select kategoria, sum(case vat when '18.0' then 0 else 1 end) AS "liczba produktow" from produkty GROUP BY kategoria order by 1, 2
----
--ZAD7
select sum(case when waga < 1000 then 1 else 0 end) as "liczba produktow" from produkty order by 1
----
--ZAD8
select
      CASE
              WHEN max(cena_netto) >= 300 then sum(cena_netto)
      END as sum
from produkty
----
--ZAD9
select
      CASE
              when count(distinct adres_dostawy) = count(adres_dostawy) then 'TAK' else 'NIE'
      END
from zamowienia
----
--ZAD10
select id_klienta from zamowienia group by id_klienta having count(id_zamowienia) > 1 order by 1
----
--ZAD11
select kategoria from produkty group by kategoria having count(rabat) = count(*) order by 1
----
--ZAD12
select kategoria from produkty where vat = 8 group by kategoria having count(rabat) = count(*) order by 1
----
--ZAD13
select kategoria, COALESCE(ROUND(VARIANCE(cena_netto), 2), 0.00) as wariancja, COALESCE(ROUND(SQRT(VARIANCE(cena_netto)), 2), 0.00)
as "odchylenie standardowe" from produkty group by kategoria order by 1, 2, 3
----
--ZAD14
select sum(case when kategoria = 'Artykuły papiernicze' then 1 else 0 end) from produkty order by 1
----
--ZAD15a
select CONCAT('{"', CONCAT(string_agg("numer_telefonu", '","'), '"}')) as "lista telefonów" from klienci where numer_telefonu IS NOT null
----
--ZAD15b
select array_agg(numer_telefonu order by numer_telefonu) as "lista telefonów" from klienci where numer_telefonu IS NOT null
----
--ZAD16
select produkt, count(*) from produkty_zamowienia group by produkt order by 2 DESC, 1 ASC
----
--ZAD17
select (case when nip IS null then 'Brak' else 'Podany' end) as "NIP", COUNT(*) as "liczba klientow" from klienci
group by "NIP" order by 1
----
--ZAD18
select COUNT(*) as "liczba klientów" from klienci where split_part(email, '@', 2) = 'gmail.com'
----
--ZAD19
select TO_CHAR(data_zlozenia, 'Month') as "Miesiac", COUNT(*) as "Liczba zamowien" from zamowienia group by "Miesiac" order by 1
----
