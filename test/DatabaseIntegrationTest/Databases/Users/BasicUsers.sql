BEGIN TRANSACTION;

INSERT INTO User (id, name, surname, login, password, role, creationTime, updateTime)
VALUES ("9055B141-3307-4868-9C81-D5722A5DC16C", "Peter", "Parker", "pparker", "SuperSecret!", 0, "20180101T102030", "20190115T152318"),
       ("4DBF18D0-689B-4974-B727-5CA503709E8E", "Kevin", "Robinson", "krobinson", "Ph2d3ghI7h", 0, "20180724T184500", "20191213T235959");

COMMIT TRANSACTION;
