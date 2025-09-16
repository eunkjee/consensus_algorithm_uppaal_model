/* Full Quorum */
    {{{0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}}}};

/* 2-Quorum variations */
// Config 1. faulty nodes outside quorum intersection {0, 1, 2} (faulty nodes up to 2, '#3, #4')
    {{{0, {0, 1, 2, N, N}}, // 0
      {0, {0, 1, 2, N, N}}, // 1
      {0, {0, 1, 2, N, N}}, // 2
      {0, {0, 1, 2, 3, N}}, // 3
      {0, {0, 1, 2, N, 4}}}}; // 4

// Config 2. faulty nodes inside quorum intersection {2, 3, 4} (up to 3, '#2, #3, #4')
    {{{0, {0, N, 2, 3, 4}}, // 0
      {0, {N, 1, 2, 3, 4}}, // 1
      {0, {N, N, 2, 3, 4}}, // 2
      {0, {N, N, 2, 3, 4}}, // 3
      {0, {N, N, 2, 3, 4}}}}; // 4

// Config 3. faulty nodes in & outside quorum intersection {1, 2, 4} ('#3(out), #4(in)')
    {{{0, {0, 1, 2, N, 4}}, // 0
      {0, {N, 1, 2, N, 4}}, // 1
      {0, {N, 1, 2, N, 4}}, // 2
      {0, {N, 1, 2, 3, 4}}, // 3
      {0, {N, 1, 2, N, 4}}}}; // 4