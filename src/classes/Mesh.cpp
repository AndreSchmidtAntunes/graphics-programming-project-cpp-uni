#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "Texture2D.h"

#define TYPE GLfloat
#define DEFAULT_VERT_COLOUR Colour::Red

static const double PI  = 3.141592653589793;
static const double PHI = 1.570796326794897;
static const double RAD2DEG = 57.29577951308232;
static const double DEG2RAD = 0.017453292519943;

Mesh::Mesh(const Vector3* vertices, const size_t vertices_count, const GLuint* indices, const size_t indices_count, const Vector3* normals, const size_t normals_count, const TexCoord* tex_coords, const size_t tex_coords_count, const Colour* colours, const size_t colours_count, const Texture2D* texture) {
	
	this->vertices_size = vertices_count;
	this->vertices = new vertex_data[vertices_count];

	this->vert_indices_count = indices_count;
	this->vert_indices = new GLuint[indices_count];

	for (size_t vert = 0; vert < vertices_count; vert++) {
		this->vertices[vert] = vertex_data(vertices[vert], tex_coords[vert], normals[vert]);
	}
	if (normals != nullptr && normals_count > 0) {
		this->has_normals = true;
	}
	if (tex_coords != nullptr && tex_coords_count > 0) {
		this->has_tex_coords = true;
	}
	if (colours != nullptr && colours_count > 0) {
		this->has_colours = true;
	}
}

Mesh::~Mesh() {
	delete[vertices_size] vertices;
	delete[vert_indices_count] vert_indices;
}



bool Mesh::LoadFromFile(const char* file_name, const Texture2D* texture) {

	/// TODO: add svg support or whatever its called

	std::vector<Vector3> l_vertices = {}, l_normals = {};
	std::vector<TexCoord> l_tex_coords = {};

	std::vector<size_t> l_vert_indices, l_tex_coord_indices, l_normal_indices;

	std::ifstream file(file_name);

	if (!file.good()) {
		std::cerr << "Error opening file: " << file_name << std::endl;
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
				Vector3 new_vertex_pos;

				for (size_t i = 0; i < 3; i++) {
					iss >> coord;
					new_vertex_pos[i] = coord;
				}
				l_vertices.push_back(new_vertex_pos);

				continue;
			}

			else if (type == "vt") { // vertex texture coordinate list
				has_tex_coords = true;

				TexCoord new_tex_coord;
				
#define TEX_COORD_N_DIM 2

				int i = 0;
				while (i < TEX_COORD_N_DIM && iss >> new_tex_coord[i]) { // add each coordinate to the correct index in new_tex_coord
					i++;
				}
#undef TEX_COORD_N_DIM

				l_tex_coords.push_back(new_tex_coord);
				continue;
			}

			else if (type == "vn") { // vertex normals list
				has_normals = true;

				TYPE coord;
				Vector3 new_vertex_normal;

				for (int i = 0; i < 3; i++) {
					iss >> coord;
					new_vertex_normal[i] = coord;
				}
				l_normals.push_back(new_vertex_normal);
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

						switch (datatype) {

						case 0: indices_str += (vert_data[i]); break;
						case 1: tex_coord_indices_str += (vert_data[i]); break;
						case 2: normal_indices_str += (vert_data[i]); break;
							    
						default: return false;
						}
					}

					char* strtol_output;

					l_vert_indices.push_back(std::strtol(indices_str.c_str(), &strtol_output, 10));
					l_normal_indices.push_back(std::strtol(normal_indices_str.c_str(), &strtol_output, 10));
					l_tex_coord_indices.push_back(std::strtol(tex_coord_indices_str.c_str(), &strtol_output, 10));
				}
				continue;
			}

			else if (type == "s") { // shading mode
				std::string mode;
				iss >> mode;
				if (mode == "0" || mode == "off") {
					shade_smooth = false;
				}
				else if (mode == "1" || mode == "on") {
					shade_smooth = true;
				}
				else {
					std::cerr << "Unknown shading mode at file: " << file_name << ", line: " << _current_line << std::endl;
				}
				continue;
			}

			else if (type == "o") { // mesh name 
				name = iss.str();
				continue;
			}

			else if (type[0] == '#') { // comment
				continue;
			} 

			else { // unknown or erroneous line mode
				std::cerr << "Unknown or erroneous command at file: " << file_name << ", line: " << _current_line << std::endl;
				continue;
			}
		}
	}

	vert_indices_count = l_vert_indices.size();
	vert_indices = new GLuint[vert_indices_count]{};

	this->vertices = new vertex_data[l_vertices.size()]{ };

	for (size_t i = 0; i < vert_indices_count; i++ ) {

		// subtract 1 because .obj files begin indexing at 1
		size_t vert_index = l_vert_indices[i]				- 1;
		size_t tex_coords_index	= l_tex_coord_indices[i]  - 1;
		size_t normal_index = l_normal_indices[i]			- 1;

		this->vert_indices[i] = vert_index;

		this->vertices[vert_index].position = l_vertices[vert_index];
		this->vertices[vert_index].tex_coord = l_tex_coords[tex_coords_index];
		this->vertices[vert_index].normal = l_normals[normal_index];
	}

	std::cout << "Successfully loaded mesh: " << file_name << std::endl;
	return true;
}

