BEGIN TRANSACTION;

INSERT INTO Allergy (id, creationTime, updateTime, name, signs, symptoms)
VALUES ("73A800FC-621C-4D94-A1A4-0B39075458D4", "20170212T093045", "20190115T152318", "Tree Nuts", "Raised red bumps of skin", "Abdominal pain, cramps, nausea and vomiting");

COMMIT TRANSACTION;