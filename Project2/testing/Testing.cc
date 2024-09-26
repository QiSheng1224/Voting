#include "gtest/gtest.h"
#include "../src/include/Audit.h"
#include "../src/include/Ballot.h"
#include "../src/include/CPL.h"
#include "../src/include/Entrants.h"
#include "../src/include/IRV.h"
#include "../src/include/TieHandler.h"
#include "../src/include/PO.h"

// #include <vector>
// #include <string>
// #include <iosteam>


class AuditTest : public ::testing::Test {
    public:
        Audit testing = Audit();
        void SetUp() {
            testing.UpdEntrants(20);
            testing.UpdBallot(4);
            testing.UpdWinner("TESTING_ENTRANT");
            testing.UpdDate("3/15/2023");
            Entrants newEntrant = Entrants("Jeffrey Bozos");
            testing.UpdEntrants(newEntrant);
        }
};

TEST_F(AuditTest, UpdGetEntrantsTEST) {
    EXPECT_EQ(testing.GetEntrants(), 20);
    testing.UpdEntrants(30);
    EXPECT_EQ(testing.GetEntrants(), 30);
}




class BallotTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};

TEST_F(BallotTest, TestGetRank) {
    std::vector<int> rank = {1, 2, 3};
    Ballot b(rank);
    EXPECT_EQ(b.GetRank(), rank);
}

TEST_F(BallotTest, TestSetRank) {
    std::vector<int> rank = {4, 5, 6};
    Ballot b({1, 2, 3});
    b.SetRank(rank);
    EXPECT_EQ(b.GetRank(), rank);
}

TEST_F(BallotTest, TestSetAndGetRank) {
    std::vector<int> rank = {7, 8, 9};
    Ballot b(rank);
    EXPECT_EQ(b.GetRank(), rank);

    rank = {10, 11, 12};
    b.SetRank(rank);
    EXPECT_EQ(b.GetRank(), rank);
}




class CPLTest : public ::testing::Test {
    public:
        void SetUp() {

        }


};

TEST_F(CPLTest, TieCheckerTest1) {
    CPL cpl("misc/CPLTEST2.csv");
    cpl.TallyVotes();
    bool result = cpl.TieChecker();

    EXPECT_TRUE(result);
    EXPECT_EQ(cpl.GetTiedParties()[0].GetName(), "Republican");
    EXPECT_EQ(cpl.GetTiedParties()[1].GetName(), "Democratic");
}

TEST_F(CPLTest, TallyVotesTest) {
    CPL cpl("misc/CPLTEST2.csv");

    cpl.TallyVotes();

    std::vector<Entrants> parties = cpl.GetParties();
    EXPECT_EQ(parties[0].GetVotes(), 3);
    EXPECT_EQ(parties[1].GetVotes(), 3);
    EXPECT_EQ(parties[2].GetVotes(), 0);
    EXPECT_EQ(parties[3].GetVotes(), 2);
    EXPECT_EQ(parties[4].GetVotes(), 0);
    EXPECT_EQ(parties[5].GetVotes(), 1);
}

class EntrantsTest : public ::testing::Test {
    public:

        void SetUp() {
          
        }
};

// Test case to check if the constructor sets the correct name
TEST_F(EntrantsTest, Constructor) {
    Entrants e("Party A");
    EXPECT_EQ(e.GetName(), "Party A");
}

// Test case to check if the name can be set and retrieved correctly
TEST_F(EntrantsTest, SetName) {
    Entrants e("Party A");
    e.SetName("Party B");
    EXPECT_EQ(e.GetName(), "Party B");
}

// Test case to check if the initial vote count is 0
TEST_F(EntrantsTest, InitialVotes) {
    Entrants e("Party A");
    EXPECT_EQ(e.GetVotes(), 0);
}

// Test case to check if a vote can be added and retrieved correctly
TEST_F(EntrantsTest, AddVote) {
    Entrants e("Party A");
    e.AddVote(1);
    EXPECT_EQ(e.GetVotes(), 1);
}

// Test case to check if the vote count can be cleared correctly
TEST_F(EntrantsTest, ClearVote) {
    Entrants e("Party A");
    e.AddVote(1);
    e.ClearVote();
    EXPECT_EQ(e.GetVotes(), 0);
}



class IRVTest : public ::testing::Test {
    public:
    
        void SetUp() {
            
        }

};

