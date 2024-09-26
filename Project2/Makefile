CXX=g++
CXXFLAGS = -std=c++17 -Wall
SRC_DIR = src
INCLUDE_DIR = src/include
TEST_DIR = testing

output: main.o Audit.o Ballot.o CPL.o IRV.o Entrants.o Testing.o TieHandler.o PO.o
	$(CXX) main.o Audit.o Ballot.o CPL.o IRV.o Entrants.o TieHandler.o PO.o -o BallotSystem

main.o:	$(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Audit.h $(INCLUDE_DIR)/Ballot.h $(INCLUDE_DIR)/CPL.h $(INCLUDE_DIR)/IRV.h $(INCLUDE_DIR)/Entrants.h
	$(CXX) -c $(SRC_DIR)/main.cpp -I $(INCLUDE_DIR)

Audit.o: $(INCLUDE_DIR)/Audit.h $(SRC_DIR)/Audit.cpp
	$(CXX) -c $(SRC_DIR)/Audit.cpp -I $(INCLUDE_DIR)

Ballot.o: $(INCLUDE_DIR)/Ballot.h $(SRC_DIR)/Ballot.cpp
	$(CXX) -c $(SRC_DIR)/Ballot.cpp -I $(INCLUDE_DIR)

CPL.o: $(INCLUDE_DIR)/CPL.h $(SRC_DIR)/CPL.cpp
	$(CXX) -c $(SRC_DIR)/CPL.cpp -I $(INCLUDE_DIR)

IRV.o: $(INCLUDE_DIR)/IRV.h $(SRC_DIR)/IRV.cpp
	$(CXX) -c $(SRC_DIR)/IRV.cpp -I $(INCLUDE_DIR)

Entrants.o: $(INCLUDE_DIR)/Entrants.h $(SRC_DIR)/Entrants.cpp
	$(CXX) -c $(SRC_DIR)/Entrants.cpp -I $(INCLUDE_DIR)

Testing.o: $(TEST_DIR)/Testing.cc
	$(CXX) -c $(TEST_DIR)/Testing.cc

TieHandler.o: $(INCLUDE_DIR)/TieHandler.h $(SRC_DIR)/TieHandler.cpp
	$(CXX) -c $(SRC_DIR)/TieHandler.cpp -I $(INCLUDE_DIR)

PO.o: $(INCLUDE_DIR)/PO.h $(SRC_DIR)/PO.cpp
	$(CXX) -c $(SRC_DIR)/PO.cpp -I $(INCLUDE_DIR)

test:
	$(CXX) Audit.o Ballot.o CPL.o IRV.o Entrants.o Testing.o TieHandler.o PO.o -lgtest -lgtest_main -lpthread -o testy.out
	./testy.out

clean:
	rm -f *.o BallotSystem *.txt *.csv testy.out
