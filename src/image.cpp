#include "common.hpp"

#include <fstream>
#include <sstream>

void write_frame(image_buffer render_buffer, unsigned int frame_number)
{
	std::stringstream filename; filename.fill('0'); filename.width(3); filename << std::to_string(frame_number);

	std::string file_name = "render/frame" + filename.str() + ".ppm";

	std::ofstream image_file;

	image_file.open(file_name);

	image_file << "P6\n" << render_buffer.buffer_size_x << " " << render_buffer.buffer_size_y << "\n255\n";

	for(unsigned int i = 0; i < render_buffer.buffer_size; i++)
	{
		// Quantization
		unsigned char channel_r = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].r), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_g = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].g), (unsigned int)0 ), (unsigned int)255);
		unsigned char channel_b = (unsigned char)std::min(std::max( (unsigned int)(255.0 * render_buffer.buffer[i].b), (unsigned int)0 ), (unsigned int)255);

		image_file << channel_r << channel_g << channel_b;
	}

	image_file.close();
}