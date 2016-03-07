#!/bin/bash

./"a.out"

echo a || exit

echo a && exit

echo a ; exit

#exit

(echo A && echo B) && exit

exit


