BEGIN TRANSACTION;

--
-- User table
--
INSERT INTO User
	(id, name, surname, login, password, role, creationTime, updateTime)
VALUES
	("73A800FC-621C-4D94-A1A4-0B39075458D4", "John", "Smith", "jsmith",	"P@assw0rd", 1, "20170212T093045", "20190115T152318"),
 	("9055B141-3307-4868-9C81-D5722A5DC16C", "Peter", "Parker", "pparker", "SuperSecret!", 0, "20180101T102030", "20190115T152318"),
	("4DBF18D0-689B-4974-B727-5CA503709E8E", "Kevin", "Robinson", "krobinson", "Ph2d3ghI7h", 0, "20180724T184500", "20191213T235959");


--
-- Patient table
--
INSERT INTO Patient
	(id, name, surname, dob, email, creationTime, updateTime)
VALUES
	("10010AC9-CCE0-4251-82F8-44791BD42C27", "Joseph", "Traver", "20100101T102030", "jtraver@gmail.com", "20190115T152318", "20190115T152318"),
	("13E698FB-4E44-44CB-AA07-DA26FA1B0FFC", "Leonardo", "Flangan", NULL, "lflanagan@msn.com", "20190115T152318", "20190115T152318"),
	("DB0570DD-3421-42E2-9C8F-99556C6849C0", "Phillip", "Froome", NULL, "pfroome@hotmail.com", "20190115T152318", "20190115T152318");


--
-- Address table
--


COMMIT TRANSACTION;
