# Phase 3 – Election Management & State Management

## Objective

The objective of Phase 3 is to implement the election management logic and
control the complete lifecycle of an election using a well-defined state
management system.

The phase will introduce an Election Manager class and an ElectionStatus
enumeration to ensure that an election follows valid lifecycle transitions.

---

## Phase 3 Scope

The following components will be implemented:

1. ElectionStatus enum
2. Election Manager class
3. Election lifecycle management
4. State transition validation
5. Election information/status methods
6. Error/invalid transition handling
7. Testing of all valid and invalid states

---

# 1. ElectionStatus

An enum class will be created to represent the current state of an election.

Possible states:

- NOT_STARTED
- ONGOING
- ENDED

Example lifecycle:

NOT_STARTED → ONGOING → ENDED

The election state should only change through valid operations.

---

# 2. Election Manager Class

An Election Manager class will be responsible for managing the election.

Possible responsibilities:

- Store election information
- Maintain current election status
- Start the election
- End the election
- Return the current status
- Display election information
- Validate state transitions

Possible data members:

- election ID
- election name
- election status

The data members will be kept private to maintain encapsulation.

---

# 3. Election Lifecycle Rules

The election will follow these rules:

| Current State | Operation | Result |
|---------------|-----------|--------|
| NOT_STARTED | Start Election | ONGOING |
| ONGOING | End Election | ENDED |
| ENDED | Start Election | Invalid |
| NOT_STARTED | End Election | Invalid |
| ONGOING | Start Election | Invalid |
| ENDED | End Election | Invalid |

The system must prevent invalid state transitions.

---

# 4. Start Election

The startElection() method will:

1. Check the current election status.
2. Allow the election to start only if the status is NOT_STARTED.
3. Change the status to ONGOING.
4. Reject the operation if the election has already started or ended.

---

# 5. End Election

The endElection() method will:

1. Check the current election status.
2. Allow the election to end only when the status is ONGOING.
3. Change the status to ENDED.
4. Reject the operation if the election has not started or has already ended.

---

# 6. State Validation

State validation will be implemented inside the Election Manager class.

The class will ensure that:

- An election cannot be started twice.
- An election cannot be ended before it starts.
- An ended election cannot be restarted.
- An ended election cannot be ended again.

This will maintain the integrity of the election lifecycle.

---

# 7. Encapsulation

The election data and status will be kept private.

Public methods will be provided to interact with the election.

Example:

private:
- electionId
- electionName
- status

public:
- startElection()
- endElection()
- getStatus()
- displayElection()

This prevents external code from directly modifying the election status.

---

# 8. Constructor

A constructor will initialize the election object.

When an election object is created:

- Election ID will be initialized.
- Election name will be initialized.
- Election status will automatically be set to NOT_STARTED.

Example:

Election election("E001", "General Election");

Initial state:

NOT_STARTED

---

# 9. Testing Plan

The following test cases will be performed.

### Test Case 1 – Initial State

Create a new election.

Expected:

NOT_STARTED

---

### Test Case 2 – Start Election

Call:

startElection()

Expected:

NOT_STARTED → ONGOING

---

### Test Case 3 – Start Already Running Election

Call startElection() again.

Expected:

Operation rejected.

---

### Test Case 4 – End Election

Call:

endElection()

Expected:

ONGOING → ENDED

---

### Test Case 5 – Restart Ended Election

Call:

startElection()

Expected:

Operation rejected.

---

### Test Case 6 – End Ended Election

Call:

endElection()

Expected:

Operation rejected.

---

### Test Case 7 – End Before Starting

Create a new election and directly call:

endElection()

Expected:

Operation rejected.

---

# 10. Implementation Order

The implementation will be completed in the following order:

Step 1:
Create ElectionStatus enum.

Step 2:
Create Election Manager class.

Step 3:
Add private election data members.

Step 4:
Add constructor.

Step 5:
Implement getStatus().

Step 6:
Implement startElection().

Step 7:
Implement endElection().

Step 8:
Implement state validation.

Step 9:
Implement display/status functionality.

Step 10:
Test all valid and invalid state transitions.

Step 11:
Integrate Phase 3 with the existing project.

---

# 11. Expected Result

After completing Phase 3, the system should be able to:

- Create an election.
- Maintain its current state.
- Start an election.
- End an election.
- Prevent invalid state transitions.
- Display the current election status.
- Maintain proper encapsulation.
- Integrate election lifecycle logic with the existing voting system.

---

# 12. Deliverables

The following will be delivered as part of Phase 3:

- ElectionStatus implementation
- Election Manager implementation
- Election lifecycle logic
- State validation
- Test cases
- Updated project documentation
- Integration with previous phases