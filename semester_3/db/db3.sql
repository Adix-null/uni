SELECT vardas, pavarde, leidykla, COUNT(*) AS egzemplioriu_skaicius
	FROM stud.autorius a
	LEFT JOIN stud.knyga k
		ON a.isbn = k.isbn
	LEFT JOIN stud.egzempliorius e
		ON k.isbn = e.isbn
	GROUP BY leidykla, vardas, pavarde
	ORDER BY egzemplioriu_skaicius DESC;