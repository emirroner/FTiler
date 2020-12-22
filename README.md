# FTiler
simple and fast tilemap library for SFML


**CODING**
```
TILE_NUMBER.COLUMN.ROW.FLIP.GHOST_TILE|...

-Textures are sliced with given crop width
 TILE_NUMBER is sliced texture number

-COLUMN and ROW determine its position in the grid

-FLIP, flip the tile
 FLIP = 0 : no flip
 FLIP = 1 : flip horizontally
 FLIP = 2 : flip vertically
 FLIP = 3 : flip both

-GHOST_TILE is needed in FTiler::getTileRect
 FTiler::getTileRect ignores tile if ghostTile of tile value is 1
 so you can get tile rects you want
```
