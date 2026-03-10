#pragma once

#include "GLLibs.h"
#include "Poly.h"

namespace GLExtras {

	// The number of frames to show each second.
	const static int FPS = 60;

	const static int REFRESHRATE = 1000 / FPS;

	/// <summary>
	/// Adds a vertex to the scene. 
	/// </summary>
	/// <param name="position">The x,y, and z of the vertex's location in the scene. </param>
	void AddVertex(const Vector3& position);

	/// <summary>
	/// Add vertices to the scene. 3 vertices make a triangle.
	/// </summary>
	/// <param name="points_array">Each Vector3 represents the x, y, and z of a vertex.</param>
	/// <param name="length">The length of the array.</param>
	void AddVertices(Vector3* points_array, int length);

	void AddPolygon(const Poly& polygon);

	void AddPolygons(Poly* polygons, int length);

	/// <summary>
	/// Set The current vertex colour using a 8 digit hexadecimal code. <br/>
	/// 2 digits for red, green, blue, and alpha.
	/// </summary>
	/// <param name="Hex">Example: <c>0xff0000ff</c> is the hex code for red.</param>
	void SetColourHexRGBA(const uint32& hex);

	/// <summary>
	/// Set The current vertex colour using a 6 digit hexadecimal code. <br/>
	/// 2 digits for red, green, and blue.
	/// </summary>
	/// <param name="Hex">Example: <c>0xff0000</c> is the hex code for red.</param>
	void SetColourHexRGB(const uint32& hex);

	/// <summary>
	/// Set The current vertex colour. 
	/// </summary>
	/// <param name="r">The amount of red. (0-1)</param>
	/// <param name="g">The amount of green. (0-1)</param>
	/// <param name="b">The amount of blue. (0-1)</param>
	/// <param name="a">The colour's opacity. (0-1)</param>
	void SetColour(const short& r, const short& g, const short& b, const short& a);

	/// <summary>
	/// Set The current vertex colour. 
	/// </summary>
	/// <param name="colour">The colour you would like to use.</param>
	void SetColour(const Colour& colour);



}