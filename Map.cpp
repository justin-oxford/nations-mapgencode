#include "Map.h"

Map::Map(unsigned short int land, unsigned short int temp, unsigned short int age, unsigned short int climate)
{
    // default map parameters
    map_setting[0] = land; // landmass
    map_setting[1] = temp; // temperature
    map_setting[2] = age; // climate
    map_setting[3] = climate; // age
    this->textureResolution = 32;
    this->genMap();
}

Map::~Map()
{

}

// Map generation handler
void Map::genMap()
{

    mapDims = Vector2i(160, 90);
    tileSize = 10;

    mapTest.clear();
    mapTest.setPrimitiveType(sf::Quads);
    mapTest.resize(mapDims.x * mapDims.y * 4);
    this->layers = 1;

    map.clear(); // clean the map off
    map.resize(mapDims.x, std::vector<std::vector<Tile>>(mapDims.y, std::vector<Tile>(1, Tile(0))));
    srand(time(0));
    map = mapBuilderLandmass(mapDims, tileSize, this->map);
    this->mapTexture.loadFromFile("Resources/Images/Sprites/32_px_tileMap.jpg");
    unsigned int types[9] = {};
    for (int y = 1; y < mapDims.y - 1; y++)
    {
        for (int x = 1; x < mapDims.x - 1; x++)
        {
            // get a pointer to the current tile's quad
            sf::Vertex* quad = &mapTest[(x + y * mapDims.x) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
            quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
            quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
            quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);
            
            types[4] = map[x][y][0].returnType(); // the tile
            
            if (types[4] == 0) // ocean
            {
                int tl_X = 1 + (rand() % 127); // get random coordinates from the ocean texture for variation
                int tl_Y = 1 + (rand() % 19);  // get random coordinates from the ocean texture for variation
                quad[0].texCoords = sf::Vector2f(tl_X, tl_Y);
                quad[1].texCoords = sf::Vector2f(tl_X + this->textureResolution, tl_Y);
                quad[2].texCoords = sf::Vector2f(tl_X + this->textureResolution, tl_Y + this->textureResolution);
                quad[3].texCoords = sf::Vector2f(tl_X, tl_Y + this->textureResolution);
            }
            else // land
            {
                // Get the type of land (i.e. corner, top, botton, etc)
                // there are 47 types
                // We generate a bitmask based on the surrounding tile types and generate the tile type from this
                
                types[0] = map[x - 1][y - 1][0].returnType(); // tile to the top left
                types[1] = map[x][y - 1][0].returnType(); // tile to the top center
                types[2] = map[x + 1][y - 1][0].returnType(); // tile to the top right
                types[3] = map[x - 1][y][0].returnType(); // tile to the center left
                //
                types[5] = map[x + 1][y][0].returnType(); // tile to the center right
                types[6] = map[x - 1][y + 1][0].returnType(); // tile to the bottom left
                types[7] = map[x][y + 1][0].returnType(); // tile to the bottom center
                types[8] = map[x + 1][y + 1][0].returnType(); // tile to the bottom right

                if (types[1] == 0) {
                    types[0] = 0;
                    types[2] = 0;
                }
                if (types[3] == 0) {
                    types[0] = 0;
                    types[6] = 0;
                }
                if (types[5] == 0) {
                    types[2] = 0;
                    types[8] = 0;
                }
                if (types[7] == 0) {
                    types[6] = 0;
                    types[8] = 0;
                }

                // generate the bitmask that gives a unique type/arrangement
                unsigned short int btMask =
                    (1 * types[0]) +
                    (2 * types[1]) +
                    (4 * types[2]) +
                    (8 * types[3]) +
                    (16 * types[5]) +
                    (32 * types[6]) +
                    (64 * types[7]) +
                    (128 * types[8])
                    ;

                unsigned short int tl;
                // assign the appropriate texture coordinate (i.e. top, bottom, bottom left, etc)
                if (btMask == 2)
                {
                    tl = 4;
                }
                else if (btMask == 8)
                {
                    tl = 5;
                }
                else if (btMask == 10)
                {
                    tl = 6;
                }
                else if (btMask == 11)
                {
                    tl = 7;
                }
                else if (btMask == 16)
                {
                    tl = 8;
                }
                else if (btMask == 18)
                {
                    tl = 9;
                }
                else if (btMask == 22)
                {
                    tl = 10;
                }
                else if (btMask == 24)
                {
                    tl = 11;
                }
                else if (btMask == 26)
                {
                    tl = 12;
                }
                else if (btMask == 27)
                {
                    tl = 13;
                }
                else if (btMask == 30)
                {
                    tl = 14;
                }
                else if (btMask == 31)
                {
                    tl = 15;
                }
                else if (btMask == 64)
                {
                    tl = 16;
                }
                else if (btMask == 66)
                {
                    tl = 17;
                }
                else if (btMask == 72)
                {
                    tl = 18;
                }
                else if (btMask == 74)
                {
                    tl = 19;
                }
                else if (btMask == 75)
                {
                    tl = 20;
                }
                else if (btMask == 80)
                {
                    tl = 21;
                }
                else if (btMask == 82)
                {
                    tl = 22;
                }
                else if (btMask == 86)
                {
                    tl = 23;
                }
                else if (btMask == 88)
                {
                    tl = 24;
                }
                else if (btMask == 90)
                {
                    tl = 25;
                }
                else if (btMask == 91)
                {
                    tl = 26;
                }
                else if (btMask == 94)
                {
                    tl = 27;
                }
                else if (btMask == 95)
                {
                    tl = 28;
                }
                else if (btMask == 104)
                {
                    tl = 29;
                }
                else if (btMask == 106)
                {
                    tl = 30;
                }
                else if (btMask == 107)
                {
                    tl = 31;
                }
                else if (btMask == 120)
                {
                    tl = 32;
                }
                else if (btMask == 122)
                {
                    tl = 33;
                }
                else if (btMask == 123)
                {
                    tl = 34;
                }
                else if (btMask == 126)
                {
                    tl = 35;
                }
                else if (btMask == 127)
                {
                    tl = 36;
                }
                else if (btMask == 208)
                {
                    tl = 37;
                }
                else if (btMask == 210)
                {
                    tl = 38;
                }
                else if (btMask == 214)
                {
                    tl = 39;
                }
                else if (btMask == 216)
                {
                    tl = 40;
                }
                else if (btMask == 218)
                {
                    tl = 41;
                }
                else if (btMask == 219)
                {
                    tl = 42;
                }
                else if (btMask == 222)
                {
                    tl = 43;
                }
                else if (btMask == 223)
                {
                    tl = 44;
                }
                else if (btMask == 248)
                {
                    tl = 45;
                }
                else if (btMask == 250)
                {
                    tl = 46;
                }
                else if (btMask == 251)
                {
                    tl = 47;
                }
                else if (btMask == 254)
                {
                    tl = 48;
                }
                else if (btMask == 255)
                {
                    tl = 3;
                }
                else if (btMask == 0)
                {
                    tl = 49;
                }
                unsigned short int tl_X;
                unsigned short int tl_Y;
                if (tl != 3)
                {
                    //tl_X = 1 + ((rand() % 8) * 34);
                    tl_X = 1;
                    tl_Y = 1 + (tl * 34);
                    //tl_X = 1 + (rand() % 239);
                    //tl_Y = 69 + (rand() % 34);
                }
                else
                {
                    tl_X = 1 + (rand() % 239);
                    tl_Y = 69 + (rand() % 34);
                }
                quad[0].texCoords = sf::Vector2f(tl_X, tl_Y);
                quad[1].texCoords = sf::Vector2f(tl_X + this->textureResolution, tl_Y);
                quad[2].texCoords = sf::Vector2f(tl_X + this->textureResolution, tl_Y + this->textureResolution);
                quad[3].texCoords = sf::Vector2f(tl_X, tl_Y + this->textureResolution);
            }
            
        }
    }
}

