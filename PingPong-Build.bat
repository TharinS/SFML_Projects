g++ -I src/include -c Projects/PingPong.cpp -o Main.o
g++ Main.o -o PingPong -L src/lib -lsfml-graphics -lsfml-window -lsfml-system
PingPong.exe