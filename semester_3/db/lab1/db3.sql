SELECT 
    a.vardas || ' ' || a.pavarde AS a_vardas_pav,
    k.leidykla,
    COUNT(DISTINCT e.nr) AS egzemplioriu_kiekis,
    COUNT(CASE WHEN sm.grazinta IS NULL THEN sm.nr END) AS skaitytoju_kiekis,
    SUM(DISTINCT k.verte) * COUNT(DISTINCT e.nr) as verte_sum
	FROM stud.autorius a
	JOIN stud.knyga k ON a.isbn = k.isbn
	JOIN stud.egzempliorius e ON k.isbn = e.isbn
	LEFT JOIN stud.skaitymas sm ON sm.egzempliorius = e.nr
	GROUP BY a_vardas_pav, k.leidykla
		HAVING COUNT(DISTINCT e.nr) > 2
	ORDER BY a_vardas_pav ASC
;
