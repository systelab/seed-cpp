BEGIN TRANSACTION;

INSERT INTO User (id, name, surname, login, password, role, creationTime, updateTime)
VALUES ("73A800FC-621C-4D94-A1A4-0B39075458D4", "John", "Smith", "jsmith",	"P@assw0rd", 1, "20170212T093045", "20190115T152318");

COMMIT TRANSACTION;
