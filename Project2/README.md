
# Instructions to test the system: 
    In the terminal, making sure you're in ../repo-Team4/Project2 folder, simply enter the following commands:

1. `make`
2. `./BallotSystem`

If Successful, then you will be prompted to enter a file(s). Once you have done so, the terminal should print complete. From here, you should see an audit file which is a .txt containing an audit of the election(s). 

**NOTE**: Please run `make clean` after each test (IR, PO, CPL) to ensure that the program runs without any issues. 

**NOTE**: The file you want to test with the system must be in the same directory as the makefile. If you wish to test using our test files, then simply add the directory named misc/ in front, such as `misc/CPLTEST.csv`.

# Intructions for Unit testing:
    In the terminal, making sure you're in ../repo-Team4/Project2 folder, simply enter the following commands:

1. `make`
2. `make test`

This will show all the integration and unit testing that was done for CPL, IRV, PO, and etc. 

**Bugs**:
- During the grading of part 1, the TA noticed that there was errors. When SSH'ing into Keller Computers we noticed that it would cause errors. We have tested that SSH'ing through the Atlas computers and using VOLE work. 
