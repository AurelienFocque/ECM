This is an implementation of Elliptic Curve Method for integer factorisation.

This uses GMP library and C++ Language.

To make it smoother, I built an Abstraction over big integers and Elliptic curves points using operator overloads.

This forced me to use a garbage collection technique.

An expression like a+b will allocate memory for result and trigger a flag that says the value is a result.

When using a BigInteger in a fonction, the developper needs to check the flag of the operands and delete them if the flag is active to avoir memoryleak.

I tested memory leaks, and it seems that, the memory taken by the programm is stable.

Every operation like + * / makes an useless copy. To improve code, you should use +=, *=, %= etc everytime you can.

