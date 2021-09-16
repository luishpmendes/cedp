CPP=g++
CARGS=-std=c++17 -O0 -g3 -m64
DLIBINC=/opt/dlib-19.22/
DLIB=-lpthread -lX11
CXXFILES=/opt/dlib-19.22/dlib/all/source.cpp
GRBINC=/opt/gurobi912/linux64/include/
GRBLIB=-L/opt/gurobi912/linux64/lib -lgurobi_c++ -lgurobi91 -lm
MKDIR=mkdir -p
RM=rm -rf
SRC=$(PWD)/src
BIN=$(PWD)/bin

clean:
	@echo "--> Cleaning compiled..."
	$(RM) $(BIN)
	@echo

$(BIN)/%.o: $(SRC)/%.cpp
	@echo "--> Compiling $<..."
	$(MKDIR) $(@D)
	$(CPP) $(CARGS) -c $< -o $@ -I$(DLIBINC) -I$(GRBINC) $(GRBLIB)
	@echo

$(BIN)/test/InstanceTest: $(BIN)/disjoint-sets/DisjointSets.o \
                          $(BIN)/graph/Vertex.o \
                          $(BIN)/graph/Edge.o \
                          $(BIN)/graph/Graph.o \
                          $(BIN)/instance/Instance.o \
                          $(BIN)/test/InstanceTest.o
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/InstanceTest
	@echo

InstanceTest: clean $(BIN)/test/InstanceTest

$(BIN)/exec/GraphGeneratorExec: $(BIN)/disjoint-sets/DisjointSets.o \
                                $(BIN)/graph/Vertex.o \
                                $(BIN)/graph/Edge.o \
                                $(BIN)/graph/Graph.o \
                                $(BIN)/instance/Instance.o \
                                $(BIN)/exec/ArgumentParser.o \
                                $(BIN)/exec/GraphGeneratorExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

GraphGeneratorExec: clean $(BIN)/exec/GraphGeneratorExec

$(BIN)/exec/InstanceGeneratorExec: $(BIN)/disjoint-sets/DisjointSets.o \
                                   $(BIN)/graph/Vertex.o \
                                   $(BIN)/graph/Edge.o \
                                   $(BIN)/graph/Graph.o \
                                   $(BIN)/instance/Instance.o \
                                   $(BIN)/exec/ArgumentParser.o \
                                   $(BIN)/exec/InstanceGeneratorExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

InstanceGeneratorExec: clean $(BIN)/exec/InstanceGeneratorExec

$(BIN)/test/SolutionTest: $(BIN)/disjoint-sets/DisjointSets.o \
                          $(BIN)/graph/Vertex.o \
                          $(BIN)/graph/Edge.o \
                          $(BIN)/graph/Graph.o \
                          $(BIN)/instance/Instance.o \
                          $(BIN)/solution/Solution.o \
                          $(BIN)/test/SolutionTest.o
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/SolutionTest
	@echo

SolutionTest: clean $(BIN)/test/SolutionTest

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
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/HeuristicTest
	@echo

HeuristicTest: clean $(BIN)/test/HeuristicTest

$(BIN)/test/StatisticsTest: $(BIN)/statistics/Statistics.o \
                            $(BIN)/test/StatisticsTest.o
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/StatisticsTest
	@echo

StatisticsTest: clean $(BIN)/test/StatisticsTest

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
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/GRASPSolverTest
	@echo

GRASPSolverTest: clean $(BIN)/test/GRASPSolverTest

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
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)
	@echo

GRASPSolverExec: clean $(BIN)/exec/GRASPSolverExec


$(BIN)/test/BnBSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
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
                           $(BIN)/solver/exact/branch-and-bound/BnBSolver.o \
                           $(BIN)/test/BnBSolverTest.o
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/BnBSolverTest
	@echo

BnBSolverTest: clean $(BIN)/test/BnBSolverTest

$(BIN)/exec/BnBSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
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
                           $(BIN)/solver/exact/branch-and-bound/BnBSolver.o \
                           $(BIN)/exec/ArgumentParser.o \
                           $(BIN)/exec/BnBSolverExec.o
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)
	@echo

BnBSolverExec: clean $(BIN)/exec/BnBSolverExec

$(BIN)/test/BnCSolverTest: $(BIN)/disjoint-sets/DisjointSets.o \
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
                           $(BIN)/solver/exact/branch-and-cut/BnCSolverCallback.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolver.o \
                           $(BIN)/test/BnCSolverTest.o
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)
	@echo
	@echo "--> Running test..."
	$(BIN)/test/BnCSolverTest
	@echo

BnCSolverTest: clean $(BIN)/test/BnCSolverTest

$(BIN)/exec/BnCSolverExec: $(BIN)/disjoint-sets/DisjointSets.o \
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
                           $(BIN)/solver/exact/branch-and-cut/BnCSolverCallback.o \
                           $(BIN)/solver/exact/branch-and-cut/BnCSolver.o \
                           $(BIN)/exec/ArgumentParser.o \
                           $(BIN)/exec/BnCSolverExec.o
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB) -I$(GRBINC) $(GRBLIB)
	@echo

BnCSolverExec: clean $(BIN)/exec/BnCSolverExec

$(BIN)/exec/StatisticsAggregatorExec: $(BIN)/exec/ArgumentParser.o \
                                      $(BIN)/exec/StatisticsAggregatorExec.o
	@echo "--> Linking objects..." 
	$(CPP) $(CXXFILES) -o $@ $^ $(CARGS) $(DLIB)
	@echo

StatisticsAggregatorExec: clean $(BIN)/exec/StatisticsAggregatorExec

