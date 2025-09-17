SELECT ak, 
vardas || ' ' || pavarde AS vardas_ir_pavarde, 
EXTRACT(YEAR FROM AGE(CURRENT_DATE, Gimimo_data)) AS Metai
        FROM stud.skaitytojas 
        WHERE Gimimo_data < CURRENT_DATE - INTERVAL '20 years'
        AND LOWER(vardas) LIKE '%ta%' 
        ORDER BY pavarde DESC ; 
