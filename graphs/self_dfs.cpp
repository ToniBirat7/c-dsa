#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjList;

public:
    Graph(int size) {
        V = size;
        adjList.resize(size);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v); // Directed
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Neighbour of Node " << i << ": ";

            for (int neighbour : adjList[i]) {
                cout << neighbour << " ";
            }

            cout << "\n";
        }
    }

    void dfs(int u,vector<bool> &visitedNode) {
        visitedNode[u] = true;

        cout << u << " ";

        for (int v : adjList[u]) {
            if (!visitedNode[v]) {
                dfs(v, visitedNode);
            }
        }
    }
};

int main() {
    Graph g(8);

    vector<bool> visitedNodes(8, false);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 6);
    g.addEdge(4, 6);
    g.addEdge(4, 7);
    g.addEdge(6, 7);

    g.printGraph();

    cout << "Dfs : ";

    g.dfs(0, visitedNodes);

    return 0;
}

// To understand exactly what happens to the call stack during this process, we need to look at how a computer physically manages memory when functions call other functions recursively.

// When a function is called, the CPU allocates a **Stack Frame** (or Activation Record) for it. This stack frame stores:
// 1.  **The Parameters:** The value of `u` (e.g., `7`) and the reference to `visitedNode`.
// 2.  **The Loop State:** The current position (iterator) of the `for (int v : adjList[u])` loop.
// 3.  **The Return Address:** The exact line of code in the calling function where the CPU must jump back to once this current function finishes.

// ---

// ### The Storyboard: From Peak to Unwind

// Let’s trace the execution step-by-step, starting from the exact moment your call stack is at its deepest point.

// ---

// #### STEP 1: The Apex — Executing `dfs(7)`

// The stack is fully built. We are inside `dfs(7)`.

// ```text
// ================== CALL STACK (State 1) ==================
// [Frame 5] dfs(u=7)  <-- Active. Loop Iterator: Position 0 of adjList[7]
// [Frame 4] dfs(u=6)  <-- Waiting at loop: processing neighbor '7'
// [Frame 3] dfs(u=3)  <-- Waiting at loop: processing neighbor '6'
// [Frame 2] dfs(u=1)  <-- Waiting at loop: processing neighbor '3'
// [Frame 1] dfs(u=0)  <-- Waiting at loop: processing neighbor '1'
// [Frame 0] main()    <-- Waiting for dfs(0) to finish
// ==========================================================
// ```

// *   **What happens inside `dfs(7)`:** 
//     The CPU checks `adjList[7]`. Because Vertex 7 has no outgoing edges, `adjList[7]` is empty. 
//     The `for (int v : adjList[7])` loop has nothing to iterate over, so the loop is completely skipped.
// *   **The Return:** 
//     The CPU reaches the closing brace `}` of `dfs(7)`. It looks at the **Return Address** stored in `Frame 5`, which says: *"Return to the loop inside `dfs(6)`."*
//     `Frame 5` is popped off the stack and destroyed.

// ---

// #### STEP 2: Returning to `dfs(6)`

// With `dfs(7)` popped, `dfs(6)` is now back at the top of the stack and becomes the active frame.

// ```text
// ================== CALL STACK (State 2) ==================
// [Frame 4] dfs(u=6)  <-- Active. Loop Iterator: Finished neighbor '7'
// [Frame 3] dfs(u=3)  <-- Waiting...
// [Frame 2] dfs(u=1)  <-- Waiting...
// [Frame 1] dfs(u=0)  <-- Waiting...
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens inside `dfs(6)`:** 
//     We resume inside `dfs(6)`'s loop:
//     ```cpp
//     for (int v : adjList[6]) { // adjList[6] only contains [7]
//         dfs(v, visitedNode);   // We just returned from here
//     }
//     ```
//     The loop checks for the next neighbor. Since `7` was the only neighbor of `6`, the loop finishes.
// *   **The Return:** 
//     The CPU reaches the closing brace of `dfs(6)`. It looks at the return address in `Frame 4`, which says: *"Return to the loop inside `dfs(3)`."*
//     `Frame 4` is popped off the stack.

// ---

// #### STEP 3: Returning to `dfs(3)`

// `dfs(3)` becomes the active frame.

