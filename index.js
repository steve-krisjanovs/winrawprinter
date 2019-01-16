"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
function PrintBufferToPrinter(buff, printername) {
    var rawprinter_native = require('./build/Release/winrawprinter.node');
    if (buff.byteLength == 0)
        throw new Error("buff:Buffer parameter cannot be zero-length");
    if (printername.length == 0)
        throw new Error("printername:String parameter cannot be blank");
    var result = rawprinter_native.PrintBufferToPrinter(buff, printername);
    return result;
}
exports.PrintBufferToPrinter = PrintBufferToPrinter;
//sample code to test out raw printer functionality
//-----------------------------------------------
//import * as fs from "fs";
//var buff:Buffer = fs.readFileSync("C:/temp/PrintJob.PCL6.txt");
//var printername:String = "HP LaserJet P4515 PCL6 Class Driver";
//var result:Boolean = PrintBufferToPrinter(buff, printername);
//console.log(`Print result: ${result}`);
//# sourceMappingURL=index.js.map