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



TODO:

- 1) expand des '*'
- 2) pouvoir executer des redirections uniques : $ > file2 ; << eof ; < file1 ; >> file2 // OU PAS ?
- 3) Normage dans Execution
- 4) Leak et sortie en cas d'erreurs de partout ! 
        -> dans init
        -> dans parsing
        -> dans ast
        -> dans execution
- cd which reset PWD environment variable only in case of PWD existing !
- option "-n" of echo builtin !
- implementation of '&' and ';'
- implementation of subshell
- handle signal :
    - Ctrl C
    - Ctrl \
- modify PATH when it is modified by unset ! // should be OK !
- in env builtin, make "_" environment variable to be the last command executed ! // or just remove this environment variable
- a function to transform env chained list to a (char **) that can be passed to execve !
- readline signal SIGINT interrupt (with something like readline hook smth)
- leaks

OLD stuff just in case for check : 

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


- 7) modifier args for token which shoudl not be init each time (optionel mais cool si fait)
