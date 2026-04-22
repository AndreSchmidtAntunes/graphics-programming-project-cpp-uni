#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Texture2D.h"

#define TYPE GLfloat
#define DEFAULT_VERT_COLOUR Colour::Red

Mesh::Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count) {
	
	this->vertices_size = vertices_count;
	this->vert_indices_size = indices_count;

	normals = nullptr;
	colours = nullptr;
	tex_coords = nullptr;
	normal_indices = nullptr;
	normals_size = tex_coords_size = colours_count = 0;

	this->normals_size = normals_size;

	this->vertices = new GLfloat[vertices_count];
	for (size_t i = 0; i < vertices_count; i++) {
		this->vertices[i] = vertices[i];
	}

	this->vert_indices = new GLuint[indices_count];
	for (size_t i = 0; i < indices_count; i++) {
		this->vert_indices[i] = indices[i];
	}
}

Mesh::Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* colours, const size_t colours_count) : Mesh(vertices, vertices_count, indices, indices_count) {

	this->colours_count = colours_count;

	normals = nullptr;
	tex_coords = nullptr;
	normal_indices = nullptr;
	normals_size = tex_coords_size = 0;

	this->colours = new GLfloat[colours_count];
	for (size_t i = 0; i < colours_count; i++) {
		this->colours[i] = colours[i];
	}
};

Mesh::Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TexCoord* tex_coords, const size_t tex_coord_count) : Mesh(vertices, vertices_count, indices, indices_count) {

	this->normals_size = normals_count;
	this->tex_coords_size = tex_coord_count;

	colours = nullptr;
	colours_count = 0;
	
	this->normals = new GLfloat[normals_count];
	for (size_t i = 0; i < normals_count; i++) {
		this->normals[i] = normals[i];
	}
	
	this->tex_coords = new TexCoord[tex_coord_count];
	for (size_t i = 0; i < tex_coord_count; i++) {
		this->tex_coords[i] = tex_coords[i];
	}
}

Mesh::Mesh(const TYPE* vertices, const size_t vertices_count, const size_t* indices, const size_t indices_count, const TYPE* normals, const size_t normals_count, const TexCoord* tex_coords, const size_t tex_coord_count, const TYPE* colours, const size_t colours_count) : Mesh(vertices, vertices_count, indices, indices_count, normals, normals_count, tex_coords, tex_coord_count) {
	this->colours_count = colours_count;

	this->colours = new GLfloat[colours_count];
	for (size_t i = 0; i < colours_count; i++) {
		this->colours[i] = colours[i];
	}
}

Mesh::~Mesh() {
	delete[this->vertices_size] this->vertices;
	delete[this->normals_size] this->normals;
	delete[this->tex_coords_size] this->tex_coords;
	delete[this->vert_indices_size] this->vert_indices;
	delete[this->normal_indices_size] this->normal_indices;
	delete[this->tex_coord_indices_size] this->tex_coord_indices;
}

