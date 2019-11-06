var fs = require('fs');

export class File
{
    public static deleteFile(path: string): void
    {
        if (fs.existsSync(path)) 
        {
            fs.unlink(path, (err) =>
            {
                if (err) throw err;
                console.log(path + ' was deleted');
            });
        }
        else
        {
            console.log('The file does not exists.');
        }
    }
}
