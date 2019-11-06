import 'mocha';
import { Thread } from '@utils';
import { RESTAPI, Response, StatusCode } from '@restapi';
import { SeedCppApp, SeedCppRestApi } from '@apps';


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
    });

    it('should create a patient', async() =>
    {
        const requestBody =
        {
            name: "User",
            surname: "Surname",
            email: "user@werfen.com",
            address:
            {
                coordinates: "41°36'36.1''N 2°17'24.9''E",
                street: "C/Enginyer, 14 2n 3a",
                city: "Granollers",
                zip: "08402"
            }
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
        RESTAPI.expectBodyExcludingMembers(response, expectedBody, ["id"]);
    });
});