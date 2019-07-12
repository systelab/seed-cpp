import 'mocha';
import { expect } from 'chai';
import { Utils } from '../libraries/lib-utils';
import { RestAPI } from '../libraries/lib-restAPI';
import { SeedCppApplication} from '../tested-apps/seed-cpp-app';

describe('Patients: ', async () =>{
  var token:string = "";
  beforeEach(async() =>
  {
    SeedCppApplication.startApplication();
    token = await RestAPI.getAuthenticationToken();
  });

  afterEach(async() =>
  {
    SeedCppApplication.closeApplication();
  });

  xit('should create a patient', async() => {
      
    let requestUrl = RestAPI.REST_PATIENT;
    let expectedStatus = RestAPI.REST_STATUS_CREATED;

    let requestBodyToSend =
    {
        "name":"User",
        "surname":"Surname",
        "email":"user@werfen.com",
        "address":
        {
            "coordinates":"41°36'36.1''N 2°17'24.9''E",
            "street":"C/Enginyer, 14 2n 3a",
            "city": "Granollers",
            "zip": "08402"
        }   
    }
    
    let expectedResponseBody =
    {
        "id": "", //Different each time
        "surname": "Surname",
        "name": "User",
        "email": "user@werfen.com",
        "dob": "19700101T000000",
        "address": {
            "coordinates": "41°36'36.1''N 2°17'24.9''E",
            "street": "C/Enginyer, 14 2n 3a",
            "city": "Granollers",
            "zip": "08402"
        }
    }      
    await RestAPI.verifyPostEndpointRequest(requestUrl, token, JSON.stringify(requestBodyToSend), expectedStatus, JSON.stringify(expectedResponseBody));
  });
});