# /bin/sh
set -xe

gcc -Wall -Wextra -pedantic -g  main.c -lreadline -o main
./main
