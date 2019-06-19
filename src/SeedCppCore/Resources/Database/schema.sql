PRAGMA encoding = "UTF-8";

--
-- User table
--
CREATE TABLE IF NOT EXISTS 'User' (
  'id' TEXT NOT NULL,
  'name' TEXT NOT NULL,
  'surname' TEXT NOT NULL,
  'login' TEXT NOT NULL,
  'password' TEXT NOT NULL,
  'role' INTEGER NOT NULL,
  'creationTime' DATETIME NOT NULL,
  'updateTime' DATETIME NOT NULL,
  PRIMARY KEY (id)
);


--
-- Patient table
--
CREATE TABLE IF NOT EXISTS 'Patient' (
  'id' TEXT NOT NULL,
  'name' TEXT NOT NULL,
  'surname' TEXT NOT NULL,
  'dob' DATETIME DEFAULT NULL,
  'email' TEXT NOT NULL,
  'creationTime' DATETIME NOT NULL,
  'updateTime' DATETIME NOT NULL,
  PRIMARY KEY (id)
);


--
-- Address table
--
CREATE TABLE IF NOT EXISTS 'Address' (
  'id' INTEGER NOT NULL,
  'patientId' TEXT NOT NULL,
  'coordinates' TEXT NOT NULL,
  'street' TEXT NOT NULL,
  'city' TEXT NOT NULL,
  'zip' TEXT NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY(patientId) REFERENCES Patient(id) ON DELETE CASCADE ON UPDATE CASCADE
);


--
-- Allergy table
--
CREATE TABLE IF NOT EXISTS 'Allergy' (
  'id' TEXT NOT NULL,
  'name' TEXT NOT NULL,
  'signs' TEXT NOT NULL,
  'symptoms' TEXT NOT NULL,
  'creationTime' DATETIME NOT NULL,
  'updateTime' DATETIME NOT NULL,
  PRIMARY KEY (id)
);

--
-- PatientAllergy table
--
CREATE TABLE IF NOT EXISTS 'PatientAllergy' (
  'id' TEXT NOT NULL,
  'patientId' TEXT NOT NULL,
  'allergyId' TEXT NOT NULL,
  'lastOcurrence' DATETIME NOT NULL,
  'assertedDate' DATETIME NOT NULL,
  'creationTime' DATETIME NOT NULL,
  'updateTime' DATETIME NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (patientId) REFERENCES Patient(id) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (allergyId) REFERENCES Allergy(id) ON DELETE RESTRICT ON UPDATE RESTRICT
);