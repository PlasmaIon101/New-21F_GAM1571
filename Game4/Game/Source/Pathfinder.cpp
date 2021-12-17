#include "Framework.h"

#include "Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap)
{
    m_pTilemap = pTilemap;
    m_MapWidth = pTilemap->GetWidth();
    m_MapHeight = pTilemap->GetHeight();

    m_Nodes.resize( m_MapWidth * m_MapHeight );
}

Pathfinder::~Pathfinder()
{
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    //Step 1. Reset everything. (DONE)
    Reset();

    //Step 2. Get both tile indicies via ints. (DONE)
    int startTileIndex = sy * m_MapWidth + sx;
    int endTileIndex = ey * m_MapWidth + ex;

    //Step 3: Open starting nodes. (DONE)
    m_Nodes[startTileIndex].cost = 0;
    m_Nodes[startTileIndex].status = PathNode::PathNodeStatus::Open;
    m_OpenTileIndexs.push_back(startTileIndex);

    //Step 4. Loop while nodes are open. (CONSTRUCTED)
    while (m_OpenTileIndexs.size() > 0)
    {
        //Step 5. Find the Lowest 'F' score, make it the current node. (Fill function)
        //Step 6. Remove the node from the open list (In function?)
        int CurrentIndex = FindLowestCostNodeFromOpenListAndDeleteIt();
        //Step 7. If we took the end node from the open list, we're done. (DONE)

        if (CurrentIndex == endTileIndex)
        {
            return true; //Path found!
        }

        //Step 8. Mark the current node as Closed. (DONE)
        m_Nodes[CurrentIndex].status = PathNode::PathNodeStatus::Closed;

        //Step 9. Loop through neighbouring tiles and add them to the open list.
        std::vector<int> neighbours = MakeListOfValidNeighbours(CurrentIndex); //Function incomplete.
        for (int i = 0; i < neighbours.size(); i++)
        {
            int neighbourIndex = neighbours[i];

            //Add neighbour to open list, if it's not already in there.
            if (m_Nodes[neighbourIndex].status == PathNode::PathNodeStatus::Unchecked)
            {
                m_Nodes[neighbourIndex].status = PathNode::PathNodeStatus::Open;
                m_OpenTileIndexs.push_back(neighbourIndex);
            }

            //Check if we found a cheaper path to this neighbour node.
            int newCost = m_Nodes[CurrentIndex].cost + 1;
            if (newCost < m_Nodes[neighbourIndex].cost)
            {
                //This path is cheaper, so update all pathNode properties.
                m_Nodes[neighbourIndex].cost = newCost;
                m_Nodes[neighbourIndex].heuristic = CalculateHeuristic(neighbourIndex, endTileIndex);
                m_Nodes[neighbourIndex].finalCost = m_Nodes[neighbourIndex].cost + m_Nodes[neighbourIndex].heuristic;

                m_Nodes[neighbourIndex].parentNodeIndex = CurrentIndex;
            }
        }
    }

    //Step 10. If no nodes are in the open list, return false. (DONE)
    return false; //    :(
}

std::vector<int> Pathfinder::GetPath(int index1)
{
    int index = index1;
    std::vector<int> path;
    while (index > -1)
    {
        path.push_back(index);
        index = m_Nodes[index].parentNodeIndex;
    }

    return path;
}

std::vector<int> Pathfinder::GetPath(int x, int y)
{
    int index = x + y * m_MapWidth;
    
    return GetPath(index);
}

vec2 Pathfinder::GetWorldPosition(int index)
{
    return vec2(index % m_MapWidth, index / m_MapWidth) * m_pTilemap->GetTileSize();
}

void Pathfinder::Reset()
{
    m_OpenTileIndexs.clear();
    for (int i = 0; i < m_Nodes.size(); i++)
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].status = PathNode::PathNodeStatus::Unchecked;

        m_Nodes[i].cost = FLT_MAX;
        m_Nodes[i].finalCost = FLT_MAX;
        m_Nodes[i].heuristic = FLT_MAX;
    }
}

int Pathfinder::FindLowestCostNodeFromOpenListAndDeleteIt()
{
    int savedNodeIndex = 0;
    //TODO: Find node with lowest finalCost.
    for (int i = 0; i < m_OpenTileIndexs.size(); i++)
    {
        if (m_Nodes[m_OpenTileIndexs[i]].finalCost < m_Nodes[m_OpenTileIndexs[savedNodeIndex]].finalCost)
        {
            savedNodeIndex = i;
        }
    }
    int returnedValue = m_OpenTileIndexs[savedNodeIndex];
    m_OpenTileIndexs.erase(m_OpenTileIndexs.begin() + savedNodeIndex);
    //m_Nodes.erase(m_Nodes.begin() + savedNode);
    return returnedValue;
}

std::vector<int> Pathfinder::MakeListOfValidNeighbours(int index) //Think this will give me a hard time.
{
    std::vector<int> neighbours;

    //TODO: Check for out of bounds.
    //Not at the right edge, look at the right neighbour. Going right.
    if (index % m_MapWidth < m_MapWidth - 1)
    {
        neighbours.push_back(index + 1);
    }
    // Going left.
    if (index % m_MapWidth > 0)
    {
        neighbours.push_back(index - 1);
    }
    // Going up.
    if (index / m_MapWidth < m_MapHeight - 1)
    {
        neighbours.push_back(index + m_MapWidth);
    }
    // Going down.
    if (index / m_MapWidth > 0)
    {
        neighbours.push_back(index - m_MapWidth);
    }

    //Check if walkable.

    //Check for already closed.
    std::vector<int> listOfReturnedNeighbours;
    for (size_t i = 0; i < neighbours.size(); i++)
    {
        if (!m_pTilemap->IsIndexWalkable(neighbours[i]))
        {
            continue;
        }
        
        if (m_Nodes[neighbours[i]].status == PathNode::PathNodeStatus::Closed)
        {
            m_Nodes[neighbours[i]].status = PathNode::PathNodeStatus::Open;
        }
        listOfReturnedNeighbours.push_back(neighbours[i]);
    }
    
    return listOfReturnedNeighbours;
}

int Pathfinder::CalculateHeuristic(int index1, int index2)
{
    //TODO: Calculate the manhatten distance between these nodes.

    int xValueOne = index1 % m_MapWidth;
    int yValueOne = index1 / m_MapHeight;

    int xValueTwo = index2 % m_MapWidth;
    int yValueTwo = index2 / m_MapHeight;

    return abs(xValueOne - xValueTwo) + abs(yValueOne - yValueTwo);
}
