# the following are SML-NJ specific defines
SML = sml

l1c: FORCE
	echo 'use "compile-l1c.sml";' | ${SML}

clean:
	find . -type d -name .cm | xargs rm -rf
	${RM} parse/*.lex.* parse/*.grm.*
	find . -type f | grep '~$$' | xargs ${RM}
	${RM} bin/l1c.heap.*

TAGS: clean
	${RM} TAGS
	bin/create-tags *.cm *.sml */*.lex */*.grm */*.sml

FORCE: 
