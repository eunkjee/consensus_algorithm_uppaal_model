// ** for (3-4-3) open membership node system
// ** copy and paste the entire code below in (Global) Declarations
// ------------------------------------------
        
/// ----- ** GLOBAL CONSTANTS
/*
    if F != 0, 
    `FaultyNodeNomination`, `FaultyNodeBallot` should be added in System declarations.
*/
const int THRESHOLD_PERCENT = 100; // Quorum Set Agreement Percentage for Quorum Slice Formation (System-wide)
const int N = 4; // total number of nodes
const int F = 0; // total number of faulty nodes
const int V = 3; // maximum number of values in nomination state

const int INFINITY = 15;
const int BOUNDARY = 14;

const int SLOTMAX = V-1; // slot max index

// ** states for NominationBallot
const int SCPPrepare = 0;
const int SCPConfirm = 1;
const int SCPExternalize = 2;

/// ------ ** TYPE DEFINITIONS

typedef int[0,N-F-1] n_id;     // node id (0 to n-f-1)
typedef int[N-F,N-1] f_id;     // fault node id (n-f to n-1)
typedef int[0,V-1] v_id;       // value id (0 to v-1)
typedef int[0,SLOTMAX] s_id;   // slot id
typedef int[0,N-1] t_id;       // tick id

typedef struct {
    int[0,N] threshold;
    int[0,N] validators[N]; // reserving as many as N, stores ids
} SCPQuorumSet;

// nomination
typedef struct {
    bool voted[V];
    bool accepted[V];
} SCPNominationState;

// ballot
typedef struct {
    int[0,INFINITY] counter;
    bool value[V];
} SCPBallot;

typedef struct {
    /* `curState`
        SCPPrepare = 0;
        SCPConfirm = 1;
        SCPExternalize = 2;
    */
    int[0,2] curState;
    SCPBallot b;
    SCPBallot p;
    SCPBallot pp;
    SCPBallot h;
    SCPBallot c;
} SCPBallotState;
SCPBallotState ballotStates[N];


/// ------ ** Node configurations
/// ------- - modify here after change N, F values

// total participants involved for each value
// used in Slot management

const int totalParticipants[V] = {3, 4, 3};

const bool NOVALUE[V] = // empty values (no values)
    {false, false, false};


bool higherlayerInput[N][V] =
    // 25.07.16
    // Assumes the values are always correct based on the modeling abstaction level.
    // indicates if a node has a value to be written.
    {{true, true, true}, 
     {true, true, true},
     {true, true, true},
     {true, true, true}};

SCPQuorumSet qs[V][N] =
    // represents an invalid validator as N (e.g., {0, 1, N})
    // {threshold, {validators[N]}}
    {
      {{0, {0, 1, 2, N}}, // 0
        {0, {0, 1, 2, N}}, // 1
        {0, {0, 1, 2, N}}, // 2
        {0, {N, N, N, N}}}, // 3 -- 3 not joined
      {{0, {0, 1, 2, 3}}, // 0
        {0, {0, 1, 2, 3}}, // 1
        {0, {0, 1, 2, 3}}, // 2
        {0, {0, 1, 2, 3}}}, // 3 -- 3 joined
      {{0, {0, 1, 2, N}}, // 0
        {0, {0, 1, 2, N}}, // 1
        {0, {0, 1, 2, N}}, // 2
        {0, {N, N, N, N}}} // 3 -- 3 not joined
    }; 

SCPNominationState nominationStates[N] =
    // voted                  accepted
    {{{false, false, false}, {false, false, false}},
     {{false, false, false}, {false, false, false}},
     {{false, false, false}, {false, false, false}},
     {{false, false, false}, {false, false, false}}};

bool nominatedValues[N][V] =
    {{false, false, false},
     {false, false, false},
     {false, false, false},
     {false, false, false}};

bool ballotDone[N] =
    {false, false, false, false};

bool tickReady[N] =
    {true, true, true, true};

int[0,INFINITY] tickNomination[N] =
    {0, 0, 0, 0};
    
int[0,INFINITY] tickBallot[N] =
    {0, 0, 0, 0};
    
int[0,INFINITY] cur_nRound[N] = // current running nomination round states of each node
    {0, 0, 0, 0};

int[0,INFINITY] cur_b_cnt[N] =
    {0, 0, 0, 0};
    


/// ----- ** CHANNELS
chan sthNominated[N];
chan nominationDone[N];

chan slotDone;

chan tickAdvanceBallot[N];
chan tickAdvance[N];
chan tickAdvanceDone[N];

/// broadcast channels
broadcast chan slotSuccess;
broadcast chan slotFail;
broadcast chan slotTimeout;
broadcast chan slotStarted[SLOTMAX+1];

broadcast chan tickStart;
broadcast chan tickStop;
broadcast chan tickManagerStart; // for TickTestApp



/// ----- ** VARIABLES
int[0,SLOTMAX] slotCur = 0; // current slot pointer


/// ------ ** METHODS
bool isLessValue(const bool &valueL[V], const bool &valueR[V]) {
    // check if valueL < valueR

    int[-1, V-1] i;

    for (i = V-1; i >= 0; i--) {
        if (valueL[i] == false && valueR[i] == true) {
            return true;
        } else if (valueL[i] == true && valueR[i] == false) {
            return false;
        }
    }
    return false; // valueL == valueR
}

int getTotalValidators(const int[0,N] curNodeID) {
    /*
        parameter: int curNodeID (range: 0 to N)
        return: int

        Count how many validators `curNodeID` has.
    */
    int[0,N] totalValidators = 0;

    for (i : int[0,N-1]) {
        if (qs[slotCur][curNodeID].validators[i] != N) {
            totalValidators++;
        }
    }
    return totalValidators;
}