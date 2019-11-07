BEGIN TRANSACTION;

INSERT INTO Patient (id, name, surname, dob, email, creationTime, updateTime)
VALUES ("9055B141-3307-4868-9C81-D5722A5DC16D", "Ibai", "Parker", "20100101T102030", "ibai@patata.com", "20190115T152318", "20190115T152318");
	   
COMMIT TRANSACTION;
