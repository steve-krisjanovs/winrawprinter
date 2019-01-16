export function PrintBufferToPrinter(buff:Buffer, printername:String):boolean {
    const rawprinter_native = require('./build/Release/winrawprinter.node');

    if (buff.byteLength == 0)
        throw new Error("buff:Buffer parameter cannot be zero-length");

    if (printername.length == 0)
        throw new Error("printername:String parameter cannot be blank");

    var result:boolean = rawprinter_native.PrintBufferToPrinter(buff, printername);
    return result;
}

//sample code to test out raw printer functionality
//-----------------------------------------------
//import * as fs from "fs";
//var buff:Buffer = fs.readFileSync("C:/temp/PrintJob.PCL6.txt");
//var printername:String = "HP LaserJet P4515 PCL6 Class Driver";
//var result:Boolean = PrintBufferToPrinter(buff, printername);
//console.log(`Print result: ${result}`);
