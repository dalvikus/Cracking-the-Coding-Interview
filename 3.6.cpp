/**
    3.6 Write a program to sort a stack in ascending order.
    You should not make any assumptions about how the stack is implemented.
    The following are the only functions that should be used to write this program:
        push | pop | peek | isEmpty.

    Stack:
        2   top
        5
        3
        9   bottom

    Use two additional stacks like Hanoi Tower.

    originalStack
    orderedStack
    temporaryStack

    while originalStack is not empty:
        pop a from originalStack
        keep = true
        while (originalStack is not empty and keep is true) {
            peek b from originalStack
            compare a and b
            if a > b
                pop b from originalStack
                push b onto temporaryStack
            else
                keep = false
        }
        push a onto originalStack
        while (temporaryStack is not empty)
            pop b from temporaryStack
            push b onto originalStack

    If we use a counter for temporaryStack, originalStack can be used as temporaryStack.
 */
