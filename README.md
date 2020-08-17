Mark Sigilai
SEEsh.c


SEEsh is a UNIX shell implementation that makes facilities of the operating system available to the users. It reads lines from the user and then performs lexical analysis on the line to form tokens. Once the tokens are created, they are fed to the command interpreter which executes the command. 
It executes the following commands: cd, pwd, help, exit, set var [value], unset var.


LEAK SUMMARY: from Valgrind
==29563==    definitely lost: 850 bytes in 10 blocks
==29563==    indirectly lost: 0 bytes in 0 blocks
==29563==      possibly lost: 0 bytes in 0 blocks
==29563==    still reachable: 0 bytes in 0 blocks
==29563==         suppressed: 0 bytes in 0 blocks
==29563== Rerun with --leak-check=full to see details of leaked memory

Help for the fork and structure of the shell : https://brennan.io/2015/01/16/write-a-shell-in-c/
