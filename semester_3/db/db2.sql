SELECT vardas, pavarde, grazinti, grazinta
FROM stud.skaitymas, stud.skaitytojas
    WHERE EXTRACT(YEAR FROM CURRENT_DATE) == EXTRACT(YEAR FROM grazinti)
    AND EXTRACT(MONTH FROM CURRENT_DATE) == EXTRACT(MONTH FROM grazinti)
    AND grazinta IS NULL;