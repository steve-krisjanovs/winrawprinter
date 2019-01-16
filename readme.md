winrawprinter
=============

A native node.js module I created to facilitate raw printing to a windows printer. If the printer uses a type=4 driver (XPS), the native code will utilize the "XPS_PASS" for the print job's DocInfo.pDatatype to allow raw passthrough to work for those printers as well. 