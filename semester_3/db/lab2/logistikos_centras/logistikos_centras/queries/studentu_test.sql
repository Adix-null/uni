 SELECT * 
	FROM pg_catalog.pg_tables 
	WHERE pg_catalog.pg_tables.tableowner <> 'postgres'
	LIMIT 10
;

CREATE TABLE IF NOT EXISTS testas
(
	i INT PRIMARY KEY,
	s VARCHAR(32)
);

INSERT INTO testas (i, s) 
	VALUES 
	(42, 'abc'),
	(-9, 'sdf'),
	(17, 'rq'),
	(73, 'adix')	
;

SELECT * FROM testas;
DROP TABLE testas;