
#include <iostream> 
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main(){
    RenderWindow window(VideoMode(400,400),"Tetris");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type==Event::Closed) window.close();

        }
        window.clear(Color(20,20,20));
        window.display();
    }
    
    return 0;

}