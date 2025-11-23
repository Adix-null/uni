CREATE TABLE IF NOT EXISTS paketas
(
	id 					INT 						BY DEFAULT AS IDENTITY PRIMARY KEY,
	kilmes_salis 		VARCHAR(2)								DEFAULT 'XX',
	galutinis_tikslas 	VARCHAR(64) 	NOT NULL,
	data_sukurta 		DATE 			NOT NULL				DEFAULT NOW(),
	kompanija 			VARCHAR(64) 	NOT NULL 	REFERENCES kompanija(pavadinimas) 
);

CREATE TABLE IF NOT EXISTS kompanija
(
    pavadinimas 		VARCHAR(64) 				PRIMARY KEY CHECK (pavadinimas ~ '^[A-Z]'), /* Pirma raidė didžioji */
    limitas_kg 			DECIMAL(9,1) 	NOT NULL 				CHECK (limitas_kg > 0),
    eur_uz_kg 			DECIMAL(9,2) 	NOT NULL 				CHECK (eur_uz_kg > 0)
);

CREATE TABLE IF NOT EXISTS galutine_busena
(
	paketo_id 			INT 						PRIMARY KEY REFERENCES paketas(id),
	data_pristatyta 	TIMESTAMP 		NOT NULL				DEFAULT NOW(),
	busena 				INT 			NOT NULL 				CHECK (busena IN (1, 2, 3, 4, 5))
);

CREATE TABLE IF NOT EXISTS zingsnis
(
	id 					INT 						BY DEFAULT AS IDENTITY PRIMARY KEY,
	paketo_id 			INT 			NOT NULL	REFERENCES paketas(id),
	tikslas_is 			VARCHAR(64) 	NOT NULL,
	tikslas_i 			VARCHAR(64) 	NOT NULL,
	busena 				VARCHAR(64) 	NOT NULL,
	ivykdymo_data 		DATE,
);

CREATE TABLE IF NOT EXISTS paketo_preke
(
	paketo_id 			INT 						PRIMARY KEY REFERENCES paketas(id),
	prekes_id 			INT 						PRIMARY KEY REFERENCES preke(id),
	kiekis 				INT 			NOT NULL				CHECK (kiekis > 0)
);

CREATE TABLE IF NOT EXISTS preke
(
	id 					INT 						BY DEFAULT AS IDENTITY PRIMARY KEY,
	pavadinimas 		VARCHAR(64) 	NOT NULL,
    kaina_eur 			DECIMAL(9,2) 	NOT NULL 				CHECK (eur_uz_kg > 0),
    svoris_kg 			DECIMAL(9,1) 	NOT NULL 				CHECK (limitas_kg > 0)
);
