SELECT sm.grazinti,
    COUNT(*) AS ta_diena_grazinti
FROM stud.skaitymas sm
GROUP BY sm.grazinti
HAVING COUNT(*) < (
        SELECT AVG(sub.cnt)
        FROM (
                SELECT COUNT(*) AS cnt
                FROM stud.skaitymas
                GROUP BY grazinti
            ) AS sub
    )
ORDER BY COUNT(*) DESC;