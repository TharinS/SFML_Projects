g++ -I src/include -c Projects/Gradient.cpp -o Main.o -fpermissive
g++ Main.o -o Gradient -L src/lib -lsfml-graphics -lsfml-window -lsfml-system
Gradient.exe