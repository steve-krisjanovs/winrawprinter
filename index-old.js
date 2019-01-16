//index.js
const testAddon = require('./build/Release/winrawprinter.node');

var fs = require("fs");
var buff = fs.readFileSync("C:/temp/PrintJob.PCL6.txt");
var printername = "HP LaserJet P4515 PCL6 Class Driver";
//var printername = "Generic / Text Only";
//var printername = "dummy printer";

//print the raw data
//console.log(testAddon.hello());
var result = testAddon.PrintBufferToPrinter(buff, printername);

//console.log(testAddon.hello());
//console.log('add ', testAddon.add(5, 10));
module.exports = testAddon;