# Processor Pipeline Simulator
Simple processor in-order pipeline simulator.
Models how each instruction move through the 5 stages of the pipeline.

## Installation
1. Download proj2.tar.gz

2. Unzip the tar.gz:
```bash
tar xvzf proj2.tar.gz
```

3. Make the executable file:
```bash
make proj2 
```

## Run
```
./proj2 trace_file_name start_inst inst_count W
```

### Parameters
| Parameter | Description|
|:---------: | :----------|
| trace_file_name | Name of the trace file |
| start_inst | Instruction number to start the simulation |
| inst_count | Number of instructions to simulate |
| W | Pipeline width |

### trace_file 
Trace files can be found here: https://www.microarch.org/cvp1/

## Simulation Information
5-stage pipeline: Instruction Fetch (IF), Instruction Decode and Read Operands (ID), Instruction Issue and Execute (EX), Memory access (MEM), and writeback results/retire (WB). 
Process has a W-wide superscalar. Instructions proceed to the next stage as long as they have no dependencies. 
Processor has 1 integer ALUY unit, 1 floating point unit, 1 branch execution unit, 1 read port from L1 data cache, and 1 write port into L1 data cache.

### Input Trace
Each line represents an instruction with comma seperated values, they contain.
| Value | Description|
|:----: | :----------|
| Program counter (PC) | Hexadecimal value, representing the instruction address |
| Instruction type | Value between 1 to 5. View below for types|
| Dependencies | List of PC values which current instruction depends on | 

#### Instruction Type
| Type | Value | Description |
|:---: |:---: |:-----------|
| Integer | 1 | Uses integer ALU |
| Floating point | 2| Uses floating point unit |
| Branch | 3 | Transfer control to next instruction  |
| Load | 4 | Reads value from memory |
| Store | 5 | Writes value form memory |

### Dependences
| Dependent | Description|
|:---------: | :----------|
| Structural hazards | Integer instruction cannot be execute with another integer instruction. Floating point instruction cannot be execute with another floating point instruction. Branch instruction cannot be execute with another branch instruction. Load instruction cannot go to MEM stage with another load instruciton. Store instruction cannot go to the MEM stage with another store instruction. |
| Control hazards | Branch instruction halts instructions fetch until branch executes |
| Data hazards | Instruction cannot be executed until all its data dependences satisfied. Dependence on integer or floating point instruction is satisifed after they executed. Dependence on load and store instruction is satisfied after they memorized. |

### Report Generation
A report will be generated at the end of the simulation. The report includes...
- Total execution time (in cycles)
- Histogram containing breakdown of retired instructions by instruciton type.

## Implementation Information
### Classes
| Class | Description|
|:---------: | :----------|
| Main | Handles inputs for simulation |
| PipelineSimulation | Handles main simulation while loop and functions | 
| InstructionManager | Handles instruciton queues |
| TraceInput | Handles trace file | 
| StatsManager | Handles report |
| Instruction | Holds all instruction information |
