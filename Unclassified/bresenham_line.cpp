#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Vector2D
{
    float x;
    float y;
};

struct ScreenPoint
{
    int x;
    int y;
};

bool BresenhamLine(std::vector<ScreenPoint>* outPoints, const Vector2D& p1, const Vector2D& p2)
{
    // Not Thread Safe
    if (nullptr == outPoints)
        return false;

    ScreenPoint startPoint{ (int)p1.x, (int)p1.y };
    ScreenPoint endPoint{ (int)p2.x, (int)p2.y };

    int dx = endPoint.x - startPoint.x;
    int dy = endPoint.y - startPoint.y;

    int width  = std::abs(dx);
    int height = std::abs(dy);

    dx = dx > 0 ? 1 : -1;
    dy = dy > 0 ? 1 : -1;

    outPoints->push_back(startPoint);

    int discriminant;
    int testA;
    int testB;

    if (width > height)
    {
        discriminant = 2 * height - width;

        testA = 2 * height;
        testB = 2 * (height - width); // 2 * height - 2 * width

        while (startPoint.x != endPoint.x)
        {
            startPoint.x += dx;

            if (discriminant < 0)
            {
                discriminant += testA;
            }
            else
            {
                discriminant += testB;

                startPoint.y += dy;
            }

            outPoints->push_back(startPoint);
        }
    }
    else
    {
        discriminant = 2 * width - height;
        
        testA = 2 * width;
        testB = 2 * (width - height); // 2 * width - 2 * height

        while (startPoint.y != endPoint.y)
        {
            startPoint.y += dy;

            if (discriminant < 0)
            {
                discriminant += testA;
            }
            else
            {
                discriminant += testB;

                startPoint.x += dx;
            }

            outPoints->push_back(startPoint);
        }
    }

    return true;
}

int main()
{
    char board[10][10];

    int x1;
    int y1;
    
    int x2;
    int y2;

    while (true)
    {
        cout << "input (x1, y1) : ";
        cin >> x1 >> y1;
        
        cout << "input (x2, y2) : ";
        cin >> x2 >> y2;

        if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
            break;

        std::fill(&board[0][0], &board[0][0] + sizeof(board), '.');

        std::vector<ScreenPoint> points;

        BresenhamLine(&points, Vector2D{ (float)x1, (float)y1 }, Vector2D{ (float)x2, (float)y2 });

        for (auto &elem : points)
        {
            board[elem.y][elem.x] = 'o';
        }

        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                cout << board[y][x] << ' ';
            }

            cout << '\n';
        }
    }

    return 0;
}
