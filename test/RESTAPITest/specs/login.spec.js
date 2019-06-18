let chai = require('chai');
let chaiHttp = require('chai-http');
const expect = require('chai').expect;
var assert = require('assert');
var child_process = require('child_process');

chai.use(chaiHttp);
const url= 'http://localhost:8080/seed/v1';

var token;


function sleep(ms)
{
  return new Promise(resolve=>{
      setTimeout(resolve,ms)
  })
}


describe('Login: ',()=>{

it('should login successfully', async () => {

      const serverProcess = child_process.spawn("SeedCpp.exe", ["--port", "7070"], { cwd: "../../build/bin/" }, (err, data) =>
      {  
        console.log(err)
        console.log(data.toString());                       
      });

      serverProcess.stdout.on('data', function(data){
        console.log('stdout:'+data);
      });
    
      serverProcess.stderr.on('data', function(data){
        console.log('stderr:'+data);
      });
    
      serverProcess.stdin.on('data', function(data){
        console.log('stdin:'+data);
      });

      serverProcess.on('close', (code, signal) => {
        console.log(
          `server process terminated due to receipt of signal ${signal}`);
      });

      await sleep(2000);
    
    chai.request(url).post('/users/login').set('content-type', 'application/x-www-form-urlencoded').send({login:'Systelab', password:'Systelab'}).end( async function(err,res)
    {
      console.log(res.body)
      expect(res).to.have.status(200);
      expect(res.header.authorization).not.equal(null);
      token = res.header.authorization;
      console.log('Your token is:', res.header.authorization);

      await sleep(2000);

      serverProcess.kill('SIGTERM');
      console.log("Kill process");
  });
});

});


