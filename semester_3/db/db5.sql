SELECT c.table_name AS view_name,
    c.data_type,
    COUNT(*) AS column_count
FROM information_schema.columns c
    JOIN information_schema.views v ON c.table_name = v.table_name
WHERE c.table_schema = 'stud'
    AND c.data_type = 'character'
GROUP BY c.table_name,
    c.data_type
ORDER BY column_count DESC
LIMIT 1;