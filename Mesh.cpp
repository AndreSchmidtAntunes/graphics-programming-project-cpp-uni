#include "Mesh.h"

Mesh::Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count) {
	
	this->vertices_count = vertices_count;
	this->indices_count = indices_count;

	normals = uvs = colours = nullptr;
	normal_indices = uv_indices = nullptr;
	normals_count = uvs_count = colours_count = 0;

	this->normals_count = normals_count;

	this->vertices = new GLfloat[vertices_count];
	for (uint i = 0; i < vertices_count; i++) {
		this->vertices[i] = vertices[i];
	}

	this->indices = new GLuint[indices_count];
	for (uint i = 0; i < indices_count; i++) {
		this->indices[i] = indices[i];
	}
}

Mesh::Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* colours, const uint colours_count) : Mesh(vertices, vertices_count, indices, indices_count) {

	this->colours_count = colours_count;

	normals = uvs = nullptr;
	normal_indices = uv_indices = nullptr;
	normals_count = uvs_count = 0;

	this->colours = new GLfloat[colours_count];
	for (uint i = 0; i < colours_count; i++) {
		this->colours[i] = colours[i];
	}
};

Mesh::Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* normals, const uint normals_count, const double* uvs, const uint uvs_count) : Mesh(vertices, vertices_count, indices, indices_count) {

	this->normals_count = normals_count;
	this->uvs_count = uvs_count;

	colours = nullptr;
	colours_count = 0;
	
	this->normals = new GLfloat[normals_count];
	for (uint i = 0; i < normals_count; i++) {
		this->normals[i] = normals[i];
	}
	
	this->uvs = new GLfloat[uvs_count];
	for (uint i = 0; i < uvs_count; i++) {
		this->uvs[i] = uvs[i];
	}
}

Mesh::Mesh(const double* vertices, const uint vertices_count, const uint* indices, const uint indices_count, const double* normals, const uint normals_count, const double* uvs, const uint uvs_count, const double* colours, const uint colours_count) : Mesh(vertices, vertices_count, indices, indices_count, normals, normals_count, uvs, uvs_count) {
	this->colours_count = colours_count;

	this->colours = new GLfloat[colours_count];
	for (uint i = 0; i < colours_count; i++) {
		this->colours[i] = colours[i];
	}
}

Mesh::~Mesh() {
	delete[this->vertices_count] vertices;
	delete[this->indices_count] indices;
	delete[this->normals_count] normals;
	delete[this->uvs_count] uvs;
	delete[this->colours_count] colours;
}

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

//enum ParseType { POLYGON, VERTEX, NORMAL, TEXTURE, INFO, MATERIALFILE };

bool Mesh::LoadFromFile(const std::string& filename) {

	std::vector<double> vertices, normals, uvs;
	std::vector<uint> indices, uv_indices, normal_indices;

	vertices = normals = uvs = { };
	indices = uv_indices = normal_indices = { };

	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	std::string line = "";

	uint _current_line = 0;
	while (std::getline(file, line)) {
		std::stringstream iss(line);

		_current_line++;

		char type;
		if (iss >> type)
			switch (type)
			{
				case 'v': { // If we are reading a vertex

					double coord;

					while (iss >> coord) 
						vertices.push_back(coord);

					continue;
				}

				case 'f': { // If we are reading a face definition

					//std::vector<uint> indices;
					

					// Loop through however many points are referenced in a face dynamically, as they can have 3 or 4 or 5 etc

					std::string vert_data;
					
					while (iss >> vert_data) {
						std::string indices_str = "";
						std::string uv_indices_str = "";
						std::string normal_indices_str = "";

						uint datatype = 0; // 0 = vert indices, 1 = uv indices, 2 = normal indices
						for (uint i = 0; i < vert_data.length(); i++) {

							while (vert_data[i] == '/') {
								datatype++;
								i++;
							}

							while (std::isspace(vert_data[i])) {
								datatype = 0;
								i++;
							}

							switch (datatype) {

							case 0: indices_str += (vert_data[i]); break;
							case 1: uv_indices_str += (vert_data[i]); break;
							case 2: normal_indices_str += (vert_data[i]); break;

							default: return false;
							}

							
						}

						char* strtol_output;

						indices.push_back(std::strtol(indices_str.c_str(), &strtol_output, 10));
						uv_indices.push_back(std::strtol(uv_indices_str.c_str(), &strtol_output, 10));
						normal_indices.push_back(std::strtol(normal_indices_str.c_str(), &strtol_output, 10));
					}

					continue;
				}
				case 'o': { // comment
					continue;
				}

				case '#': { // comment
					continue;
				} 

				default: { // erroneous first istring
					std::cerr << "Erroneous command at file: " << filename << ", line: " << _current_line << std::endl;
					continue;
				}

			}
	}
	
	this->vertices_count = vertices.size();
	this->indices_count  = indices.size();
	this->normals_count  = normals.size();
	this->uvs_count   =    uvs.size();

	delete[this->vertices_count] this->vertices;
	delete[this->indices_count]  this->indices;
	delete[this->normals_count]  this->normals;
	delete[this->uvs_count]		 this->uvs;

	this->vertices = new GLfloat[vertices_count] {};
	this->normals  = new GLfloat[normals_count] {};
	this->uvs   =	 new GLfloat[uvs_count] {};

	this->indices = new GLuint[indices_count]{};
	this->normal_indices = new GLuint[indices_count]{};
	this->uv_indices = new GLuint[indices_count]{};

	for (uint i = 0; i < vertices_count; i++)
		this->vertices[i] = vertices[i];

	for (uint i = 0; i < normals_count; i++)
		this->normals[i] = normals[i];

	for (uint i = 0; i < uvs_count; i++)
		this->uvs[i] = uvs[i];

	for (uint i = 0; i < indices_count; i++)
		this->indices[i] = indices[i];

	for (uint i = 0; i < indices_count; i++)
		this->normal_indices[i] = normal_indices[i];

	for (uint i = 0; i < indices_count; i++)
		this->uv_indices[i] = uv_indices[i];

	return true;
}

