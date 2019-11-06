import { Address, Patient } from '@model';
import { Response, StatusCode } from '@restapi';
import { SeedCppRestApi } from '@apps';

export class PatientUtility
{
    public static async createUser(api: SeedCppRestApi, name: string, surname: string, email: string, address: Address): Promise<Patient>
    {
        const requestBody: Patient =
        {
            id: 0, // Excluded member
            name: name,
            surname: surname,
            email: email,
            address: address
        }

        const response: Response = await api.sendPOSTRequest(SeedCppRestApi.PATIENTS_PATIENT, requestBody);

        if (response.status !== StatusCode.CREATED )
        {
            console.log("Unable to create a user, Response: " + JSON.stringify(response));
        }

       return response.body;
    }
}
