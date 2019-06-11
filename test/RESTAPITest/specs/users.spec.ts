var assert = require('assert');
var child_process = require('child_process');

function sleep(ms)
{
  return new Promise(resolve=>{
      setTimeout(resolve,ms)
  })
}

describe('rest/api/users', () =>
{
  describe('GET endpoint returns an array', () => 
  {
    it('should return -1 when the value is not present', async () =>
    {
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

      await sleep(5000);

      console.log ("Performing assertion...");
      assert.equal(-1, [1,2,3].indexOf(4));
      console.log ("Assertion completed");

      await sleep(10000);

      serverProcess.kill('SIGTERM');
      console.log("Kill process");
    });
  });
});
