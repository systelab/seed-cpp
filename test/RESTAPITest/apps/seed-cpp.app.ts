import { Application, Thread } from '@utils';
import { RESTAPI } from '@restapi';
import { SeedCppRestApi } from './seed-cpp-rest-api.app'

export class SeedCppApp
{
    private application: Application;

    public async start(): Promise<void>
    {
        if (!this.application)
        {
            const args: string[] = ["--port", this.getPort().toString()];
            const workingDir: string = this.getWorkingDir();
            this.application = new Application("SeedCpp.exe", args, workingDir);
            await Thread.sleep(200);
        }
    }

    public close()
    {
        if (this.application)
        {
            this.application.close();
            this.application = null;
        }
    }

    public getRESTAPI(): SeedCppRestApi
    {
        const port: number = this.getPort();
        return new SeedCppRestApi(`http://localhost:${port}/seed`);
    }

    private getPort(): number
    {
        return (process.env.PORT !== undefined) ? +process.env.PORT : 7171;
    }

    private getWorkingDir(): string
    {
        const configuration: string = (process.env.CONFIGURATION !== undefined) ? process.env.CONFIGURATION : "Debug";
        //return `../../build/bin/SeedCpp/${configuration}`;
        return "../../build/bin";
    }
}
