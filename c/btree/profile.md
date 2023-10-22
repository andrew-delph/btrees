| gcc -pg btree.c && ./a.out && gprof a.out gmon.out > analysis.txt

| gcc -pg btree.c && sudo perf record ./a.out && sudo perf report