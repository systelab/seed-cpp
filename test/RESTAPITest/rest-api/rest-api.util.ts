import { Request, RequestMethod } from './request.model';
import { Response, ResponseHeader, StatusCode } from './response.model';
import { HttpHeader } from './header.model';

let chai = require('chai');
let chaiHttp = require('chai-http');
let chaiExclude = require('chai-exclude');
const expect = require('chai').expect;

chai.use(chaiHttp);
chai.use(chaiExclude);


export class RESTAPI
{
    public static async sendRequest(request: Request): Promise<Response>
    {
        let chaiRequest = chai.request(request.appURI);

        if (request.method === RequestMethod.GET)
            chaiRequest = chaiRequest.get(request.resourceURI);
        else if (request.method === RequestMethod.POST)
            chaiRequest = chaiRequest.post(request.resourceURI);
        else if (request.method === RequestMethod.PUT)
            chaiRequest = chaiRequest.put(request.resourceURI);
        else if (request.method === RequestMethod.PATCH)
            chaiRequest = chaiRequest.patch(request.resourceURI);
        else if (request.method === RequestMethod.DELETE)
            chaiRequest = chaiRequest.del(request.resourceURI);
        else
            throw "Unknown request method: " + request.method;

        for (let header of request.headers)
        {
            chaiRequest = chaiRequest.set(header.name, header.value);
        }

        const chaiResponse = await chaiRequest.send(request.body);

        const responseHeaders: ResponseHeader[] = [];
        for (const headerName in chaiResponse.header)
        {
            responseHeaders[headerName] = {name: <HttpHeader>(headerName), value: chaiResponse.header[headerName]};
        }

        const response: Response = {
            status: chaiResponse.status,
            headers: responseHeaders,
            body: chaiResponse.body
        };

        return response;
    }

    public static expectStatus(response: Response, expectedStatus: StatusCode): void
    {
        expect(response.status).to.be.equal(expectedStatus)
    }

    public static expectHeaderPresent(response: Response, expectedHeader: HttpHeader): void
    {
        expect(response.headers).to.have.property(expectedHeader.toString().toLowerCase());
    }

    public static expectHeaderNotPresent(response: Response, expectedHeader: HttpHeader): void
    {
        expect(response.headers).to.have.not.property(expectedHeader.toString().toLowerCase());
    }

    public static expectHeader(response: Response, expectedHeader: ResponseHeader): void
    {
        expect(response.headers).to.include(expectedHeader);
    }

    public static expectBody(response: Response, expectedBody: any): void
    {
        expect(JSON.stringify(response.body)).to.be.equal(JSON.stringify(expectedBody))
    }

    public static expectBodyExcludingMembers(response: Response, expectedBody: any, excludeMembers: string[]): void
    {
        expect(response.body).excludingEvery(excludeMembers).to.deep.equal(expectedBody);
    }

}
