const rawprinter_native = require('./build/Release/winrawprinter.node');

function validateParams(buff:Buffer, printername:String) {
    if (buff.byteLength == 0)
        throw new Error("buff:Buffer parameter cannot be zero-length");

    if (printername.length == 0)
        throw new Error("printername:String parameter cannot be blank");
}

export function PrintBufferToPrinter(buff:Buffer, printername:String):boolean {
    
    validateParams(buff, printername);
    
    var result:boolean = rawprinter_native.PrintBufferToPrinter(buff, printername);
    return result;
}

export async function PrintBufferToPrinterAsync(buff:Buffer, printername:String):Promise<void> {
    validateParams(buff, printername);
    var result:Boolean = await rawprinter_native.PrintBufferToPrinter(buff, printername);

    if (result == false) {
        //FALSE typically raised if the printer name is invalid
        throw new Error("rawprinter.cpp: Call to rawprinter::RawDataToPrinter(...) returned FALSE");
    }   
}

// //sample code to test out raw printer functionality
// //-----------------------------------------------
/* import * as fs from "fs";
var buff:Buffer = fs.readFileSync("C:/temp/PrintJob.PCL6.txt");
var printername:String = "Generic / Text Only";

//synchronous:
//------------
var result:Boolean = PrintBufferToPrinter(buff, printername);
console.log(`Print result: ${result}`); */

// //asynchronous:
// //-------------
// PrintBufferToPrinterAsync(buff, printername).then(() => {
//     //print successful
// }).catch((err) => {
//     //print failed
// });


