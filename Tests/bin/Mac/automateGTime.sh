for i in {1.1}; do gtime -ao Time_Performance_Password_With_Counter_3.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_With_Counter_3'; done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Fibonacci_With_Counter_2.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Fibonacci_With_Counter_2' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Fibonacci_Without_Counter.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Fibonacci_Without_Counter' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_ForLoops_With_Counter.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_ForLoops_With_Counter' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_ForLoops_Without_Counter.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_ForLoops_Without_Counter' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Password_With_Counter_1.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_With_Counter_1' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Password_With_Counter_2.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_With_Counter_2' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Password_With_Counter_3.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_With_Counter_3' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Password_With_Counter_4.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_With_Counter_4' && sleep .0001
done
sleep 5
for i in {1..1000};
do gtime -ao Time_Performance_Password_Without_Counter.txt -f "%e" /bin/sh -c 'LD_BIND_NOW=1 ./Performance_Password_Without_Counter' && sleep .0001
done
