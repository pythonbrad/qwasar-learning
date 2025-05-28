# Welcome to Quest Shell Awk
***

## Task
The task consisted to learn the basics of awk.

## Description
awk is a program that we can use for searching in a file.
Basically, an awk program looks like below.
```
pattern { action } // The default action is 'print'
```
And can be run using the awk commmand.
```
awk 'program' input-file
```

## Installation
For this task, you will need to download a dataset.
```
wget https://storage.googleapis.com/qwasar-public/track-cloud-devops/awkard.txt -O input.txt
```

## Usage

ex00: Display all lines containing the word "is".

```
awk '/is/' input.txt
```

ex01: Display all lines containing no more than 2 fields.

```
awk 'NF < 3'
# or
awk 'NF < 3 { print }'
```

### The Core Team
Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