#include "GLExtras.h"

void Mesh::DrawElements() const {
		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);

		if (normals != nullptr && normals_count > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, normals);
		}

		if (uvs != nullptr && uvs_count > 0) {
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, uvs);
		}

		if (colours != nullptr && colours_count > 0) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, 0, colours);
		}
		else
			GLExtras::SetColour(DefaultColour);

		glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, indices);

	
		glDisableClientState(GL_VERTEX_ARRAY);

		if (normals != nullptr)
			glDisableClientState(GL_NORMAL_ARRAY);

		if (normals != nullptr)
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (colours == nullptr)
			glDisableClientState(GL_COLOR_ARRAY);
}

void Mesh::Render(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Camera* camera) const {
	glLoadIdentity();

	glPushMatrix();
	{
		Vector3 rotation_from_camera = -(camera->rotation);

		Vector3 position_from_camera = position - (camera->position);

		//glRotatef(rotation_from_camera.x, 0.0f, -1.0f, 0.0f);
		//glRotatef(rotation_from_camera.y, 0.0f, 0.0f, -1.0f);
		//glRotatef(rotation_from_camera.z, -1.0f, 0.0f, 0.0f);

		gluLookAt(
			camera->eye.x, camera->eye.y, camera->eye.z,  // eye
			0,0,0, // camera->position.x, camera->position.y, camera->position.z, // position
			camera->up.x, camera->up.y, camera->up.z // up
		);

		glTranslatef(position_from_camera.x, position_from_camera.y, position_from_camera.z);

		glScalef(scale.x, scale.y, scale.z);

		glRotatef(rotation.x, 0.0f, -1.0f, 0.0f);
		glRotatef(rotation.y, 0.0f, 0.0f, -1.0f);
		glRotatef(rotation.z, -1.0f, 0.0f, 0.0f);

		DrawElements();
	}
	glPopMatrix();
}

void Mesh::Render(const Vector3& position, const Vector3& rotation, const Camera* camera) const {
	Render(position, rotation, Vector3::One, camera);

}

void Mesh::Render(const Vector3& position, const Camera* camera) const {
	Render(position, Vector3::Zero, Vector3::One, camera);
}

/// Thank you to Zan Lynx for this int parser from a string, and thanks to LiveLaughLove for the original post on stack overflow.
/// Answer Post: https://stackoverflow.com/a/48528969

std::vector<int> parseInts(std::string str) {
	std::vector<int>lifeishard;
	std::stringstream output;
	std::string lifeisgood = str;
	output.str(lifeisgood);
	int life;
	char ch;
	while (output >> life) {
		lifeishard.push_back(life);
		output >> ch;
	}
	return lifeishard;
}
