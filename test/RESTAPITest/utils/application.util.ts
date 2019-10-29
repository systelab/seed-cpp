var child_process = require('child_process');


export class Application
{
    private applicationProcess;

    public constructor(name: string, args: string[], workingDir: string)
    {
        this.applicationProcess = child_process.spawn(name, args, { cwd: workingDir });
    }

    public close(): void
    {
        this.applicationProcess.kill('SIGINT');
    }
}
