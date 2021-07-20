--ZAD1
select produkty.nazwa, klienci.nazwa
from klienci, produkty
where email IS NOT null AND split_part(kategoria, ' ', 1) = 'Artykuły'
order by 1, 2
----
--ZAD2
select klienci.nazwa, z.data_zlozenia
from klienci NATURAL JOIN zamowienia z
where klienci.nip IS NOT null
order by 1, 2
----
--ZAD3
select p.nazwa
from produkty_zamowienia JOIN zamowienia z ON z.id_zamowienia = produkty_zamowienia.id_zamowienia
JOIN produkty p ON p.kod_produktu = produkt
where split_part(adres_dostawy, ' ', 2) = 'Kubusia' AND split_part(adres_dostawy, ' ', 3) = 'Puchatka'
group by p.nazwa
order by 1
----
--ZAD4
select klienci.nazwa as "nazwa klienta",
      CASE
              when count(distinct adres_dostawy) > 1 then 'TAK' else 'NIE'
      END as "rozne adresy"
from klienci left join zamowienia using(id_klienta)
group by klienci.id_klienta
order by 1
----
--ZAD5
select p1.nazwa, p2.nazwa
from produkty as p1 inner join produkty as p2
on p1.cena_netto * (1 + p1.vat/ 100) < p2.cena_netto * (1 + p2.vat/ 100)
group by p1.nazwa, p2.nazwa
order by 1, 2
----
--ZAD6
select klienci.nazwa, klienci.email
from zamowienia NATURAL JOIN klienci
where extract(month from data_zlozenia) = 3
group by klienci.nazwa, klienci.email
order by 1
----
--ZAD7a
SELECT kl1.nazwa, kl2.nazwa
FROM rabaty_klientow NATURAL JOIN rabaty NATURAL JOIN klienci AS kl1 JOIN klienci kl2 ON kl2.id_klienta = id_polecajacego
WHERE id_polecajacego IS NOT null
order by 1, 2
----
--ZAD7b
SELECT kl1.nazwa, kl2.nazwa
FROM rabaty_klientow NATURAL JOIN klienci AS kl1 LEFT OUTER JOIN klienci kl2 ON kl2.id_klienta = id_polecajacego
order by 1, 2
----
--ZAD8
SELECT kl2.*
FROM rabaty_klientow as rb RIGHT JOIN klienci kl2 ON kl2.id_klienta = rb.id_klienta
WHERE rb.id_klienta IS null
order by 1
----
--ZAD9
select nazwa
from rabaty_produktow natural join rabaty join produkty on produkt = kod_produktu
where min_ilosc = 1
order by 1
----
--ZAD10
select min(kl.id_klienta) as id_klienta, min(kl.nazwa) as nazwa, min(kl.numer_telefonu) as numer_telefonu, min(kl.email) as email,
min(kl.nip) as nip, zm.id_zamowienia, ROUND(sum(prod.cena_netto * ilosc), 2) as "wartosc_zamowienia"
from klienci as kl
join zamowienia zm using(id_klienta)
join produkty_zamowienia przam using(id_zamowienia)
join produkty prod on prod.kod_produktu = przam.produkt
where kl.nazwa = 'Urząd Skarbowy w Radomiu'
group by zm.id_zamowienia
order by "wartosc_zamowienia" DESC, id_zamowienia ASC
----
--ZAD11
select zam.id_zamowienia
from rabaty_klientow as rk join zamowienia zam on zam.id_klienta = rk.id_klienta
group by id_zamowienia
order by 1
----
--ZAD12
select kl.nazwa as klient, sum(case when ilosc is null then 0 else ilosc end) as "liczba produktow"
from klienci as kl left join zamowienia zam on kl.id_klienta = zam.id_klienta left join produkty_zamowienia prodzam on
prodzam.id_zamowienia = zam.id_zamowienia
group by kl.id_klienta
order by 1, 2
----
--ZAD13
select kl.nazwa as klient, sum(case when ilosc is null then 0 else ilosc end) as "liczba produktow"
from klienci as kl natural join zamowienia natural join produkty_zamowienia prodzam
join produkty prod on prod.kod_produktu = prodzam.produkt AND prod.waga > 1000
group by kl.id_klienta
order by 1, 2
----
--ZAD14
select kl.nazwa as klient, count(distinct id_zamowienia) as "liczba zamowien"
from klienci as kl left join zamowienia zam on kl.id_klienta = zam.id_klienta
group by kl.id_klienta
order by 2 DESC, 1 ASC
----
--ZAD15
select id_rabatu, znizka, (case when id_klienta is null then 'RABAT PRODUKTU' else 'RABAT KLIENCKI' end) as "typ rabatu"
from rabaty left join rabaty_klientow rabk using(id_rabatu) left join rabaty_produktow rabp using(id_rabatu)
order by 1
----
--ZAD16
select (case when sum(case when tab2.id_klienta is null then 0 else 1 end) > 0 then 'TAK' else 'NIE' end) as "bycia poleconym przez"
from rabaty_klientow as tab1 left join rabaty_klientow tab2 on tab1.id_polecajacego = tab2.id_klienta AND tab2.id_polecajacego = tab1.id_klienta
group by tab1.id_klienta + null
----
--ZAD17
select id_zamowienia, max(ilosc)
from zamowienia natural join produkty_zamowienia
group by id_zamowienia
order by 2 DESC, 1 ASC
----
