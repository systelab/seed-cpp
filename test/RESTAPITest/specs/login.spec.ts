import { SeedCppApp, SeedCppRestApi } from '@apps';
import { RESTAPI, Request, RequestMethod, HttpHeader, Response, StatusCode } from '@restapi';


describe('Login endpoint', async () =>
{
    let app: SeedCppApp;
    let api: SeedCppRestApi;

    before(async() =>
    {
        app = new SeedCppApp();
        await app.start();
        api = app.getRESTAPI();
    });

    after(async() =>
    {
        await app.close();
        app.removeDb();
    });

    it('should login successfully', async() =>
    {
        const username: string = "Systelab";
        const password: string = "Systelab";
        const request: Request = {
            appURI: api.getApplicationURI(),
            resourceURI: SeedCppRestApi.USERS_LOGIN,
            method: RequestMethod.POST,
            headers: [ {name: HttpHeader.ContentType, value: "application/x-www-form-urlencoded"} ],
            body: `login=${username}&password=${password}`
        }

        const response: Response = await RESTAPI.sendRequest(request);
        RESTAPI.expectStatus(response, StatusCode.OK);
        RESTAPI.expectHeaderPresent(response, HttpHeader.Authorization);
        RESTAPI.expectBody(response, {});
    });

    it('should not login when given user does not exist', async() =>
    {
        const username: string = "WrongUser";
        const password: string = "Systelab";
        const request: Request = {
            appURI: api.getApplicationURI(),
            resourceURI: SeedCppRestApi.USERS_LOGIN,
            method: RequestMethod.POST,
            headers: [ {name: HttpHeader.ContentType, value: "application/x-www-form-urlencoded"} ],
            body: `login=${username}&password=${password}`
        }

        const response: Response = await RESTAPI.sendRequest(request);
        RESTAPI.expectStatus(response, StatusCode.UNAUTHORIZED);
        RESTAPI.expectHeaderNotPresent(response, HttpHeader.Authorization);
        RESTAPI.expectBody(response, {});
    });

    it('should not login when given password is invalid', async() =>
    {
        const username: string = "Systelab";
        const password: string = "WrongPassword";
        const request: Request = {
            appURI: api.getApplicationURI(),
            resourceURI: SeedCppRestApi.USERS_LOGIN,
            method: RequestMethod.POST,
            headers: [ {name: HttpHeader.ContentType, value: "application/x-www-form-urlencoded"} ],
            body: `login=${username}&password=${password}`
        }

        const response: Response = await RESTAPI.sendRequest(request);
        RESTAPI.expectStatus(response, StatusCode.UNAUTHORIZED);
        RESTAPI.expectHeaderNotPresent(response, HttpHeader.Authorization);
        RESTAPI.expectBody(response, {});
    });

});