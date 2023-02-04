CREATE EXTENSION pglibpsl;
SELECT psl_regdomain('example.co.uk');
SELECT psl_regdomain('a.example.co.uk');
SELECT psl_regdomain('a.example.co.UK');
SELECT psl_regdomain('');
DROP EXTENSION pglibpsl;
