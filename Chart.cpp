
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using sf::Color;
using sf::RenderWindow;
using sf::CircleShape;
using sf::Vector2f;
using sf::Event;
using sf::RectangleShape;
using sf::VideoMode;

class Chart
{
public:
	float width;
	float height;
	int numberBars;
	Color axisColor;
	RectangleShape xAxis;
	RectangleShape yAxis;
	vector<RectangleShape> bars;
	string title;
	float barWidth;
	float barSpacing;
	Chart()
	{
		width = 900;
		height = 900;
		numberBars = 5;
		axisColor = Color::White;
		bars = vector<RectangleShape>();
	}
	Chart(float w, float h, int n)
	{
		width = w;
		height = h;
		numberBars = n;
	}
	void setBarHeight(int barIndex, float barHeight)
	{
		RectangleShape bar = bars[barIndex];
		float iH = bar.getSize().y;
		bar.setSize(Vector2f(bar.getSize().x, barHeight));
		float newY;
		if (iH > barHeight)
		{
			newY = xAxis.getPosition().y + barHeight;
		}
		else
		{
			newY = xAxis.getPosition().y - barHeight;
		}

		bar.setPosition(bar.getPosition().x, newY);
		bars[barIndex] = bar;
	}
	void setBarColor(int barIndex, Color barColor)
	{
		bars[barIndex].setFillColor(barColor);
	}
	void setAxisColor(Color axisColor)
	{
		xAxis.setFillColor(axisColor);
		yAxis.setFillColor(axisColor);
	}
	void configAxis()
	{
		RectangleShape xAxis(Vector2f(900, 5));
		RectangleShape yAxis(Vector2f(900, 5));
		xAxis.move(900, 800);
		yAxis.move(40, 5);
		xAxis.rotate(180);
		yAxis.rotate(90);
		this->xAxis = xAxis;
		this->yAxis = yAxis;
	}
	void setTitle(string title)
	{
		this->title = title;
	}
	void configBars()
	{
		this->barWidth=100;
		this->barSpacing=10;
		for (int i = 0; i < this->numberBars; i++)
		{
			RectangleShape bar(Vector2f(100, 100));
			if (i == 0)
			{
				bar.move(50, 700);
			}
			else
			{
				float lP = bars[i - 1].getPosition().x;
				bar.move(lP + 110, xAxis.getPosition().y - 100);
			}
			this->bars.push_back(bar);
		}
	}
	void draw(RenderWindow &window)
	{
		window.draw(xAxis);
		window.draw(yAxis);
		window.setTitle(title);
		for (int i = 0; i < bars.size(); i++)
		{
			window.draw(bars[i]);
		}
	}
	bool validIndex(int index){
		if(index>=0 && index<numberBars){
			return true;
		}
		return false;
	}
	vector<vector<float>> computeBarWithSpacing(){
		vector<vector<float>> barsWithSpacing;
		for(RectangleShape bar:this->bars){
			vector<float> barInfo;
			barInfo.push_back(bar.getSize().x);
			barInfo.push_back(bar.getPosition().x);
			barsWithSpacing.push_back(barInfo);
		}
		return barsWithSpacing;
	}
};
int main()
{
	RenderWindow window(VideoMode(900, 900), "SFML works!");
	Chart graph(900, 900, 5);
	graph.configAxis();
	graph.configBars();
	graph.setBarHeight(0, 200);
	graph.setBarColor(0, Color::Red);
	graph.setBarHeight(1,400);
	graph.setBarColor(1,Color::Blue);
	graph.setAxisColor(Color::Yellow);
	graph.setTitle("It works!");
	bool isValid = graph.validIndex(8);
	std::cout<<"Is valid index = "<<isValid<<std::endl;
	vector<vector<float>> barsWithSpacing = graph.computeBarWithSpacing();
	int count=1;
	for(vector<float> v:barsWithSpacing){
		int internalCount=0;
		float lastWidth,lastSpace;
		std::cout <<"Bar number "<<count;
		for(float f:v){
			if(internalCount==0){
				std::cout<<" Width= "<<f<<" ";
				lastWidth=f;
			}else{
				float space = f-lastWidth-lastSpace;
				if(space<0){
					std::cout<<"Spacing= "<<f<<" ";
				}else{
					std::cout<<"Spacing= "<<space<<" ";
				}
				lastSpace=f;
			}
			internalCount++;
		}
		std::cout<<std::endl;
		count++;
	}
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);
		graph.draw(window);
		window.display();
	}

	return 0;
}
