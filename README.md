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

- 1) expansion of variable et tokenization dans arbre! // bien avancé !
- 2) erreur syntax // normalement on a un truc, a check
- 3) code erreur dernière fonction
- 4) pouvoir executer des redirections uniques : $ > file2 ; << eof ; < file1 ; >> file2
- 5) builtin exit
- 6) correct initialisation of p_mini->cwd (for PWD)
- builtins in pipe function ! // should be working now !
- cd which reset PWD environment variable only in case of PWD existing !
- 
- option "-n" of echo builtin !
- implementation of '&' and ';'
- implementation of subshell
- make cwd_name a variable at start of shell, if $PWD is set, take its value, else call getcwd; // working but should be upgraded 
- secure pathname length (if you call cd on a path that would be greater than PATH_NAME_MAX_LENGTH, then print error message) // should be ok
- Here-documents -> MAX here doc count = 16 if more -> next command ! exit !
    - base marche
    - manque de generer un nom de fichier assez random dans /tmp/minishel.<5-7 lettres randoms>
    - check que le nom de fichier générés n'existe pas déjà sinon en générer un nouveau !
    - mieux gérer quand expand et quand ne pas expand !
- handle signal :
    - Ctrl C
    - Ctrl \
- modify PATH when it is modified by unset ! // should be OK !
- in env builtin, make "_" environment variable to be the last command executed !
- a function to transform env chained list to a (char **) that can be passed to execve !
- readline history // done 
- readline error while <C-C> when its looking for autocomplete
- leaks
