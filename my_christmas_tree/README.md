# Welcome to My Christmas Tree
***

## Task
The task consisted to display a chrismas tree.

## Description
To accomplish the task, i gone through the following steps:
- understand the logic behind the building of the tree (the growing)
- break the problem in smaller ones
- determine the middle of a tree for subtree aligments

From what i got, the chrismas tree is composed of n subtrees.
Each subtree has his width and height.
The dimension of a nth subtree can be obtained by:
- `height = 4 + nth - 1`.
- `width(nth) = (2 + nth) x 2 + width(nth-1) with width(1) = 1`

For the alignment, we can determine the start point of the the nth subtree by 
`start_point(nth) = (width(last) - width(nth)) / 2`

## Installation
You need to have the gcc compiler to compile.
```
gcc -o tree tree.c
```

## Usage
```
gcc -o tree tree.c && tree <size>
```

### The Core Team
Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
