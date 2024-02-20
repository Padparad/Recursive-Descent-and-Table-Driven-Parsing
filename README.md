# Recursive-Descent-and-Table-Driven-Parsing

Given a parsable grammar, we constructed a recursive-descent parser for the grammar using parsing functions and a table-driven parser.

Part1:
This part contains nodes and print function. 
Every nodes will save the nodes and expression according to 

⟨E⟩ → ⟨T⟩ ⟨W⟩ 
⟨W⟩ → | ⟨E⟩ | ϵ 
⟨T⟩ → ⟨F⟩ ⟨D⟩ 
⟨D⟩ → & ⟨T⟩ | ϵ 
⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩ 
⟨S⟩ → ⟨B⟩ ⟨K⟩ 
⟨K⟩ → ⟨S⟩ | ϵ 
⟨B⟩ → 0 | 1

Part2:
A structure of stack is established, containing an array and its size. To use this structure, there are push(), pop(), and peek(). 

Another structure of parsing table is used to store the table.
Repeal function:
The readstr() function will read the input string from the user and use the input to activate both 
Parts. Part1 and part2's main function are linked by recursion.
