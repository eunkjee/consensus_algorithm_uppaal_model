// ** copy and paste the entire code below in NodeFaultyNomination Declarations
// ------------------------------------------


void resetNominationState() {
    /*
        A method to reset nomination state
        when a state goes back to `StartNomination`
    */
    cur_nRound[myID] = 0;
    tickNomination[myID] = 0;

    for (v : v_id) {
        nominatedValues[myID][v] = false;
        nominationStates[myID].voted[v] = false;
        nominationStates[myID].accepted[v] = false;
    }
}

void initNominationState() {
    /*
        A method to init nomination state
        when a state starts from `StartNomination` to `NominationStarted`
    */
    int[0,N] totalValidators = getTotalValidators(myID);

    if (qs[slotCur][myID].threshold == 0) { 
        // update a threshold in `qs` for nodeID (the template parameter)
        int thr_numerator = totalValidators*THRESHOLD_PERCENT;
        qs[slotCur][myID].threshold = (thr_numerator % 100 == 0) 
                                        ? thr_numerator/100 
                                        : thr_numerator/100 + 1;
    }
}

void processMessageNomination(bool hasNominatedValues) {
    int[0,N] cntValues = 0; // node count
    int[0,N] cntValues_qs = 0; // node count in quorum set

    // blocking threshold check for accept nomination
    for (v : v_id) {
        cntValues = 0;

        // how many validators have accepted on `v`
        /* 
          For the current node
          - qs[slotCur][myID]: quorum set
          - qs[slotCur][myID].validators[n]: a validator
          - qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id]: a nested validator (validator's validator)
        */

        for (id : int[0,N-1]) {
            if (
                qs[slotCur][myID].validators[id] != N
                && qs[slotCur][myID].validators[id] != myID
                && nominationStates[
                    qs[slotCur][myID].validators[id]
                ].accepted[v]
            ) {
                cntValues++; // count for acceptance of my validators on `v`
            }
        }
        /// ** ----- FAULTY ACTION APPLICATION POINT ---- ** ///
        if (
            cntValues > (getTotalValidators(myID) - qs[slotCur][myID].threshold) // blocking threshold
            && !nominationStates[myID].accepted[v]
        ) {
            nominationStates[myID].accepted[v] = false;
        }
        
    }

    // quorum threshold check for vote nomination
    for (v : v_id) {
        cntValues = 0;

        for (id : int[0,N-1]) {
            if (qs[slotCur][myID].validators[id] != N) { 
                // check my validator's quorum slices
                cntValues_qs = 0;
                for (qs_id : int[0,N-1]) {
                    if (qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id] != N) {
                        if (
                            nominationStates[
                                qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id]
                            ].accepted[v]
                        ) {
                            cntValues_qs++;
                        }
                        else if (
                            nominationStates[
                                qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id]
                            ].voted[v]
                        ) {
                            cntValues_qs++;
                        }
                    }
                }

                if (cntValues_qs >= qs[slotCur][qs[slotCur][myID].validators[id]].threshold) {
                    cntValues++;
                }
            }
        }
        /// ** ----- FAULTY ACTION APPLICATION POINT ---- ** ///
        if (cntValues >= qs[slotCur][myID].threshold
            && !nominationStates[myID].accepted[v]) {
            nominationStates[myID].accepted[v] = false;
        }
    }

    // quorum threshold check for accept nomination
    for (v : v_id) {
        cntValues = 0;

        for (id : int[0,N-1]) {
            if (qs[slotCur][myID].validators[id] != N) {
                cntValues_qs = 0;

                // check my validator's quorum slices
                for (qs_id : int[0,N-1]) {
                    if (qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id] != N) {
                        if (
                            nominationStates[
                                qs[slotCur][qs[slotCur][myID].validators[id]].validators[qs_id]
                            ].accepted[v]
                        ) {
                            cntValues_qs++;
                        }
                    }
                }

                if (cntValues_qs >= qs[slotCur][qs[slotCur][myID].validators[id]].threshold) {
                    cntValues++;
                }
            }
        }
        /// ** ----- FAULTY ACTION APPLICATION POINT ---- ** ///
        if (cntValues >= qs[slotCur][myID].threshold) {
            if (!nominationStates[myID].accepted[v]) {
                nominationStates[myID].accepted[v] = false;
            }
        }
    }
}

int getHighestPriorityNode(int[0,MAXCNT] cur_round_in) {
    int[0,N] highest = cur_round_in % getTotalValidators(myID);
    int[0,N] current = 0;

    for (id : int[0,N-1]) {
        if (qs[slotCur][myID].validators[id] != N) {
            if (current == highest) { 
                return qs[slotCur][myID].validators[id];
            }
            else {
                current++;
            }
        }
    }

    return myID;
}

void getMyHigherlayerInput() {
    for (v : v_id) {
        if (higherlayerInput[myID][v]
            && !nominationStates[myID].accepted[v]
            && !nominationStates[myID].voted[v]) {
            nominationStates[myID].voted[v] = true;
            return;
        }
    }
}

void doEchoing(int[0,N] nodeIDHighest) {
    /*
        For v-th value,
        if (highest node `voted` or `accepted` on it) and 
            nodeID(current node) has not voted or accepted on it,

        nodeID follows the highest node's decision.
    */
    for (v : v_id) {
        if (
            (nominationStates[nodeIDHighest].accepted[v]
                || nominationStates[nodeIDHighest].voted[v])
            && !nominationStates[myID].accepted[v]
            && !nominationStates[myID].voted[v]
        ) {
            nominationStates[myID].voted[v] = true;
        }
    }
}

void newRound(bool hasNominatedValues) {
    int[0,N] nodeIDHighest;

    // check if itself exists in its quorum set
    if (qs[slotCur][myID].validators[myID] == myID) {
        
        // if its nomination tick reaches its current round value
        if (tickNomination[myID] == cur_nRound[myID]) {
            
            // nomination message passing
            processMessageNomination(hasNominatedValues);

            // mark as proceeding next round
            if (cur_nRound[myID]<MAXCNT) {
                cur_nRound[myID]++;
            }

            // only if it does not have nominated values
            // if it has some, it won't suggest or vote for new values
            if (!hasNominatedValues) {
                
                /// ** ----- FAULTY ACTION APPLICATION POINT ---- ** ///
                // get a leader
                nodeIDHighest = getHighestPriorityNode(cur_nRound[myID]);
                if (nodeIDHighest == myID) {
                    // if leader is self, get and vote for a higher layer input.
                    getMyHigherlayerInput();
                }
                else {
                    // else, vote for the leader's value
                    doEchoing(nodeIDHighest);
                }
            }
            // reset its nomination tick counter
            tickNomination[myID] = 0;
        }
        // else, increase the tick
        if (tickNomination[myID] < cur_nRound[myID]) {
            tickNomination[myID]++;
        }
    }
}