// landmass builder -- follows Civ 1 style land generation 
std::vector< std::vector< std::vector<Tile> >> Map::mapBuilderLandmass(sf::Vector2i mapDims, unsigned int tileSize, std::vector< std::vector< std::vector<Tile> >> map_geography)
{
    // total landmass
    int total_landmass = 0;
    // set landmass limit as percentage
    int max_landmass = (mapDims.x * mapDims.y) * 0.35;

    // terrain generating algorithm
    do
    {
        // reset stencil to all 0's
        // the stencil holds all of the values of the generated map and 'draws' them onto the map
        std::vector< std::vector< std::vector<int> >> map_stencil;
        map_stencil.resize(mapDims.y, std::vector<std::vector<int>>(mapDims.x, std::vector<int>(4, 0)));

        // get random starting position build landmass from
        Vector2i drawing_position;
        drawing_position.x = 2 + (std::rand() % (mapDims.y - 4 + 1));
        drawing_position.y = 2 + (std::rand() % (mapDims.x - 4 + 1));

        // define random path length
        int path_length = 1 + (rand() % 2048);
        while (path_length > 0 && drawing_position.x > 5 && drawing_position.x <= (mapDims.y - 5) && drawing_position.y > 5 && drawing_position.y <= (mapDims.x - 5))
        {
            // set 3 positions to land values to form gamma-shape
            map_stencil[drawing_position.x][drawing_position.y][0] = 15;     // position from the random numbers
            map_stencil[drawing_position.x + 1][drawing_position.y][0] = 15; // position to its right
            map_stencil[drawing_position.x][drawing_position.y + 1][0] = 15; // position to its bottom

            // pick next position
            int draw_direction = rand() % 4;
            if (draw_direction == 0)
            {
                // move north
                drawing_position.y -= 1;
            }
            else if (draw_direction == 1)
            {
                // move south
                drawing_position.y += 1;
            }
            else if (draw_direction == 2)
            {
                // move east
                drawing_position.x += 1;
            }
            else
            {
                // move west
                drawing_position.x -= 1;
            }
            path_length -= 1;
        }

        // merge stencil with geography
        for (int lr = 0; lr < mapDims.y; lr++)
        {
            for (int ud = 0; ud < mapDims.x; ud++)
            {
                int map_val = map_stencil[lr][ud][0];
                if (map_val == 15)
                {
                    // get the current type in this loop
                    unsigned int currentType = this->map[ud][lr][0].returnType();
                    // incriment it by one
                    currentType += 1;
                    // update the map 
                    this->map[ud][lr][0].setType(currentType);
                    // update total landmass -- this is the exit condition, do not delete!
                    total_landmass += 1;
                }
            }
        }
    } while (total_landmass < max_landmass); // continue until done == true

    return map;
}

