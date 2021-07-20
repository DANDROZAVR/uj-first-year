--ZAD1
select nazwa
from produkty
where id_kategoria = (select id_kategoria from produkty where nazwa = 'Piórnik duży')
group by nazwa
----
--ZAD2
select nazwa
from produkty prd
where exists (select * from kategorie where nadkategoria IS NOT null AND id_kategoria = prd.id_kategoria)
----
--ZAD3a
select ktg.nazwa
from kategorie ktg
where (select count(*) id_kategoria from produkty where id_kategoria = ktg.id_kategoria) >= 3
----
--ZAD3b
select (select nazwa from kategorie k where other.id_kategoria = k.id_kategoria)
from produkty other
group by id_kategoria
having count(*) >= 3
order by 1
----
--ZAD3c
select kategorie.nazwa
from kategorie
join produkty using(id_kategoria)
group by id_kategoria
having count(*) >= 3;
----
--ZAD4
select *
from rabaty
where data_do - data_od = (select max(data_do - data_od) from rabaty)
----
--ZAD5
select *
from kategorie kt
where vat < ANY (select vat
                         from kategorie
                         where nadkategoria = kt.id_kategoria)
----
--ZAD6
select id_zamowienia
from zamowienia as prodZam inner join (select id_zamowienia as idzam2, sum(ilosc) as cnt
      from produkty_zamowienia
      group by idzam2) as sec on true
group by id_zamowienia
having sum(case when idzam2 = prodZam.id_zamowienia then cnt else 0 end) = max(cnt)
----
--ZAD7
select nazwa, "liczba zmian"
from produkty as hisc natural join (select sec.kod_produktu, sum(case
                                                                 when extract(month from data_wprowadzenia) = 4 then 1
                                                                 else 0 end) as "liczba zmian"
         from historia_cen as sec
         group by sec.kod_produktu) as "liczba"
where "liczba zmian" > 1
----
--ZAD8
select kt1.nazwa as "nazwa kategorii" , kt10.nazwa as "nazwa najwyższej nadkategorii"
from (
      select nazwa, id_kategoria, case when nadkategoria is null then id_kategoria else (
              select (case when nadkategoria is null then id_kategoria else nadkategoria end)
              from kategorie
              where id_kategoria = kt3.nadkategoria) end as nadkategoria
      from (
              select nazwa, id_kategoria, case when nadkategoria is null then id_kategoria else (
                      select (case when nadkategoria is null then id_kategoria else nadkategoria end)
                      from kategorie
                      where id_kategoria = kt5.nadkategoria) end as nadkategoria
              from (
                      select nazwa, id_kategoria, case when nadkategoria is null then id_kategoria else (
                              select (case when nadkategoria is null then id_kategoria else nadkategoria end)
                              from kategorie
                              where id_kategoria = kt7.nadkategoria) end as nadkategoria
                      from (
                              select nazwa, id_kategoria, case when nadkategoria is null then id_kategoria else (
                                      select (case when nadkategoria is null then id_kategoria else nadkategoria end)
                                      from kategorie
                                      where id_kategoria = kt9.nadkategoria) end as nadkategoria
                              from (
                                                              select nazwa, id_kategoria, case when nadkategoria is null then id_kategoria else (
                                      select (case when nadkategoria is null then id_kategoria else nadkategoria end)
                                      from kategorie
                                      where id_kategoria = kt11.nadkategoria) end as nadkategoria
                                                                      from kategorie kt11
                                                        ) kt9) kt7
              ) kt5
      ) kt3) kt1 join kategorie kt10 on kt10.id_kategoria = kt1.nadkategoria
order by 1, 2
----
--ZAD9
select produkty.nazwa, ROUND((cena_netto * (1 + vat/100)), 2)
from historia_cen hs natural join produkty
                                   join kategorie using (id_kategoria)
where data_wprowadzenia = (select max(data_wprowadzenia) from historia_cen where hs.kod_produktu = kod_produktu)
----
--ZAD10
select produkty.nazwa,
    ROUND(cena_netto * (1 + vat/100) -
              coalesce(
                      (select sum(znizka)
                      from rabaty natural join rabaty_produkty
                      where data_od <= data_wprowadzenia AND data_do >= data_wprowadzenia AND id_produktu = kod_produktu)::numeric,
                  0),
      2)
from historia_cen hs natural join produkty
                                   join kategorie using (id_kategoria)
where data_wprowadzenia = (select max(data_wprowadzenia) from historia_cen where hs.kod_produktu = kod_produktu)
----
--ZAD11
select id_zamowienia, ROUND(sum(cena_netto * (1 + vat/100) * ilosc), 2)
from zamowienia
      natural join produkty_zamowienia
      join produkty on produkt=kod_produktu
      join kategorie using(id_kategoria)
      join historia_cen using (kod_produktu)
where data_wprowadzenia = (select max(case when data_wprowadzenia <= data_zlozenia then data_wprowadzenia else '1901-01-01' end)
                                                 from historia_cen hc
                                                 where hc.kod_produktu = produkt)
group by id_zamowienia
----
--ZAD12
select id_zamowienia,
ROUND(
      sum(
              (cena_netto * (1 + vat/100) * ilosc -
                      coalesce(
                              (select sum(znizka)
                              from rabaty natural join rabaty_produkty
                              where id_produktu=produkt AND ilosc >= min_ilosc AND data_zlozenia >= data_od AND data_zlozenia <= data_do)
                      , 0)
                        )
      )
      -
      coalesce(
              (select sum(znizka)
              from rabaty natural join rabaty_klienci as rk
              where rk.id_zamowienia = zam.id_zamowienia AND data_zlozenia >= data_od AND data_zlozenia <= data_do)
              , 0)
, 2)
from zamowienia as zam
      natural join produkty_zamowienia
      join produkty on produkt=kod_produktu
      join kategorie using(id_kategoria)
      join historia_cen using (kod_produktu)
where data_wprowadzenia = (select max(case when data_wprowadzenia <= data_zlozenia then data_wprowadzenia else '1901-01-01' end)
                                                 from historia_cen hc
                                                 where hc.kod_produktu = produkt)
 
group by id_zamowienia
----
