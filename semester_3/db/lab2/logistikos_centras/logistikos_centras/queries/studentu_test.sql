 SELECT * 
	FROM pg_catalog.pg_tables 
	WHERE pg_catalog.pg_tables.tableowner <> 'postgres'
	ORDER BY pg_catalog.pg_tables.tableowner
;

CREATE TABLE IF NOT EXISTS adbtestas
(
	i INT PRIMARY KEY,
	s VARCHAR(32)
);

INSERT INTO adbtestas (i, s) 
	VALUES 
	(42, 'abc'),
	(-9, 'sdf'),
	(17, 'rq'),
	(73, 'adix')	
;

SELECT * FROM adbtestas;
DROP TABLE adbtestas;