TEST_F(IRVTest, ConstructorWithFilename) {
    // Create a temporary file with test data
    std::string test_data = "IR\n3\nAlice, Bob, Charlie\n3\n1,2,3\n2,1,3\n2,3,1\n";
    std::string filename = "temp.csv";
    std::ofstream outfile(filename);
    outfile << test_data;
    outfile.close();

    // Test the IRV constructor with the temporary file
    IRV irv(filename);
    EXPECT_EQ(irv.getFilename(), filename);

    // Remove the temporary file
    std::remove(filename.c_str());
}

TEST_F(IRVTest, GetCandidatesTest) {
  std::string test_data = "IR\n3\nAlice, Bob, Charlie\n3\n1,2,3\n2,1,3\n2,3,1\n";
  std::string filename = "temp.csv";
  std::ofstream outfile(filename);
  outfile << test_data;
  outfile.close();
  IRV irv(filename);

  std::vector<Entrants> candidates = irv.GetCandidates();
  EXPECT_EQ(candidates.size(), 3);
  EXPECT_EQ(candidates[0].GetName(), "Alice");
  EXPECT_EQ(candidates[1].GetName(), "Bob");
  EXPECT_EQ(candidates[2].GetName(), "Charlie");
}

TEST_F(IRVTest, TallyVotesTest) {
  std::string test_data = "IR\n3\nAlice, Bob, Charlie\n3\n1,2,3\n2,1,3\n2,3,1\n";
  std::string filename = "temp.csv";
  std::ofstream outfile(filename);
  outfile << test_data;
  outfile.close();
  IRV irv(filename);
  
  // Tally votes
  irv.TallyVotes();

  // Check that each candidate received the expected number of votes
  std::vector<Entrants> candidates = irv.GetCandidates();
  EXPECT_EQ(candidates[0].GetVotes(), 1);  // Alice
  EXPECT_EQ(candidates[1].GetVotes(), 1);  // Bob
  EXPECT_EQ(candidates[2].GetVotes(), 1);  // Charlie
}

TEST_F(IRVTest, EliminateTest) {
  std::string test_data = "IR\n3\nAlice, Bob, Charlie\n3\n1,2,3\n2,1,3\n2,3,1\n";
  std::string filename = "temp.csv";
  std::ofstream outfile(filename);
  outfile << test_data;
  outfile.close();
  IRV irv(filename);

  // First round of voting
  irv.TallyVotes();

  // Second round of voting
  irv.Eliminate();

  // Check that the eliminated candidate has been marked as such
  std::vector<Entrants> candidates = irv.GetCandidates();
  EXPECT_EQ(candidates[0].GetName(), "ELIMINATED");
  EXPECT_EQ(candidates[1].GetName(), "Bob");
  EXPECT_EQ(candidates[2].GetName(), "Charlie");

  // Third round of voting
  irv.TallyVotes();

  // Fourth round of voting
  irv.Eliminate();

  // Check that the eliminated candidate has been marked as such
  candidates = irv.GetCandidates();
  EXPECT_EQ(candidates[0].GetName(), "ELIMINATED");
  EXPECT_EQ(candidates[1].GetName(), "ELIMINATED");
  EXPECT_EQ(candidates[2].GetName(), "Charlie");
}


class TieHandlerTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }


};


TEST(TieHandlerTest, HandlesMultipleTies) {
    std::vector<Entrants> entrants = {Entrants("Party A"), Entrants("Party B"), Entrants("Party C"), Entrants("Party D")};
    entrants[0].AddVote(10);
    entrants[1].AddVote(10);
    entrants[2].AddVote(10);
    entrants[3].AddVote(10);

    std::vector<Entrants> resolved = TieHandler(entrants);
    ASSERT_EQ(resolved.size(), 1);
    EXPECT_TRUE(resolved[0].GetName() == "Party A" || resolved[0].GetName() == "Party B" || resolved[0].GetName() == "Party C" || resolved[0].GetName() == "Party D");
}


class POTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};

TEST(POTest, TallyVotesTest) {
    PO po("misc/POTEST.csv");
    po.TallyVotes();
    std::vector<Entrants> parties = po.GetParties();

    EXPECT_EQ(parties[0].GetVotes(), 3);
    EXPECT_EQ(parties[1].GetVotes(), 2);
    EXPECT_EQ(parties[2].GetVotes(), 0);
    EXPECT_EQ(parties[3].GetVotes(), 2);
    EXPECT_EQ(parties[4].GetVotes(), 1);
    EXPECT_EQ(parties[5].GetVotes(), 1);
}