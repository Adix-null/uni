SELECT DISTINCT a.vardas, a.pavarde, k.pavadinimas, k.verte, e.nr AS egzemplioriaus_numeris
FROM stud.skaitytojas st, stud.skaitymas s
LEFT JOIN stud.egzempliorius e
	ON s.egzempliorius = e.nr
LEFT JOIN stud.knyga k
	ON e.isbn = k.isbn
LEFT JOIN stud.autorius a
	ON k.isbn = a.isbn
WHERE
    EXTRACT(YEAR FROM CURRENT_DATE) = EXTRACT(YEAR FROM s.grazinti)
    AND  EXTRACT(MONTH FROM s.grazinti) = 10
    AND s.grazinta IS NULL
    ORDER BY vardas ASC;

-- 2.1
-- SELECT st.vardas, st.pavarde
-- FROM stud.skaitytojas st
-- LEFT JOIN stud.skaitymas s
--    ON s.skaitytojas = st.nr
-- WHERE s.nr IS NULL;
