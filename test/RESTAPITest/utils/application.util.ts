var child_process = require('child_process');
const { platform } = require('os'),
osType = platform();

export class Application
{
    private applicationProcess;

    public constructor(name: string, args: string[], workingDir: string)
    {
        let command: string;
        if (osType == 'win32')
            command = name + ".exe";
        else
            command = "./" + name;

        this.applicationProcess = child_process.spawn(command, args, { cwd: workingDir });

        this.applicationProcess.on("error", function(err)
        {
            console.error(`Error while executing '${name}' application on '${workingDir}' folder:`);
            console.error("Error details:", err);
        });

        this.applicationProcess.on("error", function(err)
        {
            console.error(`Error while executing '${name}' application on '${workingDir}' folder:`);
            console.error("Error details:", err);
        });

        this.applicationProcess.on('close', (code, signal) =>
        {
            //console.log(`Child process closed with code ${code} and signal ${signal}`);
        });

        this.applicationProcess.on("exit", function (code, signal)
        {
            //console.log(`Child process exited with code ${code} and signal ${signal}`);
        });

        this.applicationProcess.stdout.on('data', (data) =>
        {
            //console.log(`Child stdout: ${data}`);
        });

        this.applicationProcess.stderr.on('data', (data) =>
        {
            console.error(`child stderr: ${data}`);
        });
    }

    public close(): void
    {
        this.applicationProcess.kill('SIGINT');
    }
}
