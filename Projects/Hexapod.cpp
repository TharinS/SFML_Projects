#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    // Define the size of the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Inverse Kinematics");

    // Define the position and size of the leg segments
    sf::Vector2f hip_position(400, 300);
    float upper_leg_length = 150;
    float lower_leg_length = 150;

    // Define the target position of the foot
    sf::Vector2f target_position(400, 450);

    // Define the angles of the hip, knee, and ankle joints
    float hip_angle = 0;
    float knee_angle = 0;
    float ankle_angle = 0;

    // Define the maximum and minimum angles for the knee and ankle joints
    float max_knee_angle = M_PI / 2;
    float min_knee_angle = -M_PI / 2;
    float max_ankle_angle = M_PI / 2;
    float min_ankle_angle = -M_PI / 2;

    // Define the speed at which the angles change
    float hip_speed = 0.02;
    float knee_speed = 0.02;
    float ankle_speed = 0.02;

    // Define the colors of the leg segments
    sf::Color hip_color(0, 255, 0);
    sf::Color upper_leg_color(0, 0, 255);
    sf::Color lower_leg_color(255, 0, 0);

    // Define the thickness of the leg segments
    float segment_thickness = 10;

    // Create the hip segment
    sf::RectangleShape hip(sf::Vector2f(segment_thickness, segment_thickness));
    hip.setOrigin(segment_thickness / 2, segment_thickness / 2);
    hip.setPosition(hip_position);
    hip.setFillColor(hip_color);

    // Create the upper leg segment
    sf::RectangleShape upper_leg(sf::Vector2f(segment_thickness, upper_leg_length));
    upper_leg.setOrigin(segment_thickness / 2, 0);
    upper_leg.setPosition(hip_position);
    upper_leg.setFillColor(upper_leg_color);

    // Create the lower leg segment
    sf::RectangleShape lower_leg(sf::Vector2f(segment_thickness, lower_leg_length));
    lower_leg.setOrigin(segment_thickness / 2, 0);
    lower_leg.setPosition(hip_position);
    lower_leg.setFillColor(lower_leg_color);

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Calculate the position of the knee joint using inverse kinematics
        sf::Vector2f hip_to_target = target_position - hip_position;
        float distance_to_target = std::sqrt(hip_to_target.x * hip_to_target.x + hip_to_target.y * hip_to_target.y);
        float cos_angle = (upper_leg_length * upper_leg_length + distance_to_target * distance_to_target - lower_leg_length * lower_leg_length) / (2 * upper_leg_length * distance_to_target);
        float knee_angle_cos = std::acos(cos_angle);
        float knee_angle_sin = std::asin(hip_to_target.y / distance_to_target);
        float knee_angle = knee_angle_cos + knee_angle_sin;

        // Limit the knee angle to within the minimum and maximum values
        if (knee_angle > max_knee_angle) {
            knee_angle = max_knee_angle;
        } else if (knee_angle < min_knee_angle) {
            knee_angle = min_knee_angle;
        }
        // Calculate the position of the ankle joint using inverse kinematics
        sf::Vector2f upper_leg_to_target = target_position - upper_leg.getPosition();
        distance_to_target = std::sqrt(upper_leg_to_target.x * upper_leg_to_target.x + upper_leg_to_target.y * upper_leg_to_target.y);
        cos_angle = (upper_leg_length * upper_leg_length + lower_leg_length * lower_leg_length - distance_to_target * distance_to_target) / (2 * upper_leg_length * lower_leg_length);
        float ankle_angle_cos = std::acos(cos_angle);
        float ankle_angle_sin = std::asin(upper_leg_to_target.y / distance_to_target);
        float ankle_angle = ankle_angle_cos + ankle_angle_sin - knee_angle;

        // Limit the ankle angle to within the minimum and maximum values
        if (ankle_angle > max_ankle_angle) {
            ankle_angle = max_ankle_angle;
        } else if (ankle_angle < min_ankle_angle) {
            ankle_angle = min_ankle_angle;
        }

        // Update the angles of the hip, knee, and ankle joints
        hip_angle += hip_speed;
        knee_angle += knee_speed;
        ankle_angle += ankle_speed;

        // Calculate the positions of the hip, knee, and ankle joints
        sf::Vector2f knee_position(hip_position.x + upper_leg_length * std::cos(hip_angle + knee_angle), hip_position.y + upper_leg_length * std::sin(hip_angle + knee_angle));
        sf::Vector2f ankle_position(knee_position.x + lower_leg_length * std::cos(hip_angle + knee_angle + ankle_angle), knee_position.y + lower_leg_length * std::sin(hip_angle + knee_angle + ankle_angle));

        // Update the positions of the leg segments
        hip.setPosition(hip_position);
        upper_leg.setPosition(hip_position);
        upper_leg.setRotation(hip_angle + knee_angle * 180 / M_PI);
        lower_leg.setPosition(knee_position);
        lower_leg.setRotation((hip_angle + knee_angle + ankle_angle) * 180 / M_PI);

        // Clear the window
        window.clear();

        // Draw the leg segments
        window.draw(hip);
        window.draw(upper_leg);
        window.draw(lower_leg);

        // Display the window
        window.display();
    }

    return 0;
}