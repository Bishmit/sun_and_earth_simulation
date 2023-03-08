#include<SFML/Graphics.hpp>

class sun {
	sf::Vector2f pos; // this is used to represent the position of both the sun and earth
	float force; 
	sf::CircleShape s; //it gives the visual representation of the sun and earth. it also create white circle on the screen
	// colorfill can also be done by this library, radius can be set by this too

public: 
	sun(float pos_x, float pos_y, float force) {
		pos.x = pos_x; 
		pos.y = pos_y; 
		this->force = force; 

		s.setPosition(pos); // set positon of the sun
		s.setFillColor(sf::Color::Yellow); // gives yellow color to the sun
		s.setRadius(40); // set radius for the sun of 10 pixels

	}

	void render(sf::RenderWindow& bind) {
		bind.draw(s); 
	}

	sf::Vector2f get_pos() {
		return pos; 
	}

	float get_force() {
		return force; 
	}
};

class earth {
	sf::Vector2f pos; 
	sf::Vector2f velocity; 
	sf::CircleShape s;  

public:
	earth(float pos_x, float pos_y, float vel_x, float vel_y) {
		pos.x = pos_x;
		pos.y = pos_y;
		velocity.x = vel_x; 
		velocity.y = vel_y; 

		s.setPosition(pos); // set positon of the sun
		s.setFillColor(sf::Color::White); // gives white color to the sun
		s.setRadius(10); // set radius for the sun of 10 pixels

	}

	void render(sf::RenderWindow& bind) {
		s.setPosition(pos); 
		bind.draw(s); 
	}

	void update_physics(sun &s) {
		// first finding the distance between the sun and the earth with their x and y component
		float distance_x = s.get_pos().x - pos.x; 
		float distance_y = s.get_pos().y - pos.y; 
		//finding the hypotenuse distance 
		float distance = sqrt(distance_x * distance_x + distance_y * distance_y); 
		float inverse_distance = 1.f / distance; 

		float normalized_x = inverse_distance * distance_x; 
		float normalized_y = inverse_distance * distance_y; 

		float distance_square = inverse_distance * inverse_distance;

		float accleratiion_x = normalized_x * s.get_force() * distance_square; 
		float accleratiion_y = normalized_y * s.get_force() * distance_square; 

		velocity.x += accleratiion_x; 
		velocity.y += accleratiion_y;

		pos.x += velocity.x; 
		pos.y += velocity.y; 
	}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(1600, 1000), "Sun and Earth"); 
	window.setFramerateLimit(60); 

	sf::Texture backgroundTexture; 
	if (!backgroundTexture.loadFromFile("C:/Users/acer/Downloads/space.jpg")) {
		return 1; // exit the program
	}

	sf::Sprite backgroundImage; 
	backgroundImage.setTexture(backgroundTexture); 

	sun source(800, 400, 8000);
	earth particle(600, 700, 4, 1); 

	while (window.isOpen()) {
		sf::Event event; 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close(); 

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close(); 
		}

		window.clear(); 
		window.draw(backgroundImage);
		particle.update_physics(source); 
		source.render(window); 
		particle.render(window); 
		//draw calls
		window.display(); 
	}
}
