compile: clean
	chmod +x run.sh
	mkdir build
	${JAVA_HOME}/bin/javac -Xlint:-options -source 1.5 -target 1.5 \
	  -cp lib/joeq.jar \
	  -sourcepath src -d build `find src -name "*.java"`

clean:
	rm -rf build/

submission.zip: src/submit/Faintness.java src/submit/MySolver.java src/submit/ReachingDefs.java collaborators.txt
	zip -r $@ $^

submission: submission.zip
