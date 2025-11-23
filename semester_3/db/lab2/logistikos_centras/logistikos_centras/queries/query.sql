 SELECT * 
	 FROM pg_catalog.pg_tables 
	 WHERE pg_catalog.pg_tables.tableowner <> 'postgres'
	 LIMIT 10;
