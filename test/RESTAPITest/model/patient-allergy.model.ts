import { Allergy } from "./allergy.model";

export interface PatientAllergy
{
    id: number;
    allergy: Allergy;
    assertedDate: string;
    lastOccurrence: string;
    note: string;
}
