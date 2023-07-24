#include <iostream>
#include <vector>
#include <cmath>
#include <random>

struct Node
{
    double x;
    double y;
    Node *parent;

    Node(double x_val, double y_val, Node *parent_node)
    {
        x = x_val;
        y = y_val;
        parent = parent_node;
    }
};

// Euclidean distance
double distance(Node *node1, Node *node2)
{
    double dx = node1->x - node2->x;
    double dy = node1->y - node2->y;
    return std::sqrt(dx * dx + dy * dy);
}

Node *generateRandomNode(double max_x, double max_y)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist_x(0.0, max_x);
    std::uniform_real_distribution<double> dist_y(0.0, max_y);

    double x = dist_x(gen);
    double y = dist_y(gen);

    return new Node(x, y, nullptr);
}

Node *findNearestNode(const std::vector<Node *> &tree, Node *random_node)
{
    Node *nearest_node = nullptr;
    double min_distance = std::numeric_limits<double>::max();

    for (Node *node : tree)
    {
        double dist = distance(node, random_node);
        if (dist < min_distance)
        {
            min_distance = dist;
            nearest_node = node;
        }
    }

    return nearest_node;
}

Node *steer(
    Node *nearest_node,
    Node *random_node, double max_step)
{
    double dist = distance(nearest_node, random_node);
    if (dist <= max_step)
    {
        return random_node;
    }
    else
    {
        double theta = std::atan2(
            random_node->y - nearest_node->y,
            random_node->x - nearest_node->x);
        double new_x = nearest_node->x + max_step * std::cos(theta);
        double new_y = nearest_node->y + max_step * std::sin(theta);
        return new Node(new_x, new_y, nearest_node);
    }
}

bool isCollisionFree(
    Node *node, double obs_x,
    double obs_y,
    double obs_width,
    double obs_height)
{
    // Check collision with obstacles or environment constraints
    // Assuming a rectangular obstacle defined by (obs_x, obs_y) and (obs_x + obs_width, obs_y + obs_height)

    // Check if the node is inside the rectangular obstacle
    if (node->x >= obs_x && node->x <= obs_x + obs_width &&
        node->y >= obs_y && node->y <= obs_y + obs_height)
    {
        return false; // Node is in collision
    }

    return true; // Node is collision-free
}

std::vector<Node *> buildRRT(
    double start_x,
    double start_y,
    double goal_x,
    double goal_y,
    double max_x,
    double max_y,
    int max_iterations,
    double max_step)
{
    std::vector<Node *> tree;
    Node *start_node = new Node(start_x, start_y, nullptr);
    tree.push_back(start_node);

    // Assuming rectangular obstacle defined in the environment
    double obs_x = 2.0;
    double obs_y = 2.0;
    double obs_width = 1.0;
    double obs_height = 1.0;

    for (int i = 0; i < max_iterations; i++)
    {
        Node *random_node = generateRandomNode(max_x, max_y);
        Node *nearest_node = findNearestNode(tree, random_node);
        Node *new_node = steer(nearest_node, random_node, max_step);

        if (isCollisionFree(new_node, obs_x, obs_y, obs_width, obs_height))
        {
            tree.push_back(new_node);

            // Check if the goal is reached
            if (distance(new_node, new Node(goal_x, goal_y, nullptr)) <= max_step)
            {
                Node *goal_node = new Node(goal_x, goal_y, new_node);
                tree.push_back(goal_node);
                return tree; // Path found
            }
        }
    }

    return tree; // Path not found
}

int main()
{
    double start_x = 0.0;
    double start_y = 0.0;
    double goal_x = 5.0;
    double goal_y = 5.0;
    double max_x = 10.0;
    double max_y = 10.0;
    int max_iterations = 1000;
    double max_step = 0.5;

    std::vector<Node *> rrt_tree = buildRRT(
        start_x,
        start_y,
        goal_x,
        goal_y,
        max_x,
        max_y,
        max_iterations,
        max_step);

    // Print the path if it exists
    if (rrt_tree.size() > 0)
    {
        Node *current_node = rrt_tree.back();
        while (current_node != nullptr)
        {
            std::cout << "(" << current_node->x << ", " << current_node->y << ")" << std::endl;
            current_node = current_node->parent;
        }
    }
    else
    {
        std::cout << "Path not found!" << std::endl;
    }

    // Memory Cleanup: Delete allocated nodes
    for (Node *node : rrt_tree)
    {
        delete node;
    }

    return 0;
}
