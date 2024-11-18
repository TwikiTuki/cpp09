### REVERSE POLISH NOTAION

#### What is reverse polis notation?
> The reverse polish notation, invented by Charles Leonar Hamblin, consist in alternative method to express mathematic operations. 

> In this method the numbers for a given operation are introduced and stored in a stack before the operation itself. Then when an operation is found the required amount of numbers is retrived, the operation is performed and then the result stored again in the stack. If there are not enough numbers for an operation or there are is more than one number at the end, the input is not valid.

#### How it works
> The reason of this exercice is to get expirience with the c++ stack containers. In order to simplify parsing it only accetps numbers from 0 to 9 and spaces can be ommited. The way to os it is as follows:

``` shell
 make
 ./RPN '<operations>'

 Expamples:
    ./RPN '56+'         #11
    ./RPN '562+*'       #40
    ./RPN '56+2*'       #22
 ```