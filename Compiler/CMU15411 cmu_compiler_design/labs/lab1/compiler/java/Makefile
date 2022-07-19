# Lab 1 Makefile

# On Windows
#IS_UNIX=
# On Unix
IS_UNIX=true

LAB_NUM=1
LAB_NAME=l$(LAB_NUM)

#Location of packages
PACK=edu/cmu/cs/$(LAB_NAME)
#How to the get back from cd'ing into the packages
PACKBACK=../../../..

#The final JAR archive
JARARCH=$(LAB_NAME).jar

JCC=javac
JAVA=java
JAVA_ARGS=-mx64m -ss64m

#Get CUP and Jlex into the classpath without bash
CUP=java_cup.jar
LEX=JLex.jar
SEP=$(if $(IS_UNIX),:,\;)
INCLUDE=-classpath .$(SEP)$(CUP)$(SEP)$(LEX)

SRC_DIRS=general errormsg absyn symbol translate tree x86 temp main assem codegen parse
LIB_MODULES=$(CUP) $(LEX)
USR_MODULES=$(foreach d,$(SRC_DIRS),$(PACK)/$(d)/*.class)
MODULES=$(LIB_MODULES) $(USR_MODULES)

all: l1c

l1c: $(PACK)/parse/simple.lex.java $(PACK)/parse/parser.java $(LIB_MODULES) $(foreach d,$(SRC_DIRS),$(PACK)/$(d).class)
	jar cfm $(JARARCH) manifest.mf $(MODULES) 

$(PACK)/%.class: $(PACK)/%
	$(JCC) $(INCLUDE) $</*.java

$(PACK)/parse/simple.lex.java: $(PACK)/parse/simple.lex $(PACK)/parse/parser.java
	java -classpath $(LEX) JLex.Main $(PACK)/parse/simple.lex
	$(JCC) $(INCLUDE) $(PACK)/parse/simple.lex.java

$(PACK)/parse/parser.java: $(PACK)/parse/simple.cup
	cd $(PACK)/parse; java -classpath $(PACKBACK)/../$(CUP) java_cup.Main -expect 1 -dump_grammar -dump_states <simple.cup >simple.out 2>simple.err; cd $(PACKBACK)

LAB_BIN=$(JAVA) $(JAVA_ARGS) -jar $(JARARCH)
LAB_ARGS=$(if $(IS_UNIX),,-win) -v
LAB_EXT=l$(LAB_NUM)

TEST_INPUT_PATH=../tests
TEST_INPUT=foo.$(LAB_EXT)

TEST_OUTPUT_PATH=bin
TEST_OUTPUT=$(TEST_INPUT:.$(LAB_EXT)=.s)
test: $(TEST_FILE)
	$(LAB_BIN) $(LAB_ARGS) -o $(TEST_OUTPUT_PATH)/$(TEST_OUTPUT) $(TEST_INPUT_PATH)/$(TEST_INPUT)

clean:
	rm -f *~ bin/*.o bin/*.exe *.exe *.dll $(JARARCH) \
	$(PACK)/parse/simple.lex.java $(PACK)/parse/parser.java $(PACK)/parse/sym.java \
	$(USR_MODULES)

TAGS: clean
	${RM} TAGS
	bin/create-tags $(foreach d,$(SRC_DIRS),$(PACK)/$(d)/*.java)
