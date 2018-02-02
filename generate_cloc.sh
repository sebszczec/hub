#!/bin/bash

sloccount --duplicates --wide --details $WORKSPACE > $WORKSPACE/sloccount.sc
cloc --by-file --xml --out=$WORKSPACE/cloc.xml $WORKSPACE

