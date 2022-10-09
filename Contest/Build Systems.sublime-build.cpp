{
 // fast
 "cmd":["ulimit -s unlimited && g++ -std=c++17 -D UBC=1 -D LOCAL=1 -Wshadow -Wall $file_name -o $file_base_name -O2 -Wno-unused-result && timeout 5s ./$file_base_name"],
 // safe
 "cmd":["ulimit -s unlimited && g++ -std=c++17 -D UBC=1 -D LOCAL=1 -Wshadow -Wall $file_name -o $file_base_name -g -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG && timeout 5s ./$file_base_name"],
 // no limit
  "cmd":["ulimit -s unlimited && g++ -std=c++17 -D UBC=1 -D LOCAL=1 -Wshadow -Wall $file_name -o $file_base_name -O2 -Wno-unused-result && ./$file_base_name"],
 "quiet": false ,
 "shell": true ,
 "working_dir": "${file_path}",
 "selector": "source.c++"
}