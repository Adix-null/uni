SELECT 
    c.table_schema,
    c.table_name,
    c.column_name,
    t.oid AS type_oid
FROM information_schema.columns c
JOIN pg_type t ON t.typname = c.udt_name
WHERE c.table_name = 'autorius' OR 
c.table_name = 'knyga' OR
c.table_name = 'egzempliorius' OR
c.table_name = 'skaitymas' OR
c.table_name = 'skaitytojas'
ORDER BY c.table_name
;