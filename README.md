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
