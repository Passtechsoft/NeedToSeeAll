#!/bin/sh

doxygen ntsa.doxygen
rm ./ntsaDocumentation.html
ln -s doc/html/index.html ./ntsaDocumentation.html
