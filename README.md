
# Content

This repository is my answer to the interneship test from [here](https://github.com/yoann-dufresne/bloomtest).
In this project I used a cmake file to facilitate compilation. So cmake program is requiered to compile.

# Compilation

From the root directory

```bash
  cmake .
  make
```

# Run the code

From root directory after compilation:

```bash
  # binary     
  ./bloom_test <dataset>.fasta k bits functions queries
```


# Results over the datasets

Command used (31-mers, 1GB bloom filter, 3 hash functions, 10000 requests):
```bash
  time ./bloom_test <dataset>.fasta 31 8589934592 3 10000
```

* Sars

real  0m0,436s  
user  0m0,107s  
sys 0m0,329s  
 
0/10000 random kmer found

* e.coli

real  0m1,900s  
user  0m1,561s  
sys 0m0,336s  

0/10000 random kmer found


* Human chr1

real  3m31,575s  
user  3m30,451s  
sys 0m1,108s  

86/10000 random kmer found