// ```text
// ================== CALL STACK (State 3) ==================
// [Frame 3] dfs(u=3)  <-- Active. Loop Iterator: Finished neighbor '6'
// [Frame 2] dfs(u=1)  <-- Waiting...
// [Frame 1] dfs(u=0)  <-- Waiting...
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens inside `dfs(3)`:** 
//     We resume inside `dfs(3)`'s loop:
//     ```cpp
//     for (int v : adjList[3]) { // adjList[3] only contains [6]
//         dfs(v, visitedNode);   // We just returned from here
//     }
//     ```
//     `3` has no more neighbors. The loop finishes.
// *   **The Return:** 
//     `dfs(3)` reaches its closing brace, looks at its return address, and pops `Frame 3`. We return to `dfs(1)`.

// ---

// #### STEP 4: Returning to `dfs(1)` (The Branch Point)

// This is the most critical phase. We are back in `dfs(1)`. Unlike the previous frames, `dfs(1)` has **not** finished its loop yet.

// ```text
// ================== CALL STACK (State 4) ==================
// [Frame 2] dfs(u=1)  <-- Active. Loop Iterator: Finished neighbor '3'. Next is '4'.
// [Frame 1] dfs(u=0)  <-- Waiting...
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens inside `dfs(1)`:**
//     We resume inside the loop of `dfs(1)`. 
//     ```cpp
//     for (int v : adjList[1]) { // adjList[1] contains [3, 4]
//         dfs(v, visitedNode);   // We just returned from the call for '3'
//     }
//     ```
//     Because `adjList[1]` contains another element (`4`), **the loop does not exit.** 
//     The iterator advances to `4`.
//     The CPU executes `dfs(4, visitedNode)`. 
//     This is where the stack starts growing again on a new branch.

// ---

// #### STEP 5: Branching Down to `dfs(4)`

// A brand-new stack frame is allocated for `dfs(4)` and pushed onto the stack.

// ```text
// ================== CALL STACK (State 5) ==================
// [Frame 3] dfs(u=4)  <-- Active. Loop Iterator: Position 0 of adjList[4]
// [Frame 2] dfs(u=1)  <-- Waiting... (Paused at neighbor '4')
// [Frame 1] dfs(u=0)  <-- Waiting... (Paused at neighbor '1')
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens inside `dfs(4)`:**
//     1.  `visitedNode[4]` is marked `true`.
//     2.  `4` is printed to the console.
//     3.  We look at `adjList[4]`, which contains `[6, 7]`.
//     4.  The loop `for (int v : adjList[4])` begins with the first neighbor, `6`.
//     5.  Because your code is missing the `if (!visitedNode[v])` check, **it does not matter that Vertex 6 was already visited during Step 2.** The CPU blindly calls `dfs(6, visitedNode)`.

// ---

// #### STEP 6: Re-entering `dfs(6)` (The Duplicate Call)

// A new stack frame is created for `dfs(6)`. Notice how `dfs(6)` is back on the stack, but this time its parent is `dfs(4)` instead of `dfs(3)`.

// ```text
// ================== CALL STACK (State 6) ==================
// [Frame 4] dfs(u=6)  <-- Active. Loop Iterator: Position 0 of adjList[6]
// [Frame 3] dfs(u=4)  <-- Waiting... (Paused at neighbor '6')
// [Frame 2] dfs(u=1)  <-- Waiting...
// [Frame 1] dfs(u=0)  <-- Waiting...
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens here:**
//     1.  `visitedNode[6]` is set to `true` (again).
//     2.  `6` is printed to the console (again).
//     3.  `adjList[6]` contains `[7]`.
//     4.  The loop inside this new `dfs(6)` begins and calls `dfs(7, visitedNode)`.

// ---

// #### STEP 7: Re-entering `dfs(7)`

// A new stack frame is created for `dfs(7)`.

// ```text
// ================== CALL STACK (State 7) ==================
// [Frame 5] dfs(u=7)  <-- Active. Loop Iterator: Position 0 of adjList[7]
// [Frame 4] dfs(u=6)  <-- Waiting... (Paused at neighbor '7')
// [Frame 3] dfs(u=4)  <-- Waiting...
// [Frame 2] dfs(u=1)  <-- Waiting...
// [Frame 1] dfs(u=0)  <-- Waiting...
// [Frame 0] main()
// ==========================================================
// ```

// *   **What happens here:**
//     1.  `visitedNode[7]` is set to `true` (again).
//     2.  `7` is printed to the console (again).
//     3.  `adjList[7]` is empty.
//     4.  This `dfs(7)` frame pops, returning control to `dfs(6)` at `Frame 4`.

// This process of building up, unwinding, branching, and rebuilding is how recursive backtracking works. Under normal DFS, the `if (!visitedNode[v])` check acts as a shield, preventing Steps 6 and 7 from ever pushing duplicate frames onto the stack.