declare var require: any;
var child_process = require('child_process');


export class SeedCppApplication
{
    public static serverProcess = child_process.spawn("SeedCpp.exe", ["--port", "7070"], { cwd: "../../build/bin/" }, (err, data) =>
    {  
        console.log(err)
        console.log(data.toString());                       
    });


    public static startApplication()
    {
        this.serverProcess.stdout.on('data', function(data){
            console.log('stdout:'+data);
        });

        this.serverProcess.stderr.on('data', function(data){
            console.log('stderr:'+data);
        });

        this.serverProcess.stdin.on('data', function(data){
            console.log('stdin:'+data);
        });
    }

    public static closeApplication()
    {
        this.serverProcess.on('close', (code, signal) => {
            console.log(
                `server process terminated due to receipt of signal ${signal}`);
        });
    }   
}









