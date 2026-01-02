#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>
#include <cctype>

double calculate(double a, double b, char op)
{
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return b != 0 ? a / b : 0;
    }
    return 0;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(420, 600), "Scientific Calculator");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return -1;

    std::string display = "";
    std::string expression = "";
    double num1 = 0;
    char op = 0;
    bool newInput = false;
    bool showCursor = true;

    sf::Clock cursorClock;

    // Dark theme screen
    sf::RectangleShape screen(sf::Vector2f(380, 90));
    screen.setPosition(20, 20);
    screen.setFillColor(sf::Color(30, 30, 30));

    sf::Text screenText("", font, 28);
    screenText.setPosition(30, 45);
    screenText.setFillColor(sf::Color::White);

    sf::Text expText("", font, 18);
    expText.setPosition(30, 25);
    expText.setFillColor(sf::Color(180, 180, 180));

    struct Button
    {
        sf::RectangleShape box;
        sf::Text label;
        std::string value;
    };

    std::vector<Button> buttons;

    auto addButton = [&](float x, float y, std::string text)
        {
            Button b;
            b.box.setSize({ 80, 50 });
            b.box.setPosition(x, y);
            b.box.setFillColor(sf::Color(50, 50, 50));
            b.box.setOutlineThickness(1);
            b.box.setOutlineColor(sf::Color(90, 90, 90));

            b.label.setFont(font);
            b.label.setString(text);
            b.label.setCharacterSize(18);
            b.label.setFillColor(sf::Color::White);
            b.label.setPosition(x + 22, y + 12);

            b.value = text;
            buttons.push_back(b);
        };

    std::string labels[] =
    {
        "7","8","9","/",
        "4","5","6","*",
        "1","2","3","-",
        "0",".","=","+",
        "sin","cos","tan","sqrt",
        "log","C"
    };

    int i = 0;
    for (int row = 0; row < 6; row++)
        for (int col = 0; col < 4 && i < 22; col++)
            addButton(20 + col * 95, 130 + row * 60, labels[i++]);

    auto processInput = [&](std::string v)
        {
            if (isdigit(v[0]) || v == ".")
            {
                if (newInput) { display = ""; newInput = false; }
                display += v;
            }
            else if (v == "C")
            {
                display = "";
                expression = "";
                num1 = 0;
                op = 0;
            }
            else if (v == "=" && op)
            {
                double num2 = std::stod(display);
                display = std::to_string(calculate(num1, num2, op));
                expression = "";
                newInput = true;
            }
            else if (v == "sin" || v == "cos" || v == "tan" || v == "sqrt" || v == "log")
            {
                double n = std::stod(display);
                if (v == "sin") n = sin(n);
                if (v == "cos") n = cos(n);
                if (v == "tan") n = tan(n);
                if (v == "sqrt") n = sqrt(n);
                if (v == "log") n = log10(n);
                display = std::to_string(n);
                newInput = true;
            }
            else
            {
                num1 = std::stod(display);
                op = v[0];
                expression = display + " " + v;
                newInput = true;
            }
        };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Mouse input
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mouse(sf::Mouse::getPosition(window));
                for (auto& b : buttons)
                    if (b.box.getGlobalBounds().contains(mouse))
                        processInput(b.value);
            }

            // Keyboard input
            if (event.type == sf::Event::TextEntered)
            {
                char c = static_cast<char>(event.text.unicode);
                if (isdigit(c) || c == '.')
                    processInput(std::string(1, c));
                else if (c == '+' || c == '-' || c == '*' || c == '/')
                    processInput(std::string(1, c));
                else if (c == '\b' && !display.empty())
                    display.pop_back();
                else if (c == '\r')
                    processInput("=");
                else if (c == 'c' || c == 'C')
                    processInput("C");
            }
        }

        // Cursor blink
        if (cursorClock.getElapsedTime().asSeconds() > 0.5f)
        {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        expText.setString(expression);
        screenText.setString(display + (showCursor ? "|" : ""));

        window.clear(sf::Color(20, 20, 20));
        window.draw(screen);
        window.draw(expText);
        window.draw(screenText);

        for (auto& b : buttons)
        {
            window.draw(b.box);
            window.draw(b.label);
        }

        window.display();
    }

    return 0;
}