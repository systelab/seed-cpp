export class Utils
{    
    public static sleep(ms)
    {
        return new Promise(resolve=>{
            setTimeout(resolve,ms)
        })
    }
}