bool Mesh::LoadFromFile(const std::string& filename, const Texture2D* texture) {

	std::vector<float> vertices = {}, normals = {};
	std::vector<TexCoord> tex_coords = {};

	std::vector<size_t> vert_indices = {}, tex_coord_indices = {}, normal_indices = {};

	std::ifstream file(filename);

	if (!file.good()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	this->texture = texture;

	std::string line = "";

	size_t _current_line = 0;
	while (std::getline(file, line)) {
		std::stringstream iss(line);

		_current_line++;

		std::string type;
		if (iss >> type) {
			if (type == "v") { // vertex defenition list (points)

				TYPE coord;

				while (iss >> coord) 
					vertices.push_back(coord);

				continue;
			}

			else if (type == "vt") { // vertex texture coordinate list

				TexCoord new_tex_coord;
				
#define TEX_COORD_N_DIM 2

				int i = 0;
				while (i < TEX_COORD_N_DIM && iss >> new_tex_coord[i]) { // add each coordinate to the correct index in new_tex_coord
					i++;
				}
#undef TEX_COORD_N_DIM

				tex_coords.push_back(new_tex_coord);
				continue;
			}

			else if (type == "vn") { // vertex normals list

				TYPE coord;

				while (iss >> coord)
					normals.push_back(coord);
			}

			else if (type == "f") { // face defenition (polygon)

				std::string vert_data;

				while (iss >> vert_data) {
					std::string indices_str = "";
					std::string tex_coord_indices_str = "";
					std::string normal_indices_str = "";

					size_t datatype = 0; // 0 = vert indices, 1 = texture coordinate indices, 2 = normal indices
					for (size_t i = 0; i < vert_data.length(); i++) {

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
						case 1: tex_coord_indices_str += (vert_data[i]); break;
						case 2: normal_indices_str += (vert_data[i]); break;
							    
						default: return false;
						}
					}

					char* strtol_output;

					vert_indices.push_back(std::strtol(indices_str.c_str(), &strtol_output, 10));
					normal_indices.push_back(std::strtol(normal_indices_str.c_str(), &strtol_output, 10));
					tex_coord_indices.push_back(std::strtol(tex_coord_indices_str.c_str(), &strtol_output, 10));

				}
				continue;
			}

			else if (type == "o") { // mesh name 
				continue; /// TODO: add data to mesh class
			}

			else if (type[0] == '#') { // comment
				continue;
			} 

			else { // unknown or erroneous line mode
				std::cerr << "Unknown or erroneous command at file: " << filename << ", line: " << _current_line << std::endl;
				continue;
			}
		}
	}
	
	this->vertices_size = vertices.size();
	this->normals_size = normals.size();
	this->tex_coords_size = tex_coords.size();

	this->vert_indices_size = vert_indices.size();
	this->normal_indices_size = normal_indices.size();
	this->tex_coord_indices_size = tex_coord_indices.size();

	delete[this->vertices_size] this->vertices;
	delete[this->normals_size] this->normals;
	delete[this->tex_coords_size] this->tex_coords;

	delete[this->vert_indices_size] this->vert_indices;
	delete[this->normal_indices_size] this->normal_indices;
	delete[this->tex_coord_indices_size] this->tex_coord_indices;

	this->vertices = new GLfloat[vertices_size]{};
	this->normals  = new GLfloat[normals_size]{};
	this->tex_coords = new TexCoord[tex_coords_size]{};

	this->vert_indices = new GLuint[vert_indices_size]{};
	this->normal_indices = new GLuint[vert_indices_size]{};
	this->tex_coord_indices = new GLuint[normal_indices_size]{};

	for (size_t i = 0; i < vertices_size; i++)
		this->vertices[i] = vertices[i];

	for (size_t i = 0; i < normals_size; i++)
		this->normals[i] = normals[i];

	for (size_t i = 0; i < tex_coords_size; i++)
		this->tex_coords[i] = tex_coords[i];

	for (size_t i = 0; i < vert_indices_size; i++)
		this->vert_indices[i] = vert_indices[i];

	for (size_t i = 0; i < normal_indices_size; i++)
		this->normal_indices[i] = normal_indices[i];

	for (size_t i = 0; i < tex_coord_indices_size; i++)
		this->tex_coord_indices[i] = tex_coord_indices[i];

	return true;
}

#include "GLExtras.h"

void Mesh::DrawElements() const {
		glEnableClientState(GL_VERTEX_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, vertices);

		if (normals != nullptr && normals_size > 0) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, 0, normals);
		}

		if (tex_coords != nullptr && tex_coords_size > 0) {
			glBindTexture(GL_TEXTURE_2D, texture->getID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, 0, tex_coords);
		} // where should i use uv and normal indicies?

		if (colours != nullptr && colours_count > 0) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, 0, colours);
		}
		//else
		//	GLExtras::SetColour(DEFAULT_VERT_COLOUR);

		glDrawElements(GL_TRIANGLES, vert_indices_size, GL_UNSIGNED_INT, vert_indices);
	
		glDisableClientState(GL_VERTEX_ARRAY);

		if (normals != nullptr)
			glDisableClientState(GL_NORMAL_ARRAY);

		if (tex_coords != nullptr)
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		if (colours == nullptr)
			glDisableClientState(GL_COLOR_ARRAY);
}

void Mesh::Render(const Vector3& position, const Vector3& rotation, const Vector3& scale, const Camera* camera) const {
	glLoadIdentity();

	glPushMatrix();
	{
		Vector3 rotation_from_camera = -(camera->rotation);

		Vector3 position_from_camera = position - camera->position;

		gluLookAt(
			camera->eye.x, camera->eye.y, camera->eye.z,  // eye
			0,0,0,
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
