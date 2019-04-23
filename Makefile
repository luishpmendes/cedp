CPP=g++
CARGS=-std=c++14 -Wall -Werror -O0 -g3 -m64
DLIBINC=/opt/dlib-19.19/
DLIB=-lpthread -lX11
CXXFILES=/opt/dlib-19.19/dlib/all/source.cpp
GRBINC=/opt/gurobi901/linux64/include/
GRBLIB=-L/opt/gurobi901/linux64/lib -lgurobi_c++ -lgurobi90 -lm
MKDIR=mkdir -p
RM=rm -rf
SRC=$(PWD)/src
BIN=$(PWD)/bin

clean:
	$(RM) $(BIN)

$(BIN)/%.o: $(SRC)/%.cpp
	$(MKDIR) $(@D)
	$(CPP) $(CARGS) -c $< -o $@ -I$(DLIBINC) -I$(GRBINC) $(GRBLIB)

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

$(BIN)/test/LinearRelaxationSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
                                        $(BIN)/graph/Vertex.o \
                                        $(BIN)/graph/Edge.o \
                                        $(BIN)/graph/Graph.o \
                                        $(BIN)/instance/Instance.o \
                                        $(BIN)/solution/Solution.o \
                                        $(BIN)/solver/heuristic/Heuristic.o \
                                        $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                                        $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                                        $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                                        $(BIN)/solver/CEDPSolver.o \
                                        $(BIN)/solver/metaheuristic/linear-relaxation/LinearRelaxationSolver.o \
                                        $(BIN)/test/LinearRelaxationSolverTest.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/exec/LinearRelaxationSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
                                        $(BIN)/graph/Vertex.o \
                                        $(BIN)/graph/Edge.o \
                                        $(BIN)/graph/Graph.o \
                                        $(BIN)/instance/Instance.o \
                                        $(BIN)/solution/Solution.o \
                                        $(BIN)/solver/heuristic/Heuristic.o \
                                        $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                                        $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                                        $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                                        $(BIN)/solver/CEDPSolver.o \
                                        $(BIN)/solver/metaheuristic/linear-relaxation/LinearRelaxationSolver.o \
                                        $(BIN)/exec/ArgumentParser.o \
                                        $(BIN)/exec/LinearRelaxationSolverExec.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/test/BnBSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
                           $(BIN)/graph/Vertex.o \
                           $(BIN)/graph/Edge.o \
                           $(BIN)/graph/Graph.o \
                           $(BIN)/instance/Instance.o \
                           $(BIN)/solution/Solution.o \
                           $(BIN)/solver/heuristic/Heuristic.o \
                           $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                           $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                           $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                           $(BIN)/solver/CEDPSolver.o \
                           $(BIN)/solver/exact/branch-and-bound/BnBSolver.o \
                           $(BIN)/test/BnBSolverTest.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/exec/BnBSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
                           $(BIN)/graph/Vertex.o \
                           $(BIN)/graph/Edge.o \
                           $(BIN)/graph/Graph.o \
                           $(BIN)/instance/Instance.o \
                           $(BIN)/solution/Solution.o \
                           $(BIN)/solver/heuristic/Heuristic.o \
                           $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                           $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                           $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                           $(BIN)/solver/CEDPSolver.o \
                           $(BIN)/solver/exact/branch-and-bound/BnBSolver.o \
                           $(BIN)/exec/ArgumentParser.o \
                           $(BIN)/exec/BnBSolverExec.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/test/BnCSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
                           $(BIN)/graph/Vertex.o \
                           $(BIN)/graph/Edge.o \
                           $(BIN)/graph/Graph.o \
                           $(BIN)/instance/Instance.o \
                           $(BIN)/solution/Solution.o \
                           $(BIN)/solver/heuristic/Heuristic.o \
                           $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                           $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                           $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                           $(BIN)/solver/CEDPSolver.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolverCallback.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolver.o \
                           $(BIN)/test/BnCSolverTest.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/exec/BnCSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
                           $(BIN)/graph/Vertex.o \
                           $(BIN)/graph/Edge.o \
                           $(BIN)/graph/Graph.o \
                           $(BIN)/instance/Instance.o \
                           $(BIN)/solution/Solution.o \
                           $(BIN)/solver/heuristic/Heuristic.o \
                           $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                           $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                           $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                           $(BIN)/solver/CEDPSolver.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolverCallback.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolver.o \
                           $(BIN)/exec/ArgumentParser.o \
                           $(BIN)/exec/BnCSolverExec.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)

