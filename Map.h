#pragma once

#include "Entity.h"
#include "Tile.h"

using namespace sf;

class Map 
{
private:
    float gridSizeF;
    unsigned gridSizeU;
    sf::Vector2u mapSize;
    unsigned layers;
    std::vector< std::vector <std::vector< Tile > > > map;

    sf::VertexArray mapTest;
    sf::Texture mapTexture;
    unsigned short int textureResolution;
    bool landCollision;
     
public:

    // mapsizer (x=Width, y=Height)
    Vector2i mapDims;
    unsigned int tileSize;

    Map(unsigned short int land, unsigned short int temp, unsigned short int age, unsigned short int climate);
    virtual ~Map();

    // Map Generation Functions
    void genMap();

    // Map Functions
    bool getLandCollision(const sf::Vector2f& mousePos);

    //void mapBuilder();
    std::vector< std::vector< std::vector<Tile> >> mapBuilderLandmass(sf::Vector2i mapDims, unsigned int tileSize, std::vector< std::vector< std::vector<Tile> >>);

    // OLD MAP BUILDER FCNS

    //void mapBuilderCompiler(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //void mapBuilderHighlighter(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //void mapBuilderPrinter(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //std::vector< std::vector< std::vector<int> >> mapBuilderTemperature(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //std::vector< std::vector< std::vector<int> >> mapBuilderClimate(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //std::vector< std::vector< std::vector<int> >> mapBuilderAge(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //int newTileTypeCalc(int, int);
    //std::vector< std::vector< std::vector<int> >> mapBuilderRivers(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //std::vector< std::vector< std::vector<int> >> mapBuilderPoles(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //void mapTextureGenerator(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    //void mapTextureCoastline(Vector2u, int, int, std::vector< std::vector< std::vector<int> >>);
    ////int mapTextureCoastlineTexture();
    //void mapCloudGenerator(Vector2u, int, int);

    // map settings [landmass,temperature,climate,age]
    int map_setting[4];
    virtual void update(const sf::Vector2f& mousePos);
    virtual void render(sf::RenderTarget& target);
};

