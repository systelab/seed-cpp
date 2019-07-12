import { Utils } from '../libraries/lib-utils';

declare var require: any;
let chai = require('chai');
let chaiHttp = require('chai-http');
const expect = require('chai').expect;
var assert = require('assert');
chai.use(chaiHttp);

export class RestAPI
{    

    // Constand endpoint variables
    public static SEED_APP_REST_URI: string = 'http://localhost:8080/seed/v1';

    // Users
    public static REST_USERS: string        = '/users';
    public static REST_LOGIN: string        = RestAPI.REST_USERS + '/login';

    // Patients
    public static REST_PATIENTS: string     = '/patients';
    public static REST_PATIENT: string      = RestAPI.REST_PATIENTS + '/patient';

    // Status
    public static REST_STATUS_OK: number = 200;
    public static REST_STATUS_CREATED: number = 201;
    public static REST_STATUS_UNAUTHORIZED: number = 401;
    public static REST_STATUS_NOT_FOUND: number = 404;

    static async verifyPostEndpointRequest(requestUrl, token, requestBodyToSend, expectedStatus, expectedResponseBody): Promise<void>
    {

        let res = await chai.request(RestAPI.SEED_APP_REST_URI)
            .post(requestUrl)
            .set('content-type', 'application/x-www-form-urlencoded')
            .set('Authorization', token)
            .send(requestBodyToSend);

        expect(res).to.have.status(expectedStatus);
        expect(JSON.stringify(res.body)).to.be.equal(JSON.stringify(expectedResponseBody));
        expect(res.header.authorization).not.equal(null);      
    }

    static async getAuthenticationToken(): Promise<string>
    {
        var token: string = "";
        let res = await chai.request(RestAPI.SEED_APP_REST_URI)
            .post(this.REST_LOGIN)
            .set('content-type', 'application/x-www-form-urlencoded')
            .send("login=Systelab&password=Systelab");

        expect(await res.header.authorization).not.equal(null);       
        return await res.header.authorization;
    }
}


