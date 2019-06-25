/*

Author: Andy Perrett June 2019
Course: BSc Computer Science Level 1

*/

#include "RecursiveBackTracker.h"

// Standard libraries
#include <ctime> // for random number seed
#include <stdio.h> // printf etc for error reporting

// My classes
#include "Place.h"

using namespace std;

// Instantiate with size of World
RecursiveBackTracker::RecursiveBackTracker(int y, int x)
{
    // Set the size of this world
    this->_MaxY = y;
    this->_MaxX = x;

    // Shouldn't be necessary but included for completeness
    // in case I want to import a world
    _CreateBlankWorld(this->_MaxY, this->_MaxX);

    // Seed the backtracker
    Stack stack;
    stack.Push(Place(0, 0));
    _World[0][0].Visited = true;
    int visited = 0;

    // Seed the random number generator
    srand((unsigned)time(0));

    // Off we go...
    _CreateMaze(stack, visited);
}

// Creating a maze using the recursive backtracker algorithm
void RecursiveBackTracker::_CreateMaze(Stack stack, int visited)
{
    // Exit when all cells visited
    if (visited == (_MaxY * _MaxX)) return;

    // Set the place
    Place current = stack.Top();

    // Find all neighbours that haven't been visited before
    int neighbours = GetUnvisitedNeighbours(current);

    // We might need to "Backtrack"
    while (neighbours == 0)
    {
        if (stack.IsEmpty()) return;
        current = stack.Pop();
        neighbours = GetUnvisitedNeighbours(current);
    }

    // Pick one of the neighbours to goto next
    string dir = GetRandomNeighbour(neighbours);

    // Set the door, save which direction we went in
    SetDoor(current, dir);

    // Take the door in this direction
    current = _GetNewPlace(current, dir);

    // Mark the cell as visited
    _World[current.y][current.x].Visited = true;

    // Place new cell onto the stack ready for next recursion
    stack.Push(current);

    // Keep track because this will determine when to exit
    visited++;

    // Recurse
    _CreateMaze(stack, visited);
}

// If this direction is taken return the cell address it points to
Place RecursiveBackTracker::_GetNewPlace(Place current, string dir)
{
    Place newCell;
    if (dir == "n")  newCell =  Place(current.y - 1, current.x);
    if (dir == "ne") newCell =  Place(current.y - 1, current.x + 1);
    if (dir == "e")  newCell =  Place(current.y,     current.x + 1);
    if (dir == "se") newCell =  Place(current.y + 1, current.x + 1);
    if (dir == "s")  newCell =  Place(current.y + 1, current.x);
    if (dir == "sw") newCell =  Place(current.y + 1, current.x - 1);
    if (dir == "w")  newCell =  Place(current.y,     current.x - 1);
    if (dir == "nw") newCell =  Place(current.y - 1, current.x - 1);
    return newCell;
}

// Create blank world with no doors
void RecursiveBackTracker::_CreateBlankWorld(int y, int x)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            _World[i][j].Visited = false;
            _World[i][j].Doors = (uint8_t)0b00000000;
        }
    }
}

// Return a bitmap of the doors
uint8_t RecursiveBackTracker::GetDoors(Place place)
{
    return _World[place.y][place.x].Doors;
}

// Set all doors
void RecursiveBackTracker::SetDoors(Place place, uint8_t doors)
{
    _World[place.y][place.x].Doors = doors;
}

// Set individual door
void RecursiveBackTracker::SetDoor(Place place, string dir)
{
    _World[place.y][place.x].Doors |= _Dir[dir];
    if (dir == "n")  _World[place.y - 1][place.x].Doors     |= _OpDir["n"];
    if (dir == "ne") _World[place.y - 1][place.x + 1].Doors |= _OpDir["ne"];
    if (dir == "e")  _World[place.y][place.x + 1].Doors     |= _OpDir["e"];
    if (dir == "se") _World[place.y + 1][place.x + 1].Doors |= _OpDir["se"];
    if (dir == "s")  _World[place.y + 1][place.x].Doors     |= _OpDir["s"];
    if (dir == "sw") _World[place.y + 1][place.x - 1].Doors |= _OpDir["sw"];
    if (dir == "w")  _World[place.y][place.x - 1].Doors     |= _OpDir["w"];
    if (dir == "nw") _World[place.y - 1][place.x - 1].Doors |= _OpDir["nw"];
}

// Get individual door
bool RecursiveBackTracker::IsDoor(Place place, string door)
{
    if ((_World[place.y][place.x].Doors & _Dir[door]) > 0)
    {
        return true;
    }
    return false;
}

