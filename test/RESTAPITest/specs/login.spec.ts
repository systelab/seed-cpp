import 'mocha';
import { expect } from 'chai';
import { Utils } from '../libraries/lib-utils';
import { RestAPI } from '../libraries/lib-restAPI';
import { SeedCppApplication} from '../tested-apps/seed-cpp-app';

describe('Login: ', async () =>{
  var token: string = '';
  beforeEach(async() =>
  {
    SeedCppApplication.startApplication();
  });

  afterEach(async() =>
  {
    SeedCppApplication.closeApplication();
  });

  it('should login successfully', async() => {
      
      let requestUrl = RestAPI.REST_LOGIN;
      let requestBodyToSend = "login=Systelab&password=Systelab";
      let expectedStatus = RestAPI.REST_STATUS_OK;
      
      await RestAPI.verifyPostEndpointRequest(requestUrl, token, requestBodyToSend, expectedStatus, '');
  });

  it('should not login because wrong credentials', async() => {
    
    let requestUrl = RestAPI.REST_LOGIN;
    let requestBodyToSend = "login=Systelab&password=Unexisting";
    let expectedStatus = RestAPI.REST_STATUS_UNAUTHORIZED;
    
    await RestAPI.verifyPostEndpointRequest(requestUrl, token, requestBodyToSend, expectedStatus, '');
  }); 
});