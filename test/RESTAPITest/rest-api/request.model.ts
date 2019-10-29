import { HttpHeader } from './header.model'

export enum RequestMethod
{
    GET = "GET",
    POST = "POST",
    PUT = "PUT",
    PATCH = "PATCH",
    DELETE = "DELETE"
}

export interface RequestHeader
{
    name: HttpHeader;
    value: string;
}

export interface Request
{
    appURI: string;
    resourceURI: string;
    method: RequestMethod;
    headers: RequestHeader[];
    body: any;
}
