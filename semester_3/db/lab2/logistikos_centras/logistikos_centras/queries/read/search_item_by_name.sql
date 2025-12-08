SELECT * FROM preke
    WHERE pavadinimas LIKE '%' || @p_pavadinimas || '%';