$(BIN)/exec/PlotGeneratorExec: $(BIN)/disjoint-sets/DisjointSets.o \
                               $(BIN)/graph/Vertex.o \
                               $(BIN)/graph/Edge.o \
                               $(BIN)/graph/Graph.o \
                               $(BIN)/instance/Instance.o \
                               $(BIN)/solution/Solution.o \
                               $(BIN)/exec/ArgumentParser.o \
                               $(BIN)/exec/PlotGeneratorExec.o
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PlotGeneratorExec: clean $(BIN)/exec/PlotGeneratorExec

$(BIN)/exec/PerformanceProfilesPrimalExec: $(BIN)/exec/PerformanceProfilesPrimalExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalExec: clean $(BIN)/exec/PerformanceProfilesPrimalExec

$(BIN)/exec/PerformanceProfilesDualExec: $(BIN)/exec/PerformanceProfilesDualExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualExec: clean $(BIN)/exec/PerformanceProfilesDualExec

$(BIN)/exec/PerformanceProfilesPrimalTExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalTExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalTExec: clean $(BIN)/exec/PerformanceProfilesPrimalTExec

$(BIN)/exec/PerformanceProfilesDualTExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualTExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualTExec: clean $(BIN)/exec/PerformanceProfilesDualTExec

$(BIN)/exec/PerformanceProfilesPrimalMExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalMExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalMExec: clean $(BIN)/exec/PerformanceProfilesPrimalMExec

$(BIN)/exec/PerformanceProfilesDualMExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualMExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualMExec: clean $(BIN)/exec/PerformanceProfilesDualMExec

$(BIN)/exec/PerformanceProfilesPrimalBExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalBExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalBExec: clean $(BIN)/exec/PerformanceProfilesPrimalBExec

$(BIN)/exec/PerformanceProfilesDualBExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualBExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualBExec: clean $(BIN)/exec/PerformanceProfilesDualBExec

$(BIN)/exec/PerformanceProfilesPrimalDExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalDExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalDExec: clean $(BIN)/exec/PerformanceProfilesPrimalDExec

$(BIN)/exec/PerformanceProfilesDualDExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualDExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualDExec: clean $(BIN)/exec/PerformanceProfilesDualDExec

$(BIN)/exec/PerformanceProfilesPrimalVExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalVExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalVExec: clean $(BIN)/exec/PerformanceProfilesPrimalVExec

$(BIN)/exec/PerformanceProfilesDualVExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualVExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualVExec: clean $(BIN)/exec/PerformanceProfilesDualVExec

$(BIN)/exec/PerformanceProfilesPrimalEExec: $(BIN)/exec/ArgumentParser.o \
                                            $(BIN)/exec/PerformanceProfilesPrimalEExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesPrimalEExec: clean $(BIN)/exec/PerformanceProfilesPrimalEExec

$(BIN)/exec/PerformanceProfilesDualEExec: $(BIN)/exec/ArgumentParser.o \
                                          $(BIN)/exec/PerformanceProfilesDualEExec.o 
	@echo "--> Linking objects..." 
	$(CPP) -o $@ $^ $(CARGS)
	@echo

PerformanceProfilesDualEExec: clean $(BIN)/exec/PerformanceProfilesDualEExec

$(BIN)/exec/StatisticsCalculatorExec: $(BIN)/exec/ArgumentParser.o \
                                      $(BIN)/exec/StatisticsCalculatorExec.o 
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorExec: clean $(BIN)/exec/StatisticsCalculatorExec

$(BIN)/exec/StatisticsCalculatorTExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorTExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorTExec: clean $(BIN)/exec/StatisticsCalculatorTExec

$(BIN)/exec/StatisticsCalculatorMExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorMExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorMExec: clean $(BIN)/exec/StatisticsCalculatorMExec

$(BIN)/exec/StatisticsCalculatorBExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorBExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorBExec: clean $(BIN)/exec/StatisticsCalculatorBExec

$(BIN)/exec/StatisticsCalculatorDExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorDExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorDExec: clean $(BIN)/exec/StatisticsCalculatorDExec

$(BIN)/exec/StatisticsCalculatorVExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorVExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorVExec: clean $(BIN)/exec/StatisticsCalculatorVExec

$(BIN)/exec/StatisticsCalculatorEExec: $(BIN)/exec/ArgumentParser.o \
                                       $(BIN)/exec/StatisticsCalculatorEExec.o
	@echo "--> Linking objects..."
	$(CPP) -o $@ $^ $(CARGS)
	@echo

StatisticsCalculatorEExec: clean $(BIN)/exec/StatisticsCalculatorEExec

tests: InstanceTest \
       SolutionTest \
       HeuristicTest \
       StatisticsTest \
       BnBSolverTest \
       BnCSolverTest \
       GRASPSolverTest

execs: GraphGeneratorExec \
       InstanceGeneratorExec \
       GRASPSolverExec \
       BnBSolverExec \
       BnCSolverExec \
       StatisticsAggregatorExec \
       PlotGeneratorExec \
       PerformanceProfilesPrimalExec \
       PerformanceProfilesDualExec \
       PerformanceProfilesPrimalTExec \
       PerformanceProfilesDualTExec \
       PerformanceProfilesPrimalMExec \
       PerformanceProfilesDualMExec \
       PerformanceProfilesPrimalBExec \
       PerformanceProfilesDualBExec \
       PerformanceProfilesPrimalDExec \
       PerformanceProfilesDualDExec \
       PerformanceProfilesPrimalVExec \
       PerformanceProfilesDualVExec \
       PerformanceProfilesPrimalEExec \
       PerformanceProfilesDualEExec \
       StatisticsCalculatorExec \
       StatisticsCalculatorTExec \
       StatisticsCalculatorMExec \
       StatisticsCalculatorBExec \
       StatisticsCalculatorDExec \
       StatisticsCalculatorVExec \
       StatisticsCalculatorEExec

all : tests execs

