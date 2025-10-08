SELECT sm.grazinti, COUNT(*) AS ta_diena_grzinti
FROM stud.skaitymas sm
GROUP BY sm.grazinti
    HAVING COUNT(*) < sub.sm_avg = (SELECT AVG(*) as sm_avg
           FROM stud.skaitymas
           GROUP BY sm_avg
    ) AS sub
ORDER BY sm.grazinti;