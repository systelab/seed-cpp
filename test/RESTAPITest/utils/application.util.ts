var child_process = require('child_process');


export class Application
{
    private applicationProcess;

    public constructor(name: string, args: string[], workingDir: string)
    {
        this.applicationProcess = child_process.spawn(name, args, { cwd: workingDir });
        this.applicationProcess.on("error", function(err)
        {
            console.error(`Error while executing '${name}' application on '${workingDir}' folder:`);
            console.error("Error details:", err);
        });
    }

    public close(): void
    {
        this.applicationProcess.kill('SIGINT');
    }
}
