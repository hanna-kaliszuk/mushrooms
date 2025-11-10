# MUSHROOM PICKING

This repository contains a C++ solution to the **“Na grzyby!” (Mushroom Picking)** problem from the ASD Laboratory (Algorythms & Data Structures course realised at the University of Warsaw). The task involves counting the number of valid paths through a grid-shaped forest where Bajtazar collects at least `k` mushrooms.

---

## PROBLEM OVERVIEW

You are given an `n × m` forest grid. Bajtazar starts at tree `(1,1)` and finishes at tree `(n,m)`. From each tree `(i,j)` he may move:

* **Down:** `(i+1, j)`
* **Up:** `(i−1, j)`
* **Right:** `(i, j+1)`

He cannot revisit any tree.

Some trees contain mushrooms. A mushroom-picking trip (a path from `(1,1)` to `(n,m)`) is considered successful if Bajtazar collects at least `k` mushrooms along the way.

You must count how many successful trips exist and print the last 9 digits of that number (omit leading zeros).

---

### INPUT FORMAT

```
n m k g
```

* `1 ≤ n, m ≤ 1000`
* `0 ≤ k ≤ 10`
* `0 ≤ g ≤ n × m`

Followed by `g` lines, each with two integers `a b` (`1 ≤ a ≤ n`, `1 ≤ b ≤ m`), giving the coordinates of trees with mushrooms.

---

### OUTPUT FORMAT

Output a single integer — the last 9 digits of the number of successful trips.

---

#### EXAMPLE

**Input:**

```text
2 3 2 3
1 2
2 1
2 2
```

**Output:**

```text
3
```

**Explanation:** There are 4 possible paths from `(1,1)` to `(2,3)`; 3 of them collect at least 2 mushrooms.

---

## ALGORITHM

The solution uses dynamic programming (DP) by columns.

Each DP state keeps track of:

* current row,
* number of mushrooms collected (`0..k`, clamped to `k`),
* direction of arrival (`from left`, `from above`, `from below`).

Only two DP layers are kept in memory (current and previous column). Transitions are performed in two passes per column (top→bottom and bottom→top) to handle vertical movements correctly.

**Final result:** sum of all ways to reach `(n,m)` with at least `k` mushrooms, modulo `1e9`.

---

#### COMPLEXITY

| Measure | Complexity                 |
| ------- | -------------------------- |
| Time    | `O(n × m × k)`             |
| Memory  | `O(n × k)` (two DP layers) |

Efficient for `n, m ≤ 1000`, `k ≤ 10`, and 512 MB memory limit.

---

## COMPILATION
```bash
g++ -std=c++17 -O2 -pipe main.cpp -o mushrooms
./mushrooms < input.txt > output.txt
```