// Get Unvisited Neighbours
uint8_t RecursiveBackTracker::GetUnvisitedNeighbours(Place place)
{
    uint8_t neighbours = 0;

    if (place.y > 0)
    {
        if (_World[place.y - 1][place.x].Visited == false)     neighbours |= _Dir["n"];
    }
    if ((place.y > 0) && (place.x < (_MaxX - 1)))
    {
        if (_World[place.y - 1][place.x + 1].Visited == false) neighbours |= _Dir["ne"];
    }
    if ((place.y > 0) && (place.x > 0))
    {
        if (_World[place.y - 1][place.x - 1].Visited == false) neighbours |= _Dir["nw"];
    }
    if (place.x > 0)
    {
        if (_World[place.y][place.x - 1].Visited == false)     neighbours |= _Dir["w"];
    }
    if (place.x < (_MaxX - 1))
    {
        if (_World[place.y][place.x + 1].Visited == false)     neighbours |= _Dir["e"];
    }
    if (place.y < (_MaxY - 1))
    {
        if (_World[place.y + 1][place.x].Visited == false)     neighbours |= _Dir["s"];
    }
    if ((place.y < (_MaxY - 1)) && (place.x > 0))
    {
        if (_World[place.y + 1][place.x - 1].Visited == false) neighbours |= _Dir["sw"];
    }
    if ((place.y < (_MaxY - 1)) && (place.x < (_MaxX - 1)))
    {
        if (_World[place.y + 1][place.x + 1].Visited == false) neighbours |= _Dir["se"];
    }

    return neighbours;
}

// Pick a neighbour / direction
string RecursiveBackTracker::GetRandomNeighbour(uint8_t neighbours)
{
    // Get out quick if no neighbours
    if (neighbours == 0) return "none";

    // Used to store neighbours
    string n[8];

    // The number of neighbours
    int num = 0;

    // Add the neighbours to array
    // by iterating and testing each bit
    for (int i = 0; i < 8; i ++)
    {
        // Shift 1 'i' times and test
        if (neighbours & (1 << i))
        {
            n[num++] = _Compass[i];
        }
    }

    // If we only have one, return it;
    if (num == 1) return n[0];

    // Return a random direction
    return n[rand() % num];
}

