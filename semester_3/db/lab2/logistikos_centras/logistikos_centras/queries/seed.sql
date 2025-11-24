INSERT INTO kompanija VALUES
    ('Intera',      2.5,    1.74),
    ('Miderum',     7.3,    2.17),
    ('Ganytojai',   22.8,   2.81),
    ('Gigantus',    10000,  5.00)
;

INSERT INTO paketas (kilmes_salis, galutinis_tikslas, data_sukurta, kompanija) VALUES
    ('CN', 'Lietuva, Prienai, 01276',       '2025-11-22',   'Intera'),
    ('LT', 'Lenkija, Varšuva, 181-14695',   '2025-11-12',   'Intera'),
    ('AU', 'JAV, Harrison, NJ-27346',       '2025-09-28',   'Ganytojai'),
    ('CL', 'Kinija, Chongqing, 7A-07294',   '2025-10-15',   'Gigantus')
;

INSERT INTO galutine_busena VALUES
    (2, '2025-11-16 14:34:51', 5)
;
REFRESH MATERIALIZED VIEW pristatyti_paketai;

INSERT INTO preke (pavadinimas, kaina_eur, svoris_kg) VALUES
    ('Smart water bottle',      8.50,   0.1),
    ('USB LED Light',           5.99,   0.2),
    ('Hoodie - Black',          19.90,  0.8),
    ('Bolts 50pcs',             12.40,  1.7),
    ('Plastic Housing Shell',   475.54, 14.1),
    ('Lithium 4 metric tons',   80000,  4000)
;

INSERT INTO paketo_preke VALUES
    (1, 1, 2),
    (1, 2, 1),
    (1, 4, 1),
    (2, 3, 1),
    (3, 4, 3),
    (3, 5, 5),
    (4, 6, 2)
;

INSERT INTO zingsnis (paketo_id, tikslas_is, tikslas_i, busena, ivykdymo_data) VALUES
    (1, 'Guangzhou sorting center',             'Port of Guangzhou',            'Įvykdyta',     '2025-11-23'),
    (1, 'Port of Guangzhou',                    'Klaipėdos uostas',             'Vykdoma',       NULL),

    (2, 'Vilniaus Intera logistikos centras',   'Varšuvos Intera sandėlis',     'Įvykdyta',     '2025-11-13'),
    (2, 'Varšuvos Intera sandėlis',             'Pašto punktas 12',             'Įvykdyta',     '2025-11-15'),
    (2, 'Pašto punktas 12',                     'Lenkija, Varšuva, 181-14695',  'Įvykdyta',     '2025-11-16'),

    (3, 'Perth manufactoring company',          'Perth airport',                'Įvykdyta',     '2025-10-04'),
    (3, 'Perth airport',                        'Port of LA',                   'Nepradėta',    NULL),

    (4, 'Santiago ore processor',               'Port of Arica',                'Įvykdyta',     '2025-10-26'),
    (4, 'Port of Arica',                        'Shenzhen dry dock',            'Vykdoma',      NULL)
;

