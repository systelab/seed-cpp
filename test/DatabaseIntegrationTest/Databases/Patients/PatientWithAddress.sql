BEGIN TRANSACTION;

INSERT INTO Patient (id, name, surname, dob, email, creationTime, updateTime)
VALUES ("1E751CF0-9C20-485E-B0A5-0BE754E74AD9", "Marc", "Robinson", "19861004T102030", "marc@robinson.com", "20200927T091011", "20200927T121314");

INSERT INTO Address (id, patientId, coordinates, street, city, zip)
VALUES (123456, "1E751CF0-9C20-485E-B0A5-0BE754E74AD9", "12.344 N, 78.2323 W", "C/Muntaner, 123 4t 1a", "Barcelona", "08080");

COMMIT TRANSACTION;
