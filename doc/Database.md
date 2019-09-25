# Database

Model entities of `seed-cpp` project shall be persisted into a SQL relational database which each model entity shall be persisted in its own table. Moreover, the contents of the database shall be stored in a single file with [SQLite](https://www.sqlite.org) format and encrypted using [sqleet](https://github.com/resilar/sqleet) encryption scheme.


## Tables

### User table

The **User** table contains information of the users registered in the application as well as their credentials and profile.

#### Columns

| Name         | Data Type| Not NULL | Description                                             |
|--------------|:--------:|:--------:|:--------------------------------------------------------|
| id           | Text     | &#x2713; | User record internal identifier in the form of a [UUID](https://en.wikipedia.org/wiki/Universally_unique_identifier).|
| name         | Text     | &#x2713; | Name of the user.                                       |
| surname      | Text     | &#x2713; | Surname of the user.                                    |
| login        | Text     | &#x2713; | Login name of the user.                                 |
| password     | Text     | &#x2713; | User password, encrypted using [SHA-256](https://en.wikipedia.org/wiki/SHA-2) algorithm. |
| role         | Integer  | &#x2713; | Identifier of the role assigned to user.                |
| creationTime | Datetime | &#x2713; | Timestamp of the moment when the user was created.      |
| updateTime   | Datetime | &#x2713; | Timestamp of the moment when the user was last updated. |


#### Integrity constraints

* **Primary key** is defined over `id` column
* Values for `login` column shall be **unique**

#### Role column values

The **role** column can take one of the following values:

| ID | Role name     | Description                                                  |
|:--:|---------------|:-------------------------------------------------------------|
| 0  | Administrator | User with privileges to perform all the available operations |
| 1  | Operator      | Basic user with limited privileges                           |


### Patient table

The **Patient** table contains information of the basic data of the patients registered in the application.

#### Columns

| Name         | Data Type| Not NULL | Description                                                  |
|--------------|:--------:|:--------:|:-------------------------------------------------------------|
| id           | Text     | &#x2713; | Patient record internal identifier in the form of a [UUID](https://en.wikipedia.org/wiki/Universally_unique_identifier).|
| name         | Text     | &#x2713; | Name of the patient.                                         |
| surname      | Text     | &#x2713; | Surname of the patient.                                      |
| dob          | Datetime |          | Date of birth of the patient. Time shall be set to 00:00:00. |
| email        | Text     | &#x2713; | Email address of the patient.                                |
| creationTime | Datetime | &#x2713; | Timestamp of the moment when the patient was created.        |
| updateTime   | Datetime | &#x2713; | Timestamp of the moment when the patient was last updated.   |


#### Integrity constraints

* **Primary key** is defined over `id` column
* Combinations of values for `name` and `surname` columns shall be **unique**


### Address table

The **Address** table contains the details of the addresses of each one of the patients of the application.

#### Columns

| Name         | Data Type| Not NULL | Description                                       |
|--------------|:--------:|:--------:|:--------------------------------------------------|
| id           | Integer  | &#x2713; | Address record unique internal identifier.        |
| patientId    | Text     | &#x2713; | UUID of the patient that has this address.        |
| coordinates  | Text     | &#x2713; | Geographical coordinates.                         |
| street       | Text     | &#x2713; | Street name.                                      |
| city         | Text     | &#x2713; | City name.                                        |
| zip          | Text     | &#x2713; | ZIP code.                                         |

#### Integrity constraints

* **Primary key** is defined over `id` column
* **Foreign key** defined over `patientId` column referencing column `id` of `Patient` table

### Allergy table

The **Allergy** table contains the data about all the allergies registered on the application.

#### Columns

| Name         | Data Type| Not NULL | Description                                                  |
|--------------|:--------:|:--------:|:-------------------------------------------------------------|
| id           | Integer  | &#x2713; | Allergy record unique internal identifier.                   |
| name         | Text     | &#x2713; | Name of the allergy.                                         |
| signs        | Text     | &#x2713; | Signs observed on patients that have the allergy.            |
| symptoms     | Text     | &#x2713; | Symptoms observed on patients that have the allergy.         |
| creationTime | Datetime | &#x2713; | Timestamp of the moment when the allergy was created.        |
| updateTime   | Datetime | &#x2713; | Timestamp of the moment when the allergy was last updated.   |

#### Integrity constraints

* **Primary key** is defined over `id` column

