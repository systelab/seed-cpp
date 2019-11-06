import { Address } from "./address.model";

export interface Patient
{
    id: number;
    name: string;
    surname: string;
    email: string;
    dob?: string;
    address: Address;
}
