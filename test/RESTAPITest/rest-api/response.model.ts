import { HttpHeader } from "./header.model";

export enum StatusCode
{
    OK = 200,
    CREATED = 201,
    NO_CONTENT = 204,

    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,

    INTERNAL_SERVER_ERROR = 500
}

export interface ResponseHeader
{
    name: HttpHeader;
    value : string;
}

export interface Response
{
    status: StatusCode;
    headers: ResponseHeader[];
    body: any;
}
