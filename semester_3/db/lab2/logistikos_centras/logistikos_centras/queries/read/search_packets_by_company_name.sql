SELECT pavadinimas, p.id AS paketo_id FROM kompanija k 
    LEFT JOIN paketas p ON p.kompanija = k.pavadinimas
    WHERE pavadinimas = @p_pavadinimas;