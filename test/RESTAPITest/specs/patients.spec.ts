import 'mocha';
import { Address, Patient, Page } from '@model';
import { RESTAPI, Response, StatusCode } from '@restapi';
import { SeedCppApp, SeedCppRestApi } from '@apps';
import { PatientUtility } from '@utils';


describe('Patients', async () =>
{
    let app: SeedCppApp;
    let api: SeedCppRestApi;

    before(async() =>
    {
        app = new SeedCppApp();
        await app.start();
        api = app.getRESTAPI();
        await api.login();
    });

    after(async() =>
    {
        app.close();
        app.removeDb();
    });   
   

    it('should create a patient', async() =>
    {
        const address: Address =
        {
            coordinates: "41°36'36.1''N 2°17'24.9''E",
            street: "C/Enginyer, 14 2n 3a",
            city: "Granollers",
            zip: "08402"
        }

        const requestBody: Patient =
        {
            name: "User",
            surname: "Surname",
            email: "user@werfen.com",
            address: address
        }

        const response: Response = await api.sendPOSTRequest(SeedCppRestApi.PATIENTS_PATIENT, requestBody);
        RESTAPI.expectStatus(response, StatusCode.CREATED);

        const expectedBody: any =
        {
            surname: "Surname",
            name: "User",
            email: "user@werfen.com",
            address: {
                coordinates: "41°36'36.1''N 2°17'24.9''E",
                street: "C/Enginyer, 14 2n 3a",
                city: "Granollers",
                zip: "08402"
            }
        };
        await RESTAPI.expectBodyExcludingMembers(response, expectedBody, ["id"]);
    });

    it('should not get an unexisting patient', async() =>
    {
        let unexistingUid: string = "aa6a6aa6-66a6-6666-6aa6-a6aa666a666a";      
        let response: Response = await api.sendGETRequest(api.translateEndpointWithParams(SeedCppRestApi.PATIENTS_PATIENT_UID, [unexistingUid]));
        RESTAPI.expectStatus(response, StatusCode.NOT_FOUND);
        RESTAPI.expectBody(response, "");
    });

    it('should get all created patient', async() =>
    {
        // Get the only created patient for the moment to construct later expectedJSON
        let response: Response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        RESTAPI.expectStatus(response, StatusCode.OK);
        let firstPatient = response.body.content[0];

        // Construct expectedJSON
        const address: Address = 
        {
            coordinates: "41°36'36.1''N 2°17'24.9''E",
            street: "C/Enginyer, 14 2n 3a",
            city: "Granollers",
            zip: "08402"
        }

        let expectedJSON: Page<Patient> = 
        {
            "content":
            [
                firstPatient,
                await PatientUtility.createUser(api, "John", "Smith", "john.smith@email.com", address),
                await PatientUtility.createUser(api, "Robert", "Williams", "robert.williams@email.com", address),
                await PatientUtility.createUser(api, "Mary", "Brown", "mary.brown@email.com", address)
            ],
            "totalElements": 4,
            "first": true,
            "last": true,
            "number": 0,
            "numberOfElements": 4,
            "size": 20,
            "totalPages": 1
        }
       
        response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        RESTAPI.expectStatus(response, StatusCode.OK);
        RESTAPI.expectBody(response, expectedJSON);
    });

    it('should get a particular patient by UID', async() =>
    {
        let responseGETAllPatients: Response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        RESTAPI.expectStatus(responseGETAllPatients, StatusCode.OK);
        let firstPatient = responseGETAllPatients.body.content[0];
        let uid: string = firstPatient.id;
       
        let responseGETPatient: Response = await api.sendGETRequest(api.translateEndpointWithParams(SeedCppRestApi.PATIENTS_PATIENT_UID, [uid]));    
         // Construct expectedJSON
         const address: Address = 
         {
             coordinates: "41°36'36.1''N 2°17'24.9''E",
             street: "C/Enginyer, 14 2n 3a",
             city: "Granollers",
             zip: "08402"
         }
 
         let expectedJSON: Patient = 
         { 
             "id": uid,
            "surname": "Surname",
            "name": "User",
            "email": "user@werfen.com",
            "address": address      
         }         
         RESTAPI.expectStatus(responseGETPatient, StatusCode.OK);
         RESTAPI.expectBody(responseGETPatient, expectedJSON);
    });

    it('should update a patient by UID', async() =>
    {
        let responseGETAllPatients: Response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        await RESTAPI.expectStatus(responseGETAllPatients, StatusCode.OK);
        let firstPatient = responseGETAllPatients.body.content[0];
        let uid: string = firstPatient.id;

        const newAddress: Address =
        {
            coordinates: "41°38'88.841''N 2°15'62.21''E",
            street: "C/Muntaner, 108 1r 1a",
            city: "Barcelona",
            zip: "08006"
        }

        const requestBody: Patient =
        {
            name: "User",
            surname: "Surname",
            email: "user@werfen.com",
            address: newAddress
        }

        let response: Response = await api.sendPUTTRequest(api.translateEndpointWithParams(SeedCppRestApi.PATIENTS_PATIENT_UID, [uid]), requestBody);
        RESTAPI.expectStatus(response, StatusCode.OK);

        const expectedBody: any =
        {
            surname: "Surname",
            name: "User",
            email: "user@werfen.com",
            address: newAddress
        };
        await RESTAPI.expectBodyExcludingMembers(response, expectedBody, ["id"]);
    });

    it('should delete a patient by UID', async() =>
    {
        let responseGETAllPatients: Response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        await RESTAPI.expectStatus(responseGETAllPatients, StatusCode.OK);
        let firstPatient = responseGETAllPatients.body.content[1];
        let uid: string = firstPatient.id;
        
        // Check patients count before deletion
        let patientsCountBeforeDeletion = responseGETAllPatients.body.numberOfElements;

        let response: Response = await api.sendDELETERequest(api.translateEndpointWithParams(SeedCppRestApi.PATIENTS_PATIENT_UID, [uid]));
        RESTAPI.expectStatus(response, StatusCode.NO_CONTENT);

        // Check patients count after deletion
        responseGETAllPatients = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        let patientsCountAfterDeletion = responseGETAllPatients.body.numberOfElements;
        RESTAPI.expectEqual(patientsCountAfterDeletion, patientsCountBeforeDeletion - 1);
    });    

    it('should not get all patients when unauthorized user', async() =>
    {
        await api.login("WrongUser", "WrongPassword");
        const response: Response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        RESTAPI.expectStatus(response, StatusCode.UNAUTHORIZED);
        RESTAPI.expectBody(response, "");
    });

    it('should not create a patient when unauthorized user', async() =>
    {
        await api.login("WrongUser", "WrongPassword");

        const requestBody: Patient =
        {
            name: "User",
            surname: "Surname",
            email: "user@werfen.com",
            address: {
                coordinates: "41°36'36.1''N 2°17'24.9''E",
                street: "C/Enginyer, 14 2n 3a",
                city: "Granollers",
                zip: "08402"
            }
        }
        const response: Response = await api.sendPOSTRequest(SeedCppRestApi.PATIENTS_PATIENT, requestBody);
        await RESTAPI.expectStatus(response, StatusCode.UNAUTHORIZED);
        await RESTAPI.expectBody(response, "");
    }); 
});