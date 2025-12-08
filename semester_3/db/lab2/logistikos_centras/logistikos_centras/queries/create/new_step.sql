CREATE OR REPLACE FUNCTION add_step(
    p_id INT,
    p_tikslas_is VARCHAR,
    p_tikslas_i VARCHAR
)
RETURNS VOID AS $$
DECLARE
    last_step zingsnis%ROWTYPE;
BEGIN
    SELECT *
    INTO last_step
    FROM zingsnis
    WHERE paketo_id = p_id
    ORDER BY id DESC
    LIMIT 1;

    IF last_step.ivykdymo_data IS NOT NULL THEN
        RAISE EXCEPTION 'Paketas jau pristatytas';
    END IF;

    IF last_step.tikslas_i <> p_tikslas_is THEN
        RAISE EXCEPTION 'Praeito žingsnio atvykimo vieta nesutampa su naujo žingsnio iškeliavimo vieta';
    END IF;

    UPDATE zingsnis
    SET ivykdymo_data = NOW(),
        busena = 'Įvykdyta'
    WHERE id = last_step.id;

    INSERT INTO zingsnis (paketo_id, tikslas_is, tikslas_i, busena, ivykdymo_data)
    VALUES (p_id,
            p_tikslas_is,
            p_tikslas_i,
            CASE
                WHEN p_tikslas_i = (SELECT galutinis_tikslas FROM paketas WHERE id = p_id)
                THEN 'Įvykdyta'
                ELSE 'Vykdoma'
            END,
            CASE
                WHEN p_tikslas_i = (SELECT galutinis_tikslas FROM paketas WHERE id = p_id)
                THEN NOW()
                ELSE NULL
            END
        );

    IF p_tikslas_i = (SELECT galutinis_tikslas FROM paketas WHERE id = p_id) THEN
        INSERT INTO galutine_busena(paketo_id, data_pristatyta, busena)
        VALUES (p_id, NOW(), NULL)
        ON CONFLICT (paketo_id) DO NOTHING;
    END IF;

END;
$$ LANGUAGE plpgsql;

SELECT add_step(@p_id, @p_tikslas_is, @p_tikslas_i);

REFRESH MATERIALIZED VIEW paketu_ataskaita;