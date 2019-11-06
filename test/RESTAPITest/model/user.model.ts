export enum UserRole
{
    User = "USER",
    Admin = "ADMIN"
}

export interface User
{
    id: number;
    surname: string;
    name: string;
    login: string;
    password: string;
    role: UserRole;
}
