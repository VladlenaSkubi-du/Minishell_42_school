# Minishell_42_school
Minishell project is a mini UNIX command interpreter. It displays a prompt after that a user types his/her commands.

This minishell works with simple command lines, does limited work with environment, executes programms defined in PATH, manages expansions $ and ~.

# Usage
You need to compile the program and then use it according to the usage an average shell has (mostly, bash).

So, your steps -

Clone the repository:

    git clone https://github.com/VladlenaSkubi-du/Minishell_42school.git [folder's name you want]
  
Get into it and compile the ft_ls-program:

    cd [folder's name you want]
    make
  
After you make:

    ./minishell

And input your commands. For example:

    $minishell> ls
    Makefile        author          libft           objs
    README.md       includes        minishell       srcs
    $minishell> /bin/ls ../
    10_Docker               7_Ft_printf_with_Petr   
    11_Push_swap_mygit      8_Ft_ls_mygit           
    1_Piscine               9_Minishell_mygit       
    2_Preparation           DevOps                  
    3_LIBFT                 
    $minishell> echo -e "\033[35mHello\x1b[0m"
    Hello (in pink)
    $minishell> env
  
And so on. To leave minishell you should input "exit" or ^D (ctrl + D on Mac OS).
Paralelly you can check the output using the same command lines. I hope it will show the same results (but not always, in some cases output should differ).

Go and try. Good luck!

# Limits
Though it is minishell, mini-interpreteur, do not try to do the following, it will not work:
    
- push "↑", there will be no commands history;
- push "tab" many times: auto-completion was done for bonuses only, in last hours and it works only with 1 or 2 letters until it finds the first coincidence in the directories found in PATH variable;
- send combinations you got used to - there are only ctrl + C (ctrl + J, ctrl + M, all the same) and ctrl + D working.
    
But something still works:
    
- "→" and "←" - if you push "Enter" after, each "→" or "←" will become a space;
- you can delete and add printable symbols from each part of the line BUT it does not work if the line is too big and is carried over to the next line;
- ~ and $ and also ; and "" '' () {} - if you do not close anything, minishell will be angry;
- builtins env, setenv, unsetenv, echo, exit, cd that we had to reproduce:
    - cd with not arguments and '-' flag;
    - setenv only with '=';
    - echo with '-n' and '-e' or '-E' flag
Remember that "mini" means "small in relation to others of the same kind".

# Grade
125/100 (the maximum bonus is 25 points)
