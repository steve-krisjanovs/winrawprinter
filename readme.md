winrawprinter
=============

A native node.js module I created to facilitate synchronous raw printing to a windows printer. If the printer uses a type=4 driver (XPS), the native code will utilize the "XPS_PASS" override for the print job's DocInfo.pDatatype to allow raw passthrough to work for those printers as well (default is "RAW"). 

Print data can be anything compatible with the printer your are sending the print job to (e.g. ZPL for Zebra thermal printing, PCL for HP PCL printers, Postscript, ESC/P for legacy Epson dot matrix printing, etc.)

## Dev environment configuration

Since this module is a native C++ module, please refer to the guides at https://github.com/nodejs/node-gyp for setting things up in order to compile this module. Personally I used VS Code for the module itself and VS 2017 community for the c++ build toolchain

## Installation

```
npm install winrawprinter
```

## Usage

```
var fs = require("fs");
var rawprint = require("winrawprinter");
var printername = "My Windows printer name";
var filepath = "C:/temp/printjobdata.dat";

var buff = fs.readFileSync(filepath);
var result = rawprint.PrintBufferToPrinter(buff, printername);

//note: result is a boolean (true = print successful)

```