#include "GLExtras.h"

#define VERTEX_DATA_STRIDE 48

void Mesh::DrawElements() const {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, VERTEX_DATA_STRIDE, vertices );

		glShadeModel(shade_smooth ? GL_SMOOTH : GL_FLAT);

		if (has_tex_coords) {
			glBindTexture(GL_TEXTURE_2D, texture->getID());
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, VERTEX_DATA_STRIDE, vertices + 12);
		} // where should i use uv and normal indicies?

		if (has_normals) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_FLOAT, VERTEX_DATA_STRIDE, vertices + 20);
		}

		if (has_colours) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_FLOAT, VERTEX_DATA_STRIDE, vertices + 32);
		}

		glDrawElements(GL_TRIANGLES, vert_indices_count, GL_UNSIGNED_INT, vert_indices);
	
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
}

void Mesh::RenderWithoutMatrices(Camera* const camera, const Vector3& position, const Quaternion& rotation, const Vector3& scale) const {
	//glLoadIdentity(); /// might need to remove

	//glPushMatrix();
	//{
		Vector3 rotation_from_camera = -(camera->euler_rotation);

		Vector3 position_from_camera = position - camera->position;

		gluLookAt(
			camera->eye.x, camera->eye.y, camera->eye.z,  // eye
			0, 0, 0,
			camera->up.x, camera->up.y, camera->up.z // up
		);

		glTranslatef(position_from_camera.x, position_from_camera.y, position_from_camera.z);

		glScalef(scale.x, scale.y, scale.z);

		glRotatef(2 * acos(rotation.w) * RAD2DEG, rotation.x, rotation.y, rotation.z);

		DrawElements();
	//}
	//glPopMatrix();
}
void Mesh::Render(Camera* const camera, const Vector3& position, const Quaternion& rotation, const Vector3& scale) const
{
	glLoadIdentity(); /// might need to remove

	glPushMatrix();
	{
		Vector3 rotation_from_camera = -(camera->euler_rotation);

		Vector3 position_from_camera = position - camera->position;

		gluLookAt(
			camera->eye.x, camera->eye.y, camera->eye.z,  // eye
			0,0,0,
			camera->up.x, camera->up.y, camera->up.z // up
		);

		glTranslatef(position_from_camera.x, position_from_camera.y, position_from_camera.z);

		glScalef(scale.x, scale.y, scale.z);

		glRotatef(2 * acos(rotation.w) * RAD2DEG, rotation.x, rotation.y, rotation.z);

		DrawElements();
	}
	glPopMatrix();
}
