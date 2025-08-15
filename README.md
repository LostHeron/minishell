TESTS ETRANGES :

(cat) | (cat) | ((cat)) -> is it a bug, -> bug report it ?

chose a tester : 

> file1 echo "coucou"
echo "lala" && > file1 echo "coucou"
> log valgrind echo "yo" 2>&3 > log2
echo $'cou\tcou\n'

exemple de commande à prendre en compte pour l'algorithme de parsing
quelques exemples : 

(> log echo "coucou \n" le plus beau | > file1 cat > file3 && echo $?) && (cat file1 | cat | cat && ls -l ~ && sleep 3 ; echo fini & echo yo la team) && toi la && "" && ici

cat << yoyo > log1 & sleep 2 && echo youhou

(((sleep 3 && ls -l ~ | grep l ; pppd) ; echo "retour de retour = $?" && sleep 3 && ls -l ~ | grep l ; pppd) ; echo "retour = $?" && sleep 3 && ls -l ~ | grep azlejzmaelkj) & echo puis

{ (sleep 2 && exit 3); eheh=$?; } ; echo "ehehe = $eheh"

{ sleep 4 && echo "eheh = $eheh" ; } & { (sleep 2 && exit 3); eheh=$?; }

cat << eof > file1 | cat << eoff > file2

the following command with dup2 failure 
ls > log1 << eof1 | ls > log2 << eof2 | ls > log3 << eof3 


TODO:

- 6) change get_line funciton to allow to call it to free it !
- 5) rename start_minishell and run_minishell to some more specific names
- 4) SEGFAULT IF : unset PATH; export PATH; echo $PATH 
(must be because trying to dereference ((t_env*)tmp->content)->value which is NULL, just a verification to add i guess)
- 4 ) SEGFAULT IF : ( (echo coucou < not_exitst ; ) )  et just  echo coucou < not_exitst ; enfaite -> Probleme au niveau du free_tree aussi i guess
- 3) Normage dans Execution
- 4) Leak et sortie en cas d'erreurs de partout ! 
        -> dans init
        -> dans parsing
        -> dans ast
        -> dans execution

OPTIONAL BUT COOL:
- 3) ls si dans deux PATH differents mais premier pas acces, va essayer d'executer le deuxième -> a voir si on fait
- 5) change all bandage on the stuff in case_no_forking and return value with specific case if builtin is exit
maybe solution is to change p_mini->err_code directly inside the builtins, so we can always return 0 if function performed well ! -> let's see later

 |
 |
 |
 |
 |
\ /
OLD stuff just in case for check : 

- 4) regarder pourquoi ./minishell | ./minishell ne fonctionne pas // and look how to make it work
- implementation of '&' // -> gave up
- implementation of subshell // quite good advanced ! even done ?? -> should be working well !
- implementation of ';' // DONE
- 5) faire en sorte que lorsque l'on quitte minishell on close tous les fds restant des HERE-DOCS (ceux ouvert dans les subshells que je ne close pas de suite ! // logiquement c'est fait mais peut être quelque cas ou ça ne marche pas 
- 13) in rl_gnl remove last "\n"
- 1) gerer les here doc pour eviter que le prompt aille dans le fichier log si on lance $ ./minishell > log
- 2) CTRL-C dans here doc
- 4) create error ERROR_MAX_HERE_DOC_COUNT_EXCEEDED et afficher dans print error 
- handle signal :
    - Ctrl C
    - Ctrl \
- readline signal SIGINT interrupt (with something like readline hook smth)
- 3) Refaire error synthax au niveau des parenthese, apres des parenthese ou avant, il peu y avoir 
que des redirections s'il y a autre chose ou des operateurs de commande 
- 2) pouvoir executer des redirections uniques : $ > file2 ; << eof ; < file1 ; >> file2 // OU PAS ?
- 2) faire quand > vers un nom de fichier sans permission que ça arrete la commande 
- 5) utiliser readline au lieu de get next line dans les here documents ?
- 5) gerer le shell qui se lance dans /home/jweber/goinfre/a/b/c après avoir supprimer a/b/c ? // work ok execpt for printing pwd just does not behave like bash but nvm;
- 6) wrong error message in case of SIGINT in heredocuments (and maybe cat)
- 13) cat < coucou avec coucou qui est inexistant code erreur = 7 au lieu de 1, de même avec cat > coco sans permission sur coco // DONE 
- 11) export code d'erreur pas bon quand fail  // DONE 
- 9) segfault when entering empty line // DONE 
- 8) generate error message for ERROR_WRITE // DONE 
- 7) generate error message for ERROR_READ // DONE 
- 7) regler le probleme ou une commande se finit par ';' // DONE (execpt for print tree);
- 8) MODIFIER wait_children en fonction d'un nombre d'enfant a wait
pour pouvoir exec_background un nombre infini de command // DONE even if exec_background is suppressed
- 9) et voir pour que les signaux ne soient pas envoyé du parents aux enfants 'zombie' // so we forget this one
- 9) tester programme qui handle sigint et qui boucle a l'infinie et dans le process parent voir ce que ça donne sur wait
- 1) expand des '*' // done logiquement !
- cd which reset PWD environment variable only in case of PWD existing ! // should be done !
- 1) do not display prompt of readline if not in tty mode // DONE
- 3) initialiaze an environment even is 'char **env' passed to minishell is NULL // done for PWD
- a function to transform env chained list to a (char **) that can be passed to execve ! // done !
- modify PATH when it is modified by unset ! // should be OK !
- option "-n" of echo builtin ! // DONE mais à check
- 1) expansion of variable et tokenization dans arbre! // bien avancé !
- 2) erreur syntax // normalement on a un truc, a check
- 3) code erreur dernière fonction // logiquement c'est pas trop mal , mais a vérifier
- 3) expand dans les Here-doc mieux gérer quand oui et non // DONE
- 5) Change parenthesis synthax check (do it on tokens instead, cuz this line echo ")(" would be treated as 'unmatching parenthesis'// Done
- 4) pouvoir executer des redirections uniques : $ > file2 ; << eof ; < file1 ; >> file2
- 5) builtin exit // FAIT !
- 6) correct initialisation of p_mini->cwd (for PWD) // FAIT !
- make cwd_name a variable at start of shell, if $PWD is set, take its value, else call getcwd; // working but should be upgraded 
- builtins in pipe function ! // should be working now !
- secure pathname length (if you call cd on a path that would be greater than PATH_NAME_MAX_LENGTH, then print error message) // should be ok
- readline history // done 
- Here-documents -> MAX here doc count = 16 if more -> next command ! exit ! // Normalement c'est bon !
    - base marche
    - manque de generer un nom de fichier assez random dans /tmp/minishel.<5-7 lettres randoms>
    - check que le nom de fichier générés n'existe pas déjà sinon en générer un nouveau !
    - mieux gérer quand expand et quand ne pas expand !

flemme :

- expand of cd '-' as '-' corresponding to OLDPWD
- initialize environment varaible SHLVL ?
- 7) modifier args for token which shoudl not be init each time (optionel mais cool si fait)