// checks if mouse is over land
bool Map::getLandCollision(const sf::Vector2f& mousePos)
{
    int check = 0;
    int quadNoX = floor(mousePos.x / tileSize);
    int quadNoY = floor(mousePos.y / tileSize);
    if (
        quadNoX >= 0 &&
        quadNoX < mapDims.x &&
        quadNoY >= 0 &&
        quadNoY < mapDims.y
        )
    {
        sf::Vertex* quad = &mapTest[(quadNoX + quadNoY * mapDims.x) * 4];
        unsigned type = map[quadNoX][quadNoY][0].returnType();
        if (type > 0)
        {
            landCollision = true;
            return true;
        }
        else
        {
            landCollision = false;
            return false;
        }
    }
}

// ####################
// old map builder code
// ####################

//// special thanks to darkpanda on forums.civfanatics.com for this outline of the Civ-1 map generation process
//void Map::mapBuilder()
//{
//    // import map size settings
//    int map_dims_height = m_mapSize.x;
//    int map_dims_width = m_mapSize.y;
//    sf::Vector2u tileSize = sf::Vector2u(256, 256);
//
//    // create the map geography -- actual map that will accrue land
//    std::vector< std::vector< std::vector<int> >> map_geography;
//    map_geography.resize(map_dims_height, std::vector<std::vector<int>>(map_dims_width, std::vector<int>(4, 0)));
//
//    map_geography = mapBuilderLandmass(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    mapBuilderCompiler(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    mapBuilderHighlighter(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    map_geography = mapBuilderTemperature(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    map_geography = mapBuilderClimate(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    map_geography = mapBuilderAge(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    //map_geography = mapBuilderRivers(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    map_geography = mapBuilderPoles(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    //mapBuilderPrinter(map_dims_height, map_dims_width, map_geography);
//
//    mapTextureGenerator(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    mapTextureCoastline(tileSize, map_dims_height, map_dims_width, map_geography);
//
//    mapCloudGenerator(tileSize, map_dims_height, map_dims_width);
//}
//
// map generation algorithm
//
//// this function creates the vertex that displays the map on screen
//void Map::mapBuilderCompiler(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    // load the tileset texture
//    m_mapTexture.loadFromFile("./resource/img/land_water_placeholder_256_4_4.jpg");
//    game_map_display.setPrimitiveType(sf::Quads);
//    game_map_display.resize(map_dims_width * map_dims_height * 4);
//
//    // populate the vertex array, with one quad per tile
//    for (unsigned int m = 0; m < map_dims_height; ++m)
//    {
//        for (unsigned int n = 0; n < map_dims_width; ++n)
//        {
//            // get the current tile number
//            int tileNumber = map_geography[m][n][0];
//
//            // find its position in the tileset texture
//            int tu = tileNumber % (m_mapTexture.getSize().x / tileSize.x);
//            int tv = tileNumber / (m_mapTexture.getSize().x / tileSize.x);
//
//            // get a pointer to the current tile's quad
//            sf::Vertex* quad = &game_map_display[(n + m * map_dims_width) * 4];
//
//            // define its 4 corners
//            quad[0].position = sf::Vector2f(n * tileSize.x, m * tileSize.y);
//            quad[1].position = sf::Vector2f((n + 1) * tileSize.x, m * tileSize.y);
//            quad[2].position = sf::Vector2f((n + 1) * tileSize.x, (m + 1) * tileSize.y);
//            quad[3].position = sf::Vector2f(n * tileSize.x, (m + 1) * tileSize.y);
//
//            // define its 4 texture coordinates
//
//            if (tileNumber == 0)
//            {
//                quad[0].texCoords = sf::Vector2f(0, 0);
//                quad[1].texCoords = sf::Vector2f(256, 0);
//                quad[2].texCoords = sf::Vector2f(256, 256);
//                quad[3].texCoords = sf::Vector2f(0, 256);
//            }
//            else if (tileNumber == 1)
//            {
//                quad[0].texCoords = sf::Vector2f(1 * tileSize.x, 0 * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((1 + 1) * tileSize.x, 0 * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((1 + 1) * tileSize.x, (1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(1 * tileSize.x, (1) * tileSize.y);
//            }
//            else if (tileNumber == 2)
//            {
//                quad[0].texCoords = sf::Vector2f(2 * tileSize.x, 0 * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((2 + 1) * tileSize.x, 0 * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((2 + 1) * tileSize.x, (1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(2 * tileSize.x, (1) * tileSize.y);
//            }
//            else if (tileNumber >= 3)
//            {
//                quad[0].texCoords = sf::Vector2f(3 * tileSize.x, 0 * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((3 + 1) * tileSize.x, 0 * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((3 + 1) * tileSize.x, (1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(3 * tileSize.x, (1) * tileSize.y);
//            }
//        }
//    }
//}
//
//// this function creates the vertex that displays the map on screen
//void Map::mapBuilderHighlighter(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    m_highlightTexture.loadFromFile("./resource/img/highlight.png");
//    map_highlighter.setPrimitiveType(sf::Quads);
//    map_highlighter.resize(map_dims_width * map_dims_height * 4);
//
//    // populate the vertex array, with one quad per tile
//    for (unsigned int m = 0; m < map_dims_height; ++m)
//    {
//        for (unsigned int n = 0; n < map_dims_width; ++n)
//        {
//            // get a pointer to the current tile's quad
//            sf::Vertex* quad = &map_highlighter[(n + m * map_dims_width) * 4];
//
//            // define its 4 corners
//            quad[0].position = sf::Vector2f(n * tileSize.x, m * tileSize.y);
//            quad[1].position = sf::Vector2f((n + 1) * tileSize.x, m * tileSize.y);
//            quad[2].position = sf::Vector2f((n + 1) * tileSize.x, (m + 1) * tileSize.y);
//            quad[3].position = sf::Vector2f(n * tileSize.x, (m + 1) * tileSize.y);
//
//            // define its 4 texture coordinates
//            quad[0].texCoords = sf::Vector2f(128, 128);
//            quad[1].texCoords = sf::Vector2f(128, 128);
//            quad[2].texCoords = sf::Vector2f(128, 128);
//            quad[3].texCoords = sf::Vector2f(128, 128);
//        }
//    }
//}
//
//// this function prints out the map on the console
//void Map::mapBuilderPrinter(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    // print the map for debugging
//    for (int pew = 0; pew < map_dims_height; pew++)
//    {
//        for (int pns = 0; pns < map_dims_width; pns++)
//        {
//            int map_val_print = map_geography[pew][pns][0];
//            if (map_val_print >= 5)
//            {
//                std::cout << "@";
//            }
//            else if (map_val_print >= 1)
//            {
//                std::cout << "#";
//            }
//            else
//            {
//                std::cout << "-";
//            }
//        }
//        std::cout << std::endl;
//    }
//}
//
//// this function runs the tempterature simulation to generate deserts near the equator
//std::vector< std::vector< std::vector<int> >> Map::mapBuilderTemperature(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    // populate the vertex array, with one quad per tile
//    for (unsigned int m = 0; m < map_dims_height; ++m)
//    {
//        for (unsigned int n = 0; n < map_dims_width; ++n)
//        {
//            // get the current tile number
//            int tileNumber = map_geography[m][n][0];
//            int latitude = m - ((map_dims_height / 2));
//            latitude = abs(latitude) - 2;
//            latitude = latitude + (rand() % 6);
//            latitude = ((latitude) / (map_dims_height / 12)) + 1;
//
//            // get a pointer to the current tile's quad
//            sf::Vertex* quad = &game_map_display[(n + m * map_dims_width) * 4];
//
//            if ((latitude == 1 || latitude == 2) && tileNumber != 0) // desert
//            {
//                map_geography[m][n][1] = 1;
//                /*
//                int tile_index = 1;
//                if (tileNumber == 1)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber == 2)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber >= 3)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                */
//            }
//            else if ((latitude == 3 || latitude == 4) && tileNumber != 0) // grass
//            {
//                map_geography[m][n][1] = 0;
//                /*
//                int tile_index = 0;
//                if (tileNumber == 1)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber == 2)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber >= 3)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                */
//            }
//            else if ((latitude == 5 || latitude == 5) && tileNumber != 0) // tundra
//            {
//                map_geography[m][n][1] = 2;
//                /*
//                int tile_index = 2;
//                if (tileNumber == 1)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber == 2)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                else if (tileNumber >= 3)
//                {
//                    quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                    quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                    quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                    quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//                }
//                */
//            }
//            else if ((latitude == 6 || latitude >= 7) && tileNumber != 0) // snow
//            {
//                map_geography[m][n][1] = 3;
//            }
//            /*
//            int tile_index = 3;
//            if (tileNumber == 1)
//            {
//                quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//            }
//            else if (tileNumber == 2)
//            {
//                quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//            }
//            else if (tileNumber >= 3)
//            {
//                quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//            }
//
//        }
//        else if (tileNumber == 0) // ocean
//        {
//            // define its 4 corners
//            quad[0].texCoords = sf::Vector2f(0, 0);
//            quad[1].texCoords = sf::Vector2f(256, 0);
//            quad[2].texCoords = sf::Vector2f(256, 256);
//            quad[3].texCoords = sf::Vector2f(0, 256);
//        }*/
//        }
//    }
//
//    return map_geography;
//}
//
//// this function runs the climate simulation to determine rain fall
//std::vector< std::vector< std::vector<int> >> Map::mapBuilderClimate(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//
//    for (unsigned int m = 0; m < map_dims_height; ++m)
//    {
//        int wetness = 0;
//        for (unsigned int n = 0; n < map_dims_width; ++n)
//        {
//            int latitude = (map_dims_height / 2) - m;
//            latitude = abs(latitude);
//            int tileNumber = map_geography[m][n][0];
//            int tileClimate = map_geography[m][n][1];
//            if (tileNumber == 0)
//            {
//                int yeild = latitude - (map_dims_height / 4);
//                yeild = abs(yeild) + 4;
//                if (yeild > wetness)
//                {
//                    wetness += 1;
//                }
//            }
//            else if (wetness > 0)
//            {
//
//                int rainfall = rand() % 5;
//                wetness -= rainfall;
//                if (tileClimate == 1)
//                {
//                    map_geography[m][n][1] = 0;
//                }
//                else if (tileClimate == 2)
//                {
//                    map_geography[m][n][1] = 3;
//                }
//                if (tileNumber == 2)
//                {
//                    wetness -= 3;
//                }
//                if (wetness < 0)
//                {
//                    wetness = 0;
//                }
//            }
//        }
//        wetness = 0;
//        for (int n = map_dims_width - 1; n >= 0; --n)
//        {
//            int latitude = (map_dims_height / 2) - m;
//            latitude = abs(latitude);
//            int tileNumber = map_geography[m][n][0];
//            int tileClimate = map_geography[m][n][1];
//            if (tileNumber == 0)
//            {
//                int yeild = latitude - (map_dims_height / 4);
//                yeild = abs(yeild) + 4;
//                if (yeild > wetness)
//                {
//                    wetness += 1;
//                }
//            }
//            else if (wetness > 0)
//            {
//
//                int rainfall = rand() % 5;
//                wetness -= rainfall;
//                if (tileClimate == 1)
//                {
//                    map_geography[m][n][1] = 0;
//                }
//                if (tileNumber == 2)
//                {
//                    wetness -= 3;
//                }
//                if (wetness < 0)
//                {
//                    wetness = 0;
//                }
//            }
//        }
//    }
//    return map_geography;
//}
//
//// this function ages the map by randomly changing tiles and evoling mountains
//std::vector< std::vector< std::vector<int> >> Map::mapBuilderAge(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    int erosion_time = 800 * (1 + 1);
//    for (int ero = 0; ero < erosion_time; ++ero)
//    {
//        int action = ero % 2;
//        if (action == 0)
//        {
//            // get random starting position build landmass from
//            Vector2i adjustment_tile;
//            adjustment_tile.x = std::rand() % (map_dims_width);
//            adjustment_tile.y = std::rand() % (map_dims_height);
//            int curTileGeog = map_geography[adjustment_tile.y][adjustment_tile.x][0];
//            int curTileType = map_geography[adjustment_tile.y][adjustment_tile.x][1];
//
//            if (curTileGeog != 0)
//            {
//                int newTileGeog = newTileTypeCalc(curTileGeog, curTileType);
//                map_geography[adjustment_tile.y][adjustment_tile.x][0] = newTileGeog;
//            }
//        }
//        else
//        {
//            //
//        }
//    }
//
//    return map_geography;
//}
//
//int Map::newTileTypeCalc(int currentTileGeography, int currentTileType)
//{
//    if (currentTileGeography == 2)
//    {
//        int newTileGeography = 3;
//        return newTileGeography;
//    }
//}
//
//std::vector< std::vector< std::vector<int> >> Map::mapBuilderRivers(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    return map_geography;
//}
//
//std::vector< std::vector< std::vector<int> >> Map::mapBuilderPoles(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    for (int northPole = 0; northPole < map_dims_width; ++northPole)
//    {
//        map_geography[0][northPole][0] = 1;
//        map_geography[0][northPole][1] = 3;
//        map_geography[map_dims_height - 1][northPole][0] = 1;
//        map_geography[map_dims_height - 1][northPole][1] = 3;
//    }
//
//    for (int polesRand = 0; polesRand < map_dims_width / 4; ++polesRand)
//    {
//        int rando = rand() % map_dims_width;
//        map_geography[1][rando][0] = 1;
//        map_geography[1][rando][1] = 3;
//        rando = rand() % map_dims_width;
//        map_geography[2][rando][0] = 1;
//        map_geography[2][rando][1] = 3;
//        rando = rand() % map_dims_width;
//        map_geography[map_dims_height - 2][rando][0] = 1;
//        map_geography[map_dims_height - 2][rando][1] = 3;
//        rando = rand() % map_dims_width;
//        map_geography[map_dims_height - 3][rando][0] = 1;
//        map_geography[map_dims_height - 3][rando][1] = 3;
//    }
//
//    return map_geography;
//}
//
//void Map::mapTextureGenerator(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    // populate the vertex array, with one quad per tile
//    for (unsigned int m = 0; m < map_dims_height; ++m)
//    {
//        for (unsigned int n = 0; n < map_dims_width; ++n)
//        {
//            // get the current tile number
//            int tileNumber = map_geography[m][n][0];
//
//            // get a pointer to the current tile's quad
//            sf::Vertex* quad = &game_map_display[(n + m * map_dims_width) * 4];
//
//            if (tileNumber != 0) // land
//            {
//                int tile_index = map_geography[m][n][1];
//                quad[0].texCoords = sf::Vector2f(tileNumber * tileSize.x, tile_index * tileSize.y);
//                quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, tile_index * tileSize.y);
//                quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize.x, (tile_index + 1) * tileSize.y);
//                quad[3].texCoords = sf::Vector2f(tileNumber * tileSize.x, (tile_index + 1) * tileSize.y);
//
//            }
//            else // ocean
//            {
//                // define its 4 corners
//                quad[0].texCoords = sf::Vector2f(0, 0);
//                quad[1].texCoords = sf::Vector2f(256, 0);
//                quad[2].texCoords = sf::Vector2f(256, 256);
//                quad[3].texCoords = sf::Vector2f(0, 256);
//            }
//        }
//    }
//}
//
//void Map::mapTextureCoastline(sf::Vector2u tileSize, int map_dims_height, int map_dims_width, std::vector< std::vector< std::vector<int> >> map_geography)
//{
//    // load the tileset texture
//    m_coastlineTexture.loadFromFile("./resource/img/Coastline_1.png");
//    coastline_display.clear();
//    coastline_display.setPrimitiveType(sf::Quads);
//    coastline_display.resize(map_dims_width * map_dims_height * 36);
//    int tileSurrounding[9];
//    const int spacing[3][3][2] = {
//        {{112,112},{32,112},{112,112}},
//        {{112,32},{32,32},{112,32}},
//        {{112,112},{32,112},{112,112}},
//    };
//    int last_topLeft_x = 0;
//    int last_topLeft_y = 0;
//    int counter = 0;
//    int top_left_x;
//    int top_left_y;
//    // populate the vertex array, with one quad per tile
//    for (unsigned int m = 1; m < map_dims_height - 1; ++m)
//    {
//        for (unsigned int n = 1; n < map_dims_width - 1; ++n)
//        {
//            // get the current tile number
//            //int tileNum = map_geography[m][n][0];
//            if (m > 0 && m < map_dims_height - 1 && n > 0 && n < map_dims_width - 1)
//            {
//                tileSurrounding[0] = map_geography[m - 1][n - 1][0]; // top left
//                tileSurrounding[1] = map_geography[m - 1][n][0];     // top middle
//                tileSurrounding[2] = map_geography[m - 1][n + 1][0]; // top right
//                tileSurrounding[3] = map_geography[m][n - 1][0];     // mid left
//                tileSurrounding[4] = map_geography[m][n][0];         // TILE ITSELF
//                tileSurrounding[5] = map_geography[m][n + 1][0];     // mid right
//                tileSurrounding[6] = map_geography[m + 1][n - 1][0]; // bot left
//                tileSurrounding[7] = map_geography[m + 1][n][0];     // bot middle
//                tileSurrounding[8] = map_geography[m + 1][n + 1][0]; // bot right
//            };
//
//            last_topLeft_x = 0;
//            last_topLeft_y = 0;
//            counter = 0;
//            if (tileSurrounding[4] == 0) {
//                // generate each 3x3 block based on spacing
//                for (int w = 0; w < 3; ++w) {   // scan the rows
//                    for (int h = 0; h < 3; ++h) // scan the columns 
//                    {
//                        int width = spacing[w][h][0];
//                        int height = spacing[w][h][1];
//                        // get a pointer to the current tile's quad
//                        int quad_no = (((n * 9) + (m * (map_dims_width * 9))) * 4) + (4 * counter);
//                        sf::Vertex* quad = &coastline_display[quad_no];
//
//                        top_left_x = n * tileSize.x;
//                        top_left_y = m * tileSize.y;
//
//                        // top left box
//                        quad[0].position = sf::Vector2f(top_left_x + last_topLeft_x, top_left_y + last_topLeft_y);
//                        quad[1].position = sf::Vector2f(top_left_x + last_topLeft_x + width, top_left_y + last_topLeft_y);
//                        quad[2].position = sf::Vector2f(top_left_x + last_topLeft_x + width, top_left_y + last_topLeft_y + height);
//                        quad[3].position = sf::Vector2f(top_left_x + last_topLeft_x, top_left_y + last_topLeft_y + height);
//
//                        if (counter == 0)
//                        {
//                            if (tileSurrounding[0] != 0 && tileSurrounding[1] == 0 && tileSurrounding[3] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(256, 768);
//                                quad[1].texCoords = sf::Vector2f(400, 768);
//                                quad[2].texCoords = sf::Vector2f(400, 912);
//                                quad[3].texCoords = sf::Vector2f(256, 912);
//                            }
//                            else if (tileSurrounding[3] != 0 && tileSurrounding[1] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(0, 256);
//                                quad[1].texCoords = sf::Vector2f(144, 256);
//                                quad[2].texCoords = sf::Vector2f(144, 368);
//                                quad[3].texCoords = sf::Vector2f(0, 368);
//                            }
//                            else if (tileSurrounding[3] == 0 && tileSurrounding[1] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(256, 256);
//                                quad[1].texCoords = sf::Vector2f(368, 256);
//                                quad[2].texCoords = sf::Vector2f(368, 400);
//                                quad[3].texCoords = sf::Vector2f(256, 400);
//                            }
//                            else if (tileSurrounding[3] != 0 && tileSurrounding[1] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(0, 512);
//                                quad[1].texCoords = sf::Vector2f(144, 512);
//                                quad[2].texCoords = sf::Vector2f(144, 656);
//                                quad[3].texCoords = sf::Vector2f(0, 656);
//                            }
//                        }
//                        else if (counter == 1 && tileSurrounding[1] != 0) {
//                            // define its 4 corners
//                            quad[0].texCoords = sf::Vector2f(368, 0);
//                            quad[1].texCoords = sf::Vector2f(400, 0);
//                            quad[2].texCoords = sf::Vector2f(400, 144);
//                            quad[3].texCoords = sf::Vector2f(368, 144);
//                        }
//                        else if (counter == 2)
//                        {
//                            if (tileSurrounding[2] != 0 && tileSurrounding[1] == 0 && tileSurrounding[5] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(624, 768);
//                                quad[1].texCoords = sf::Vector2f(768, 768);
//                                quad[2].texCoords = sf::Vector2f(768, 912);
//                                quad[3].texCoords = sf::Vector2f(624, 912);
//                            }
//                            else if (tileSurrounding[1] != 0 && tileSurrounding[5] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(400, 256);
//                                quad[1].texCoords = sf::Vector2f(512, 256);
//                                quad[2].texCoords = sf::Vector2f(512, 400);
//                                quad[3].texCoords = sf::Vector2f(400, 400);
//                            }
//                            else if (tileSurrounding[1] == 0 && tileSurrounding[5] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(624, 256);
//                                quad[1].texCoords = sf::Vector2f(768, 256);
//                                quad[2].texCoords = sf::Vector2f(768, 368);
//                                quad[3].texCoords = sf::Vector2f(624, 368);
//                            }
//                            else if (tileSurrounding[1] != 0 && tileSurrounding[5] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(368, 512);
//                                quad[1].texCoords = sf::Vector2f(512, 512);
//                                quad[2].texCoords = sf::Vector2f(512, 656);
//                                quad[3].texCoords = sf::Vector2f(368, 656);
//                            }
//                        }
//                        else if (counter == 3 && tileSurrounding[3] != 0) {
//                            // define its 4 corners
//                            quad[0].texCoords = sf::Vector2f(0, 112);
//                            quad[1].texCoords = sf::Vector2f(144, 112);
//                            quad[2].texCoords = sf::Vector2f(144, 144);
//                            quad[3].texCoords = sf::Vector2f(0, 144);
//                        }
//                        else if (counter == 4)
//                        {
//                            // middle tile :)
//                        }
//                        else if (counter == 5 && tileSurrounding[5] != 0) {
//                            // define its 4 corners
//                            quad[0].texCoords = sf::Vector2f(624, 112);
//                            quad[1].texCoords = sf::Vector2f(768, 112);
//                            quad[2].texCoords = sf::Vector2f(768, 144);
//                            quad[3].texCoords = sf::Vector2f(624, 144);
//                        }
//                        else if (counter == 6)
//                        {
//                            if (tileSurrounding[6] != 0 && tileSurrounding[3] == 0 && tileSurrounding[7] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(0, 880);
//                                quad[1].texCoords = sf::Vector2f(144, 880);
//                                quad[2].texCoords = sf::Vector2f(144, 1024);
//                                quad[3].texCoords = sf::Vector2f(0, 1024);
//                            }
//                            else if (tileSurrounding[3] != 0 && tileSurrounding[7] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(0, 400);
//                                quad[1].texCoords = sf::Vector2f(144, 400);
//                                quad[2].texCoords = sf::Vector2f(144, 512);
//                                quad[3].texCoords = sf::Vector2f(0, 512);
//                            }
//                            else if (tileSurrounding[3] == 0 && tileSurrounding[7] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(768, 368);
//                                quad[1].texCoords = sf::Vector2f(880, 368);
//                                quad[2].texCoords = sf::Vector2f(880, 512);
//                                quad[3].texCoords = sf::Vector2f(768, 512);
//                            }
//                            else if (tileSurrounding[3] != 0 && tileSurrounding[7] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(768, 624);
//                                quad[1].texCoords = sf::Vector2f(912, 624);
//                                quad[2].texCoords = sf::Vector2f(912, 768);
//                                quad[3].texCoords = sf::Vector2f(768, 768);
//                            }
//                        }
//                        else if (counter == 7 && tileSurrounding[7] != 0) {
//                            // define its 4 corners
//                            quad[0].texCoords = sf::Vector2f(880, 112);
//                            quad[1].texCoords = sf::Vector2f(912, 112);
//                            quad[2].texCoords = sf::Vector2f(912, 256);
//                            quad[3].texCoords = sf::Vector2f(880, 256);
//                        }
//                        else if (counter == 8)
//                        {
//                            if (tileSurrounding[8] != 0 && tileSurrounding[5] == 0 && tileSurrounding[7] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(880, 880);
//                                quad[1].texCoords = sf::Vector2f(1024, 880);
//                                quad[2].texCoords = sf::Vector2f(1024, 1024);
//                                quad[3].texCoords = sf::Vector2f(880, 1024);
//                            }
//                            else if (tileSurrounding[5] != 0 && tileSurrounding[7] == 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(624, 400);
//                                quad[1].texCoords = sf::Vector2f(768, 400);
//                                quad[2].texCoords = sf::Vector2f(768, 512);
//                                quad[3].texCoords = sf::Vector2f(624, 512);
//                            }
//                            else if (tileSurrounding[5] == 0 && tileSurrounding[7] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(912, 368);
//                                quad[1].texCoords = sf::Vector2f(1024, 368);
//                                quad[2].texCoords = sf::Vector2f(1024, 512);
//                                quad[3].texCoords = sf::Vector2f(912, 512);
//                            }
//                            else if (tileSurrounding[5] != 0 && tileSurrounding[7] != 0)
//                            {
//                                quad[0].texCoords = sf::Vector2f(624, 624);
//                                quad[1].texCoords = sf::Vector2f(768, 624);
//                                quad[2].texCoords = sf::Vector2f(768, 768);
//                                quad[3].texCoords = sf::Vector2f(624, 768);
//                            }
//                        }
//
//                        last_topLeft_x = last_topLeft_x + width;
//                        last_topLeft_y = last_topLeft_y;
//                        counter += 1;
//                    }
//                    last_topLeft_x = 0;
//                    last_topLeft_y += spacing[w][0][1];
//                }
//            }
//        }
//    }
//}
//
//void Map::mapCloudGenerator(Vector2u tileSize, int map_height, int map_width)
//{
//    // load the tileset texture
//    m_cloudsTexture.loadFromFile("./resource/img/clouds.png");
//    map_clouds.clear();
//    map_clouds.setPrimitiveType(sf::Quads);
//    map_clouds.resize(4);
//    sf::Vertex* quad = &map_clouds[0];
//
//    // top left box
//    quad[0].position = sf::Vector2f(0, 0);
//    quad[1].position = sf::Vector2f(tileSize.x * map_width, 0);
//    quad[2].position = sf::Vector2f(tileSize.x * map_width, tileSize.x * map_height);
//    quad[3].position = sf::Vector2f(0, tileSize.x * map_height);
//
//    quad[0].texCoords = sf::Vector2f(0, 0);
//    quad[1].texCoords = sf::Vector2f(3840, 0);
//    quad[2].texCoords = sf::Vector2f(3840, 2160);
//    quad[3].texCoords = sf::Vector2f(0, 2160);
//
//    quad[0].color = sf::Color::Color(255, 255, 255, 0);
//    quad[1].color = sf::Color::Color(255, 255, 255, 0);
//    quad[2].color = sf::Color::Color(255, 255, 255, 0);
//    quad[3].color = sf::Color::Color(255, 255, 255, 0);
//}

void Map::update(const sf::Vector2f& mousePos)
{
    getLandCollision(mousePos);
}
// Render Map
void Map::render(sf::RenderTarget & target)
{
    target.draw(mapTest, &mapTexture);
}