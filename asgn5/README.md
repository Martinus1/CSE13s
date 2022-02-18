# RSA Cryptography

Cryptography is a way to ensure safe file transfer between two parties

## Usage

We need to start by producing RSA public and private key pairs, for which we use the command-line command: 

##
`./keygen`

bellow are the possible command-line options:

> **Optional**

`-h [file]`

prints program synopsis and usage.

`-v`

enable ***verbose***, Output

`-b [bits]`

minimum number of bits needed for public key n (default: 256)

`-i [iterations]`
 
specifies the number of iterations the encrypt is going to go over. The default is **50**

`-n [pbfile]`

specifies the public key file(default rsa.pub)

`-d [pvfile]`

 Private Key file(default: rsa.priv)

`-s [seed]`

Specifies random seed

##

Now we can use the RSA algorithm to encrypt out files with the command-line command: 

`./encrypt`

bellow are the possible command-line options:

> **Optional**

`-h [file]`

prints program synopsis and usage.

`-v`

enable ***verbose***, Output

`-i [infile]`
 
specifies the input file (default: stdin)

`-o [outfile]`

specifies the output file (default: stdout)

`-n [pubfile]`

 public Key file(default: rsa.pub)


##

Now we can use the RSA algorithm to decrypt out files with the command-line command: 

`./decrypt`

bellow are the possible command-line options:

> **Optional**

`-h [file]`

prints program synopsis and usage.

`-v`

enable ***verbose***, Output

`-i [infile]`
 
specifies the input file (default: stdin)

`-o [outfile]`

specifies the output file (default: stdout)

`-n [pvfile]`

 private Key file(default: rsa.priv)


## Info

Created by Martin Michalko for CSE13s Assignment 5, in Winter of 2022
