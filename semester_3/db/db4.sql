WITH bendras AS 
(
    SELECT grazinti, 
        COUNT(*) AS ta_diena_grazinti,
        AVG(COUNT(*)) OVER () AS graz_vid,
        RANK () OVER (ORDER BY COUNT(*) DESC) AS rankas
    FROM stud.skaitymas
    GROUP BY grazinti
)
SELECT grazinti, ta_diena_grazinti, rankas
FROM bendras
WHERE rankas < 6
ORDER BY ta_diena_grazinti DESC;