$(BIN)/test/StatisticsTest: $(BIN)/statistics/Statistics.o \
                            $(BIN)/test/StatisticsTest.o
	$(MKDIR) $(@D)
	$(CPP) -o $@ $^ $(CARGS)

$(BIN)/test/GRASPSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
                             $(BIN)/statistics/Statistics.o \
                             $(BIN)/graph/Vertex.o \
                             $(BIN)/graph/Edge.o \
                             $(BIN)/graph/Graph.o \
                             $(BIN)/instance/Instance.o \
                             $(BIN)/solution/Solution.o \
                             $(BIN)/solver/heuristic/Heuristic.o \
                             $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                             $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                             $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                             $(BIN)/solver/CEDPSolver.o \
                             $(BIN)/solver/metaheuristic/grasp/GRASPSolver.o \
                             $(BIN)/test/GRASPSolverTest.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)

$(BIN)/exec/GRASPSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
                             $(BIN)/statistics/Statistics.o \
                             $(BIN)/graph/Vertex.o \
                             $(BIN)/graph/Edge.o \
                             $(BIN)/graph/Graph.o \
                             $(BIN)/instance/Instance.o \
                             $(BIN)/solution/Solution.o \
                             $(BIN)/solver/heuristic/Heuristic.o \
                             $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                             $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                             $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                             $(BIN)/solver/CEDPSolver.o \
                             $(BIN)/solver/metaheuristic/grasp/GRASPSolver.o \
                             $(BIN)/exec/ArgumentParser.o \
                             $(BIN)/exec/GRASPSolverExec.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)

$(BIN)/test/LagrangianHeuristicSolver1Test: $(BIN)/disjoint-sets/DisjointSets.o \
                                            $(BIN)/graph/Vertex.o \
                                            $(BIN)/graph/Edge.o \
                                            $(BIN)/graph/Graph.o \
                                            $(BIN)/instance/Instance.o \
                                            $(BIN)/solution/Solution.o \
                                            $(BIN)/solver/heuristic/Heuristic.o \
                                            $(BIN)/solver/heuristic/constructive/GreedyConstructiveHeuristic.o \
                                            $(BIN)/solver/heuristic/fixer/SolutionFixer.o \
                                            $(BIN)/solver/heuristic/localsearch/LocalSearchHeuristic.o \
                                            $(BIN)/solver/CEDPSolver.o \
                                            $(BIN)/solver/metaheuristic/lagrangian-heuristic/LagrangianHeuristicSolver1.o \
                                            $(BIN)/test/LagrangianHeuristicSolver1Test.o
	$(MKDIR) $(@D)
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)

InstanceTest: $(BIN)/test/InstanceTest

GraphGeneratorExec: $(BIN)/exec/GraphGeneratorExec

InstanceGeneratorExec: $(BIN)/exec/InstanceGeneratorExec

SolutionTest: $(BIN)/test/SolutionTest

HeuristicTest: $(BIN)/test/HeuristicTest

LinearRelaxationSolverTest: $(BIN)/test/LinearRelaxationSolverTest

LinearRelaxationSolverExec: $(BIN)/exec/LinearRelaxationSolverExec

BnBSolverTest: $(BIN)/test/BnBSolverTest

BnBSolverExec: $(BIN)/exec/BnBSolverExec

BnCSolverTest: $(BIN)/test/BnCSolverTest

BnCSolverExec: $(BIN)/exec/BnCSolverExec

StatisticsTest: $(BIN)/test/StatisticsTest

GRASPSolverTest: $(BIN)/test/GRASPSolverTest

GRASPSolverExec: $(BIN)/exec/GRASPSolverExec

LagrangianHeuristicSolver1Test: $(BIN)/test/LagrangianHeuristicSolver1Test

