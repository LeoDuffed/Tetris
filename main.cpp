#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
using namespace std;
using namespace sf;

int main(){
    RenderWindow window(VideoMode({400,400}),"Tetris");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent()){
            cout << "Event: " << event.type << endl;

            }

        }
        window.clear(Color(20,20,20));
        window.display();
    
    
    return 0;

}