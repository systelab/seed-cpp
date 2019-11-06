import { Application, File, Thread } from '@utils';
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
            this.application = new Application("SeedCpp", args, workingDir);
            await Thread.sleep(200);
        }
    }

    public async close(): Promise<void>
    {
        if (this.application)
        {
            this.application.close();
            this.application = null;
            await Thread.sleep(200);
        }
    }

    public getRESTAPI(): SeedCppRestApi
    {
        const port: number = this.getPort();
        return new SeedCppRestApi(`http://127.0.0.1:${port}/seed`);
    }

    public removeDb(): void
    {
        let dbPath: string = this.getWorkingDir() + "/seed_cpp.db";   
        File.deleteFile(dbPath);    
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
