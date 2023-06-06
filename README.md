### To forward X11 from inside a docker container to a host running macOS

valgrind --tool=memcheck --leak-check=yes|no|full|summary --leak-resolution=low|med|high --show-reachable=yes ./test


1. no : ne fait rien.
2. full / yes : donne des détails sur chaque fuite mémoire.
3. summary : indique le nombre de fuites mémoires.
4. où le paramètre show-reachable étend la recherche aux zones encore pointées mais non désallouées.
5. où le paramètre leak-resolution indique le niveau de recherche des fuites mémoires.

```
https://doc.ubuntu-fr.org/valgrind
 ```

valgrind --tool=memcheck --leak-check=yes --leak-resolution=med --show-reachable=yes --track-origins=yes ./bin/main
valgrind --tool=memcheck --leak-check=summary --leak-resolution=med --show-reachable=yes ./bin/main