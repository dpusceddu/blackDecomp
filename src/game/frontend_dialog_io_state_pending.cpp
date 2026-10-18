// Unmatched: 33-case asynchronous save-I/O scheduling and register allocation.
#if 0
#include "game/frontend/save_dialog.hpp"
extern "C" int func_0026F7E0(void*,int,int*);
extern "C" int func_0026F560(void*);
extern "C" int func_0026F508(void*,const char*);
extern "C" int func_0010B9B0(void*);
extern "C" int func_0026F4C0(void*,const char*);
extern "C" int func_0026F798(void*,const char*);
extern "C" int func_0026F4B8(void*);
extern "C" int func_0026F748(void*);
extern "C" void func_0010BBE8(void*);
extern "C" int func_0026F580(void*,const char*,int,int);
extern "C" int func_0026F6E8(void*,void*,int,int);
extern "C" int func_0026F640(void*);
extern "C" void func_0010F620(void*);
extern "C" void* D_0040F4EC;
extern "C" int func_0026F688(void*,void*,int,int);
void FrontendSaveDialog::UpdateIO() {
    int result[4];
    int next, statusCode, deviceStatus;
    switch(operation) {
    case 0:
        func_0026F7E0(io,0,result);
        requested=0;
        operation=1;
        return;
    case 1:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode==0) {
            requested=func_0026F560(io);
            operation=31;
            return;
        }
        if(statusCode!=13) return;
        requested=0;
        next=32;
        break;
    case 2:
        status=0;
        if(func_0026F508(io,directory)) {next=3;break;}
        goto errorWithFlag;
    case 3:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode) {if(statusCode!=13)return;goto errorWithFlag;}
        status=result[0];
        next=31;
        if(result[0]<=0) goto setErrorFlag;
        ioError=0;
        break;
    case 4:next=5;break;
    case 5:
        next=requested<func_0010B9B0(this)?32:31;
        break;
    case 6:
        next=func_0026F4C0(io,filename)?7:31;
        break;
    case 7:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode==0) {next=31;break;}
        if(statusCode!=13)return;
        next=func_0026F798(io,filename)?8:32;
        break;
    case 8:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode==0){next=31;break;}
        goto pollError;
    case 11:
        func_0026F7E0(io,0,result);
        operation=12;
        return;
    case 12:
        statusCode=func_0026F7E0(io,0,result);
        deviceStatus=func_0026F4B8(io);
        if(statusCode==0)goto error;
        if(statusCode!=13)return;
        next=32;
        if(deviceStatus==3 && func_0026F748(io)) {operation=13;return;}
        break;
    case 13:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode==0){next=31;break;}
        goto pollError;
    case 14:
        func_0010BBE8(profileData);
        if(ioError==1) {operation=15;fileCount=3;exists=0;return;}
        exists=1;operation=17;fileCount=1;return;
    case 15:
        next=16;
        if(!func_0026F508(io,fileNames[fileCount-1])) {next=17;exists=0;}
        break;
    case 16:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode==0){operation=17;exists=1;return;}
        if(statusCode!=13)return;
        exists=0;next=17;break;
    case 17:
        if(exists) statusCode=func_0026F580(io,fileNames[fileCount-1],2,0);
        else statusCode=func_0026F580(io,fileNames[fileCount-1],6,0);
        if(!statusCode)goto error;
        next=18;break;
    case 18:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode){goto pollError;}
        next=19;break;
    case 19:
        if(func_0026F6E8(io,fileData[fileCount-1],*fileLengths[fileCount-1],0)){next=20;break;}
        goto closeError;
    case 20:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode)goto pollError;
        next=21;break;
    case 21:
        if(!func_0026F640(io))goto error;
        next=22;break;
    case 22:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode)goto pollError;
        --fileCount;
        if(fileCount>0)next=15;
        else {func_0010F620(D_0040F4EC);next=31;}
        break;
    case 23:next=24;break;
    case 24:
        if(!func_0026F580(io,directory,1,0))goto error;
        next=25;break;
    case 25:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode)goto pollError;
        next=26;break;
    case 26:
        if(!func_0026F688(io,profileData,profileBytes,0))goto error;
        next=27;break;
    case 27:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode){if(statusCode!=13)return;goto closeError;}
        next=28;break;
    case 28:
        if(!func_0026F640(io))goto error;
        next=29;break;
    case 29:
        statusCode=func_0026F7E0(io,0,result);
        if(statusCode)goto pollError;
        next=31;break;
    case 9:case 10:case 30:case 31:case 32:default:return;
    }
    operation=next;
    return;
errorWithFlag:
    next=32;
setErrorFlag:
    operation=next;
    ioError=1;
    return;
closeError:
    func_0026F640(io);
error:
    operation=32;
    return;
pollError:
    if(statusCode==13)operation=32;
}
#endif
