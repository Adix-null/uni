--egzemplioriu kiekis
SELECT a.vardas || ' ' || a.pavarde AS a_vardas_pav,
leidykla, COUNT(a.vardas) AS egzemplioriu_skaicius
	FROM stud.autorius a
	LEFT JOIN stud.knyga k
		ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e
		ON k.isbn = e.isbn
	GROUP BY leidykla, a_vardas_pav
	HAVING COUNT(a.vardas) > 2
	ORDER BY egzemplioriu_skaicius DESC
;
--skaitytoju tiems egzemplioriams kiekis
SELECT a.vardas || ' ' || a.pavarde AS a_vardas_pav,
leidykla, COUNT(sm.nr) as skaitytoju_kiekis
	FROM stud.autorius a
	LEFT JOIN stud.knyga k
		ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e
		ON k.isbn = e.isbn
	INNER JOIN stud.skaitymas sm
		ON sm.egzempliorius = e.nr		
	WHERE sm.grazinta IS NULL
	GROUP BY a_vardas_pav, leidykla	
	ORDER BY a_vardas_pav ASC
;

--egzemplioriu sumine verte
SELECT a.vardas || ' ' || a.pavarde AS a_vardas_pav,
leidykla,
SUM(k.verte) AS bendra_verte
	FROM stud.autorius a
	LEFT JOIN stud.knyga k
		ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e
		ON k.isbn = e.isbn
	GROUP BY a_vardas_pav, leidykla
	ORDER BY a_vardas_pav ASC
;
