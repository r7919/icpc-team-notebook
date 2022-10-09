g++ temp.cpp -static -DONLINE_JUDGE -lm -s -x -fno-stack-protector -O2 -std=c++17 -D__USE_MINGW_ANSI_STDIO=0 -o temp
g++ brute_force.cpp -static -DONLINE_JUDGE -lm -s -x -fno-stack-protector -O2 -std=c++17 -D__USE_MINGW_ANSI_STDIO=0 -o brute_force
g++ generator.cpp -static -DONLINE_JUDGE -lm -s -x -fno-stack-protector -O2 -std=c++17 -D__USE_MINGW_ANSI_STDIO=0 -o generator

> input.txt  
> output.txt
> failed_cases.txt
> output_brute.txt

for ((i = 1; ;i++)) do
  printf "[TEST #$i]"
  ./generator > input.txt 
  ./brute_force < input.txt > output_brute.txt
  ./temp < input.txt > output.txt

  if diff -w output_brute.txt output.txt
  then
     printf "[-OK-]\n"
  else
     printf "\n"
     echo "[-*-WA-*-]"
     cat input.txt >> failed_cases.txt
     printf "\n"
     echo "[-FOUND FAILING TEST!-]"
     printf "\n"
     echo "[INPUT]"
     printf "\n"
     cat failed_cases.txt
     printf "\n"
     echo "[BRUTE FORCE OUTPUT]"
     printf "\n"
     cat output_brute.txt
     printf "\n"
     echo "[TEMP OUTPUT]"
     printf "\n"
     cat output.txt
     printf "\n"
     break
  fi
done