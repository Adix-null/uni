SELECT a.vardas || ' ' || a.pavarde AS a_vardas_pav, 
leidykla, e.nr,
sj.vardas || ' ' || sj.pavarde AS sj_vardas_pav
	FROM stud.autorius a
	LEFT JOIN stud.knyga k
		ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e
		ON k.isbn = e.isbn
	LEFT JOIN stud.skaitymas sm
		ON sm.egzempliorius = e.nr
	LEFT JOIN stud.skaitytojas sj
		ON sm.skaitytojas = sj.nr
;