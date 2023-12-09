main.c:56:32: warning: length modifier 'll' results in undefined behavior or no effect with 'f' conversion specifier [-Wformat]
        fprintf(log_file, "%d %llf", len, elapsed_time);
                              ~^~~
main.c:64:30: warning: length modifier 'll' results in undefined behavior or no effect with 'f' conversion specifier [-Wformat]
        fprintf(log_file, " %llf\n", elapsed_time);
                            ~^~~
2 warnings generated.
