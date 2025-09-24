SELECT a.vardas, a.pavarde, k.pavadinimas, e.nr
FROM stud.skaitytojas st, stud.skaitymas s
LEFT JOIN stud.egzempliorius e
	ON s.nr = e.nr
LEFT JOIN stud.knyga k
	ON e.isbn = k.isbn
LEFT JOIN stud.autorius a
	ON k.isbn = a.isbn
WHERE
    EXTRACT(YEAR FROM CURRENT_DATE) = EXTRACT(YEAR FROM s.grazinti)
    AND  EXTRACT(MONTH FROM s.grazinti) = 10
    AND s.grazinta IS NULL;

-- 2.1
-- SELECT st.vardas, st.pavarde
-- FROM stud.skaitytojas st
-- LEFT JOIN stud.skaitymas s
--    ON s.skaitytojas = st.nr
-- WHERE s.nr IS NULL;
