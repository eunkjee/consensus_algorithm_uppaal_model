// processMessageNomination -- blocking threshold check for accept nomination
        /* FM1
            FAULTY ACTION: REJECT 'v' against the blocking set's decision
            (original: .accepted[v] = true;)
        */
        if (
            cntValues > (getTotalValidators(myID) - qs[slotCur][myID].threshold) // blocking threshold
            && !nominationStates[myID].accepted[v]
        ) {
            nominationStates[myID].accepted[v] = false;
        }

        /* FM2
            FAULTY ACTION: ACCEPT 'v' below blocking threshold
            (original: if (cntValues > (...)){ })
        */
        if (
            cntValues <= (getTotalValidators(myID) - qs[slotCur][myID].threshold) // blocking threshold
            && !nominationStates[myID].accepted[v]
        ) {
            nominationStates[myID].accepted[v] = true; 
            nominationStates[myID].voted[v] = false;
        }

// processMessageNomination -- quorum threshold check for vote nomination
        /* FM3
            FAULTY ACTION: REJECT 'v' despite exceeding threshold 
            (original: accepted[v] = true;)
        */
        if (cntValues >= qs[slotCur][myID].threshold
            && !nominationStates[myID].accepted[v]) {
            nominationStates[myID].accepted[v] = false;
        }

        /* FM4
            FAULTY ACTION: ACCEPT 'v' below threshold
            (original: if (cntValues >= (...)) { })
        */
        if (cntValues < qs[slotCur][myID].threshold
            && !nominationStates[myID].accepted[v]) {
            nominationStates[myID].accepted[v] = true;
            nominationStates[myID].voted[v] = false;
        }

// processMessageNomination -- quorum threshold check for accept nomination
        /* FM5
            FAULTY ACTION: REJECT 'v' despite exceeding threshold 
            (original: accepted[v] = true;)
        */
        if (cntValues >= qs[slotCur][myID].threshold) {
            if (!nominationStates[myID].accepted[v]) {
                nominationStates[myID].accepted[v] = false;
            }

            if (!nominatedValues[myID][v]) {
                nominatedValues[myID][v] = true;
                if (hasNominatedValues == false) {
                    canTick[myID] = false;
                }
            }
        }

        /* FM6
            FAULTY ACTION: ACCEPT 'v' below threshold
            (original: if (cntValues >= (...)) { })
        */
        if (cntValues < qs[slotCur][myID].threshold) {
            if (!nominationStates[myID].accepted[v]) {
                nominationStates[myID].accepted[v] = true;
                nominationStates[myID].voted[v] = false;
            }

            if (!nominatedValues[myID][v]) {
                nominatedValues[myID][v] = true;
                if (hasNominatedValues == false) {
                    canTick[myID] = false;
                }
            }
        }