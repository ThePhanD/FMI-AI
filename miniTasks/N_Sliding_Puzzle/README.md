# N Sliding Puzzle
## IDA* search algorithm with Manhattan distance

### For input:
Board size: 8 for 3x3 board, 15 for 4x4 board, 24 for 5x5 board, etc.<br/>
Zero position: <br/>
For example in:<br/>
                       
| 0 | 1 | 2 |                           | 5 | 1 | 2 | <br/>
| 3 | 4 | 5 |  => zero position is 0;   | 3 | 7 | 0 |  => zero position is 5; <br/>
| 6 | 7 | 8 |                           | 6 | 4 | 8 | <br/>
       
Insert the elements of the board: <br/>
0 1 2 <br/>
3 4 5 <br/>
6 7 8 <br/>

### Example:

