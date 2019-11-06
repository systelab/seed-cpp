
export interface Page<T>
{
    content: T[];
    totalElements: number;
    first: boolean;
    last: boolean;
    number: number;
    numberOfElements: number;
    size: number;
    totalPages: number;
}
