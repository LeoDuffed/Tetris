#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <variant>
using namespace std;
using namespace sf;

int main(){
    RenderWindow window(VideoMode({400,400}),"Tetris");
    window.setFramerateLimit(60);
    while(window.isOpen()){
        std::optional<Event> event;
        while((event =window.pollEvent())){
            if(std::holds_alternative<sf::Event::ClosedEvent>(*event)){
            window.close();

            }

        }
        window.clear(Color(20,20,20));
        window.display();
    }
    
    return 0;

}