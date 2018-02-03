#!/bin/bash

cloc --by-file --xml --out=$WORKSPACE/cloc.xml $WORKSPACE
xsltproc $WORKSPACE/cloc2sloccount.xsl $WORKSPACE/cloc.xml > $WORKSPACE/sloccount.sc
