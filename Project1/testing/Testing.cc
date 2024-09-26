#include "gtest/gtest.h"
#include "../src/include/Audit.h"
#include "../src/include/Ballot.h"
#include "../src/include/CPL.h"
#include "../src/include/Entrants.h"
#include "../src/include/IRV.h"
#include "../src/include/TieHandler.h"

// #include <vector>
// #include <string>
// #include <iosteam>

// INCOMPLETE RAN OUT OF TIME

class AuditTest : public ::testing::Test {
    public:
        Audit testing = Audit();
        void SetUp() {
            testing.UpdEntrants(20);
            testing.UpdBallot(4);
            testing.UpdWinner("TESTING_ENTRANT");
            testing.UpdDate("3/15/2023");
            Entrants newEntrant = Entrants("JeffreyBezos");
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


class CPLTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};


class EntrantsTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};

class IRVTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};

class TieHandlerTest : public ::testing::Test {
    public:
        void SetUp() {
            
        }
};

