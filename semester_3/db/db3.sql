SELECT 
    a.vardas || ' ' || a.pavarde AS a_vardas_pav,
    k.leidykla,
    COUNT(DISTINCT e.nr) AS egzemplioriu_kiekis,
    COUNT(DISTINCT CASE WHEN sm.grazinta IS NULL THEN sm.nr END) AS skaitytoju_kiekis
	FROM stud.autorius a
	LEFT JOIN stud.knyga k ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e ON k.isbn = e.isbn
	LEFT JOIN stud.skaitymas sm ON sm.egzempliorius = e.nr
	GROUP BY a_vardas_pav, k.leidykla
		HAVING COUNT(DISTINCT e.nr) > 2
	ORDER BY a_vardas_pav ASC
;
