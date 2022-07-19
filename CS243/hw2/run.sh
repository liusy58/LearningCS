#!/bin/sh
here=`dirname $0`
java -cp build/:${here}/lib/joeq.jar "$@"