// Display the world
void RecursiveBackTracker::DisplayMaze()
{
    //The window we'll be rendering to
    SDL_Window* window = NULL;

    SDL_Renderer *renderer = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "Maze by Andy Perrett 2019", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            SDL_bool done = SDL_FALSE;

            int markerX = 0;
            int markerY = 0;

            while (!done)
            {
                SDL_Event event;

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);

                int y = 0, x = 0;
                int offsetY = 10;
                int offsetX = 10;

                for(int i = 0; i < _MaxY; i ++)
                {
                    y = i * 35 + offsetY;
                    for(int j = 0; j < _MaxX; j++)
                    {
                        x = j * 35 + offsetX;
                        DrawOctagon(renderer, y, x, i ,j);
                    }
                }


                DrawMarker(renderer, markerY, markerX);
                DrawArrows(renderer, markerY, markerX);

                SDL_RenderPresent(renderer);

                // Wait for close window event
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                        case SDL_QUIT:
                            done = SDL_TRUE;
                            break;
                            case SDL_KEYDOWN:
                                switch (event.key.keysym.sym)
                                {
                                    case SDLK_KP_4:
                                    {
                                        if (markerX > 0 && IsDoor(Place(markerY, markerX), "w"))
                                        {
                                            markerX--;
                                        }
                                        break;
                                    }
                                    case SDLK_KP_6:
                                    {
                                        if (markerX < _MaxX - 1 && IsDoor(Place(markerY, markerX), "e"))
                                        {
                                            markerX++;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_8:
                                    {
                                        if (markerY > 0 && IsDoor(Place(markerY, markerX), "n"))
                                        {
                                            markerY--;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_2:
                                    {
                                        if (markerY < _MaxY - 1 && IsDoor(Place(markerY, markerX), "s"))
                                        {
                                            markerY++;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_3:
                                    {
                                        if ( markerY < _MaxY - 1 && markerX < _MaxX - 1 && IsDoor(Place(markerY, markerX), "se"))
                                        {
                                            markerY++;
                                            markerX++;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_7:
                                    {
                                        if (markerY > 0 && markerX > 0 && IsDoor(Place(markerY, markerX), "nw"))
                                        {
                                            markerY--;
                                            markerX--;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_1:
                                    {
                                        if (markerY < _MaxY - 1 && markerX > 0 && IsDoor(Place(markerY, markerX), "sw"))
                                        {
                                            markerY++;
                                            markerX--;
                                        }
                                    }
                                    break;
                                    case SDLK_KP_9:
                                    {
                                        if (markerY > 0 && markerX < _MaxX - 1 && IsDoor(Place(markerY, markerX), "ne"))
                                        {
                                            markerY--;
                                            markerX++;
                                        }
                                    }
                                    break;
                                }
                                break;
                     }
                }

            // reduce cpu usage, set frame rate
            // Without delaying a cpu core will work at 100%
            SDL_Delay( 66 );
            }
        }
    }

    // Destroy renderer
    if (renderer) SDL_DestroyRenderer(renderer);
    //Destroy window
    if (window) SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();
}

void RecursiveBackTracker::DrawMarker(SDL_Renderer *renderer, int i, int j)
{
    int y = (i * 35) + 20;
    int x = (j * 35) + 20;
    //Render red filled quad
    SDL_Rect fillRect = { x , y , 15, 15 };
    SDL_SetRenderDrawColor( renderer, 0x0, 0xFF, 0x00, 0xFF );
    SDL_RenderFillRect( renderer, &fillRect );
}

void RecursiveBackTracker::DrawArrows(SDL_Renderer *renderer, int i, int j)
{
    int y = (i * 35) + 27;
    int x = (j * 35) + 27;
    int y1;
    int x1;

    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );

    if (IsDoor(Place(i, j), "se"))
    {
        x1 = ((j + 1) * 35) + 27;
        y1 = ((i + 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "e"))
    {
        x1 = ((j + 1) * 35) + 27;
        y1 = (i * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "w"))
    {
        x1 = ((j - 1) * 35) + 27;
        y1 = (i * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "n"))
    {
        x1 = (j * 35) + 27;
        y1 = ((i - 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "s"))
    {
        x1 = (j * 35) + 27;
        y1 = ((i + 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "ne"))
    {
        x1 = ((j + 1) * 35) + 27;
        y1 = ((i - 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "nw"))
    {
        x1 = ((j - 1) * 35) + 27;
        y1 = ((i - 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
    if (IsDoor(Place(i, j), "sw"))
    {
        x1 = ((j - 1) * 35) + 27;
        y1 = ((i + 1) * 35) + 27;
        SDL_RenderDrawLine(renderer, x , y, x1, y1);
        DrawSmallDot(renderer, x1, y1);
    }
}

void RecursiveBackTracker::DrawSmallDot(SDL_Renderer *renderer, int x1, int y1)
{
    SDL_Rect fillRect = { x1 - 3 , y1 - 3 , 7, 7 };
    SDL_RenderFillRect( renderer, &fillRect );
}

void RecursiveBackTracker::DrawOctagon(SDL_Renderer *renderer, int y, int x, int i, int j)
{
    uint8_t doors = _World[i][j].Doors;

    // If the cell doesn't have a door in this direction draw the wall
    if (!(doors & _Dir["n"])) DrawLineN(renderer, y, x);
    if (!(doors & _Dir["ne"])) DrawLineNE(renderer, y, x);
    if (!(doors & _Dir["e"])) DrawLineE(renderer, y, x);
    if (!(doors & _Dir["se"])) DrawLineSE(renderer, y, x);
    if (!(doors & _Dir["s"])) DrawLineS(renderer, y, x);
    if (!(doors & _Dir["sw"])) DrawLineSW(renderer, y, x);
    if (!(doors & _Dir["w"])) DrawLineW(renderer, y, x);
    if (!(doors & _Dir["nw"])) DrawLineNW(renderer, y, x);
}

// Wall drawing...
void RecursiveBackTracker::DrawLineN(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 10, y, x + 25, y);
}

void RecursiveBackTracker::DrawLineNE(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 25, y, x + 35, y + 10);
}

void RecursiveBackTracker::DrawLineE(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 35, y + 10, x + 35, y + 25);
}

void RecursiveBackTracker::DrawLineSE(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 35, y + 25, x + 25, y + 35);
}

void RecursiveBackTracker::DrawLineS(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 25, y + 35, x + 10, y + 35);
}

void RecursiveBackTracker::DrawLineSW(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x + 10, y + 35, x, y + 25);
}

void RecursiveBackTracker::DrawLineW(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x, y + 25, x, y + 10);
}

void RecursiveBackTracker::DrawLineNW(SDL_Renderer *renderer, int y, int x)
{
    SDL_RenderDrawLine(renderer, x, y + 10, x + 10, y);
}

RecursiveBackTracker::~RecursiveBackTracker()
{
    // Destructor
}
