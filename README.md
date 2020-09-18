# Introduction
This work is built from this paper [SIFA: Exploiting Ineffective Fault Inductions on Symmetric Cryptography](https://ojs.ub.rub.de/index.php/TCHES/article/view/7286)

Strictly, I don't complete the SIFA because of my lack of faulty knowledge.

From now ,I have completed the Ineffective part,in this context, we can recover the first byte of the last round key with a stuck-0 faulty.

# Use

command
'''shell
make
'''
to generate input,key and output,
then, command 
'''shell
cd handle
make
'''
to get the right key guess.

# Todo
  Test new faulty

  add Statistic