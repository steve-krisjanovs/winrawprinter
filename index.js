"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const rawprinter_native = require('./build/Release/winrawprinter.node');
function validateParams(buff, printername) {
    if (buff.byteLength == 0)
        throw new Error("buff:Buffer parameter cannot be zero-length");
    if (printername.length == 0)
        throw new Error("printername:String parameter cannot be blank");
}
function PrintBufferToPrinter(buff, printername) {
    validateParams(buff, printername);
    var result = rawprinter_native.PrintBufferToPrinter(buff, printername);
    return result;
}
exports.PrintBufferToPrinter = PrintBufferToPrinter;
function PrintBufferToPrinterAsync(buff, printername) {
    return __awaiter(this, void 0, void 0, function* () {
        validateParams(buff, printername);
        var result = yield rawprinter_native.PrintBufferToPrinter(buff, printername);
        if (result == false) {
            //FALSE typically raised if the printer name is invalid
            throw new Error("rawprinter.cpp: Call to rawprinter::RawDataToPrinter(...) returned FALSE");
        }
    });
}
exports.PrintBufferToPrinterAsync = PrintBufferToPrinterAsync;
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
//# sourceMappingURL=index.js.map