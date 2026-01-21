

## Single Quorum
![Single Quorum](node_config_images/SingleQuorum.png "Single Quorum Configuration")
```cpp

    {{{0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}},
      {0, {0, 1, 2, 3, 4}}}};

```






## Multiple quorums variations

**UPPAAL Quorum Set Code 1 for config 1, 4**
```cpp
    {{{0, {0, 1, 2, N, N}}, // 0
      {0, {0, 1, 2, N, N}}, // 1
      {0, {0, 1, 2, N, N}}, // 2
      {0, {0, 1, 2, 3, N}}, // 3
      {0, {0, 1, 2, N, 4}}}}; // 4
```

for
![Multi Quorum1](node_config_images/MultiQuorums_1.png "Multiple Quorum Configuration1")
![Multi Quorum4](node_config_images/MultiQuorums_4.png "Multiple Quorum Configuration4")

**UPPAAL Quorum Set Code 2 for config 5**
```cpp
    {{{0, {0, N, 2, 3, 4}}, // 0
      {0, {N, 1, 2, 3, 4}}, // 1
      {0, {N, N, 2, 3, 4}}, // 2
      {0, {N, N, 2, 3, 4}}, // 3
      {0, {N, N, 2, 3, 4}}}}; // 4
```
for
![Multi Quorum5](node_config_images/MultiQuorums_5.png "Multiple Quorum Configuration5")

**UPPAAL Quorum Set Code 3 for config 2, 3**
```cpp
    {{{0, {0, 1, 2, N, 4}}, // 0
      {0, {N, 1, 2, N, 4}}, // 1
      {0, {N, 1, 2, N, 4}}, // 2
      {0, {N, 1, 2, 3, 4}}, // 3
      {0, {N, 1, 2, N, 4}}}}; // 4
```

for
![Multi Quorum2](node_config_images/MultiQuorums_2.png "Multiple Quorum Configuration2")
![Multi Quorum3](node_config_images/MultiQuorums_3.png "Multiple Quorum Configuration3")