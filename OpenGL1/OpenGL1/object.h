#ifndef _OBJECT_H
#define _OBJECT_H
#define MAX_VERTICES 800000 // Max number of vertices (for each object)
#define MAX_POLYGONS 800000 // Max number of polygons (for each object)
//#define MAX_OBJECTS 100 // Max number of objects
/*********************************************************
TYPES DECLARATION
*********************************************************/
// Our vertex type
typedef struct
{
	float x, y, z;
}vertex_type;
// The polygon(triangle), 3 numbers that aim 3 vertices
typedef struct
{
	unsigned short a, b, c;
}polygon_type;
// The mapcoord type, 2 texture coordinates for each vertex
typedef struct
{
	float u, v;
}mapcoord_type;
// The object type
typedef struct
{
	char name[20]; // Name of the object
	
	int vertices_qty; // Number of vertices
	int polygons_qty; // Number of polygons
	
	vertex_type vertex[MAX_VERTICES]; // Array of vertices
	vertex_type normal[MAX_VERTICES]; // Array of the vertices' normals
	polygon_type polygon[MAX_POLYGONS]; // Array of polygons (numbers that point to the vertices' list)
	mapcoord_type mapcoord[MAX_VERTICES]; // Array of U,V coordinates for texture mapping
	
	int id_texture; // Number of the texture 
	//matrix_4x4_type matrix; // Object matrix
} obj_type, *obj_type_ptr;
#endif