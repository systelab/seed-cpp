import 'mocha';
import { Address, Patient } from '@model';
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
            id: 0, // Excluded member
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

        let expectedJSON = 
        {
            "content":
            [
                firstPatient,
                await PatientUtility.createUser(api, "John", "Smith", "john.smith@email.com", address),
                await PatientUtility.createUser(api, "Robert", "Williams", "robert.williams@email.com", address),
                await PatientUtility.createUser(api, "Mary", "Brown", "mary.brown@email.com", address)
            ],
            "totalElements":4,
            "first":true,
            "last":true,
            "number":0,
            "numberOfElements":4,
            "size":20,
            "totalPages":1
        }
       
        response = await api.sendGETRequest(SeedCppRestApi.PATIENTS);
        RESTAPI.expectStatus(response, StatusCode.OK);
        RESTAPI.expectBody(response, expectedJSON);
    });
    

    it('should not create a patient when unauthorized user', async() =>
    {
        await api.login("WrongUser", "WrongPassword");

        const address: Address =
        {
            coordinates: "41°36'36.1''N 2°17'24.9''E",
            street: "C/Enginyer, 14 2n 3a",
            city: "Granollers",
            zip: "08402"
        }

        const requestBody: Patient =
        {
            id: 0, // Excluded member
            name: "User",
            surname: "Surname",
            email: "user@werfen.com",
            address: address
        }

        const response: Response = await api.sendPOSTRequest(SeedCppRestApi.PATIENTS_PATIENT, requestBody);
        await RESTAPI.expectStatus(response, StatusCode.FORBIDDEN);

        const expectedBody: string = "";
        await RESTAPI.expectBody(response, expectedBody);
    });
});