import { HttpHeader, Request, RequestMethod, Response, RESTAPI, StatusCode } from "@restapi";

export class SeedCppRestApi
{
    // Health
    public static HEALTH: string            = '/v1/health';

    // Users
    public static USERS: string             = '/v1/users';
    public static USERS_LOGIN: string       = SeedCppRestApi.USERS + '/login';

    // Patients
    public static PATIENTS: string          = '/v1/patients';
    public static PATIENTS_PATIENT: string  = SeedCppRestApi.PATIENTS + '/patient';

    // Allergies
    public static ALLERGIES: string         = '/v1/allergies';
    public static ALLERGIES_ALLERGY: string = SeedCppRestApi.ALLERGIES + '/allergy';

    // Application URI
    private applicationURI: string;
    private authorizationToken: string;

    constructor(appURI: string)
    {
        this.applicationURI = appURI;
        this.authorizationToken = null;
    }

    public getApplicationURI(): string
    {
        return this.applicationURI;
    }

    public async login(username: string = "Systelab", password: string = "Systelab") : Promise<boolean>
    {
        const request: Request = {
            appURI: this.applicationURI,
            resourceURI: SeedCppRestApi.USERS_LOGIN,
            method: RequestMethod.POST,
            headers: [ {name: HttpHeader.ContentType, value: "application/x-www-form-urlencoded"} ],
            body: `login=${username}&password=${password}`
        }

        const response: Response = await RESTAPI.sendRequest(request);
        if (response.status == StatusCode.OK)
        {
            this.authorizationToken = response.headers[HttpHeader.Authorization.toLowerCase()].value;
            return true;
        }
        else
        {
            return false;
        }
    }

    public async sendPOSTRequest(resourceURI: string, body: any): Promise<Response>
    {
        const request: Request = {
            appURI: this.applicationURI,
            resourceURI: resourceURI,
            method: RequestMethod.POST,
            headers: [ {name: HttpHeader.ContentType, value: "application/json"} ],
            body: body
        }

        if (!!this.authorizationToken)
        {
            request.headers.push({name: HttpHeader.Authorization, value: this.authorizationToken});
        }

        return await RESTAPI.sendRequest(request);
    }
}
