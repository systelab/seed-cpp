PRAGMA encoding = "UTF-8";

--
-- Users table
--

CREATE TABLE IF NOT EXISTS 'User' (
  'id' INTEGER NOT NULL,
  'name' TEXT NOT NULL,
  'surname' TEXT NOT NULL,
  'login' TEXT NOT NULL,
  'password' TEXT NOT NULL,
  'role' INTEGER NOT NULL, 
  PRIMARY KEY (id)
);


--
-- Patients table
--

CREATE TABLE IF NOT EXISTS 'Patient' (
  'id' INTEGER NOT NULL,
  'name' TEXT NOT NULL,
  'surname' TEXT NOT NULL,
  'dob' DATETIME NOT NULL,
  'email' TEXT NOT NULL,
  PRIMARY KEY (id)
);


--
-- Addresses table
--

CREATE TABLE IF NOT EXISTS 'Address' (
  'id' INTEGER,
  'patientId' INTEGER NOT NULL,
  'coordinates' TEXT NOT NULL,
  'street' TEXT NOT NULL,
  'city' TEXT NOT NULL,
  'zip' TEXT NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY(patientId) REFERENCES Patient(id) ON DELETE CASCADE ON UPDATE CASCADE
);


