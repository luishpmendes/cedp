CPP=g++
CARGS=-std=c++14 -Wall -Werror -O0 -g3 -m64
DLIBINC=/opt/dlib-19.19/
DLIB=-lpthread -lX11
CXXFILES=/opt/dlib-19.19/dlib/all/source.cpp
MKDIR=mkdir -p
RM=rm -rf
SRC=$(PWD)/src
BIN=$(PWD)/bin

clean:
	$(RM) $(BIN)

$(BIN)/%.o: $(SRC)/%.cpp
	$(MKDIR) $(@D)
	$(CPP) $(CARGS) -c $< -o $@ -I$(DLIBINC)

$(BIN)/test/InstanceTest: $(BIN)/disjoint-sets/DisjointSets.o \
                          $(BIN)/graph/Vertex.o \
                          $(BIN)/graph/Edge.o \
                          $(BIN)/graph/Graph.o \
                          $(BIN)/instance/Instance.o \
                          $(BIN)/test/InstanceTest.o
	$(MKDIR) $(@D)
	$(CPP) -o $@ $^ $(CARGS)

$(BIN)/exec/GraphGeneratorExec: $(BIN)/disjoint-sets/DisjointSets.o \
                                $(BIN)/graph/Vertex.o \
                                $(BIN)/graph/Edge.o \
                                $(BIN)/graph/Graph.o \
                                $(BIN)/instance/Instance.o \
                                $(BIN)/exec/ArgumentParser.o \
                                $(BIN)/exec/GraphGeneratorExec.o
	$(MKDIR) $(@D)
	$(CPP) -o $@ $^ $(CARGS)

$(BIN)/exec/InstanceGeneratorExec: $(BIN)/disjoint-sets/DisjointSets.o \
                                   $(BIN)/graph/Vertex.o \
                                   $(BIN)/graph/Edge.o \
                                   $(BIN)/graph/Graph.o \
                                   $(BIN)/instance/Instance.o \
                                   $(BIN)/exec/ArgumentParser.o \
                                   $(BIN)/exec/InstanceGeneratorExec.o
	$(MKDIR) $(@D)
	$(CPP) -o $@ $^ $(CARGS)

$(BIN)/test/SolutionTest: $(BIN)/disjoint-sets/DisjointSets.o \
                          $(BIN)/graph/Vertex.o \
                          $(BIN)/graph/Edge.o \
                          $(BIN)/graph/Graph.o \
                          $(BIN)/instance/Instance.o \
                          $(BIN)/solution/Solution.o \
                          $(BIN)/test/SolutionTest.o
	$(MKDIR) $(@D)
	$(CPP) -o $@ $^ $(CARGS)

$(BIN)/test/HeuristicTest: $(BIN)/disjoint-sets/DisjointSets.o \
                           $(BIN)/graph/Vertex.o \
                           $(BIN)/graph/Edge.o \
                           $(BIN)/graph/Graph.o \
                           $(BIN)/instance/Instance.o \
                           $(BIN)/solution/Solution.o \
                           $(BIN)/solver/heuristic/Heuristic.o \
                           $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                           $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                           $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                           $(BIN)/test/HeuristicTest.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)

InstanceTest: $(BIN)/test/InstanceTest

GraphGeneratorExec: $(BIN)/exec/GraphGeneratorExec

InstanceGeneratorExec: $(BIN)/exec/InstanceGeneratorExec

SolutionTest: $(BIN)/test/SolutionTest

HeuristicTest: $(BIN)/test/HeuristicTest

