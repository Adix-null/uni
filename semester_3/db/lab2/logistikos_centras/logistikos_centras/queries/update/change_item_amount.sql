UPDATE paketo_preke
    SET kiekis = @p_kiekis
    WHERE paketo_id = @p_paketo_id AND prekes_id = @p_prekes_id;