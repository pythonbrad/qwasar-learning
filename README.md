# Welcome to Quest Shell Sed
***

## Task
The task consist to use sed for text manipulation.

## Description
To solve this task, i used patterns.

## Installation
You need to download the dataset.

```
mkdir -p ex00
wget 'https://storage.googleapis.com/qwasar-public/track-cloud-devops/sedance.txt' -O ex00/my_first_sed.txt
mkdir -p ex01
wget 'https://storage.googleapis.com/qwasar-public/track-cloud-devops/sedance.txt' -O ex01/my_first_sed_inplace.txt
```

## Usage
- Exercise 0
```
sed 's/\<5\>/five/g' ex00/my_first_sed.txt
```

- Exercise 1
```
sed -i 's/\<5\>/five/g' ex01/my_first_sed_inplace.txt
```

### The Core Team
Brady Fomegne


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
